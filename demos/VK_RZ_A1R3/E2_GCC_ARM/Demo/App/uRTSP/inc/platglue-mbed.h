#pragma once

#include <mbed.h>
#include "EthernetInterface.h"
//#include <WiFiClient.h>
//#include <WiFiUdp.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

extern EthernetInterface network;

typedef TCPSocket *SOCKET;
typedef UDPSocket *UDPSOCKET;
typedef nsapi_addr_t IPADDRESS; // On linux use uint32_t in network byte order (per getpeername)
typedef uint16_t IPPORT; // on linux use network byte order

#define NULLSOCKET NULL

inline void delay(int ms){
	ThisThread::sleep_for(ms);
}

inline void closesocket(SOCKET s) {
    printf("closing TCP socket\r\n");

    if(s) {
        s->close();
        // delete s; TDP WiFiClients are never on the heap in arduino land?
    }
}

#if defined( __CC_ARM ) || defined( __ARMCC_VERSION )
typedef	unsigned short	u_short;
#define getRandom() rand()
#else
#define getRandom() random()
#endif

inline void socketpeeraddr(SOCKET s, IPADDRESS *addr, IPPORT *port) {
	SocketAddress r;
	if ( s->getpeername(&r) != NSAPI_ERROR_OK )
	{
        printf("getpeername failed\r\n");
        memset(addr, 0, sizeof(IPADDRESS));
        *port = 0;
	}
	else
	{
		*addr = r.get_addr();
		*port = r.get_port();
	}
}

inline void udpsocketclose(UDPSOCKET s) {
    printf("closing UDP socket\r\n");
    if(s) {
        s->close();
        delete s;
    }
}

inline UDPSOCKET udpsocketcreate(unsigned short portNum)
{
    printf("creating UDP socket at port %d\r\n", portNum);
    UDPSOCKET s = new UDPSocket();

    s->open(&network);

    if(s->bind(portNum) != NSAPI_ERROR_OK ) {
        printf("Can't bind port %d\r\n", portNum);
        delete s;
        return NULL;
    }

    return s;
}

// TCP sending
inline ssize_t socketsend(SOCKET sockfd, const void *buf, size_t len)
{
    return sockfd->send(buf, len);
}

inline ssize_t udpsocketsend(UDPSOCKET sockfd, const void *buf, size_t len,
                             IPADDRESS destaddr, IPPORT destport)
{
	SocketAddress sa(destaddr, destport);

	nsapi_size_or_error_t result = sockfd->sendto(sa, buf, len);

	if ( result < 0 )
	{
		printf("error sending udp packet\r\n");

		result = 0;
	}

    return (ssize_t)result;
}

/**
   Read from a socket with a timeout.

   Return 0=socket was closed by client, -1=timeout, >0 number of bytes read
 */
inline int socketread(SOCKET sock, char *buf, size_t buflen, int timeoutmsec)
{
	if (!sock)
		return 0;

	sock->set_timeout(timeoutmsec);

	nsapi_size_or_error_t res = sock->recv(buf, buflen);


    if(res > 0) {
        return res;
    }
    else if(res == 0) {
        return 0; // client dropped connection
    }
    else if (res == NSAPI_ERROR_WOULD_BLOCK || res == NSAPI_ERROR_NO_SOCKET ) {
    	// printf("timeout on read\n");
		return -1;
    }
    else {
    	return 0; // unknown error, just claim client dropped it
    }

}
