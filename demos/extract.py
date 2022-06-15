#! /usr/bin/env python2

import os
import sys
import platform
import subprocess

shell_ENV = platform.system()
if shell_ENV == "Windows":
    os.system("color")

CLR = {
    "GREEN": "\033[92m",
    "RED":   "\033[91m",
    "ENDC":  "\033[0m",
}

TARGETS = [
    'VK_RZ_A1H',
    'VK_RZ_A1LU',
    'VK_RZ_A1R3'
]

BRD = "".join(sys.argv[1:])
PRJ = "".join(sys.argv[2:])

if BRD == "VK_RZ_A1R3":
    if PRJ == "":
        PRJ = "Demo"
    #elif not os.path.isdir(os.path.join(os.path.dirname(__file__),  os.path.normpath('BUILD/{}/E2_GCC_ARM/{}'.format(BRD, PRJ)))):
    #    raise Exception("No Project: {}".format(PRJ))
    #else:

    SRC_DIR = os.path.join(os.path.dirname(__file__),  os.path.normpath('{}/E2_GCC_ARM/{}'.format(BRD, PRJ)))
    DEST_DIR = os.path.join(os.path.dirname(__file__), os.path.normpath('../../BUILD/{}/E2_GCC_ARM/{}'.format(BRD, PRJ)))

    print("SRC: {}".format(SRC_DIR))
    print("DEST: {}".format(DEST_DIR))

    if shell_ENV == "Windows":
        dbg = "XCOPY {}\* {} /Y /S /I".format(SRC_DIR, DEST_DIR)
        cli = "MOVE /Y {} {}".format(os.path.join(DEST_DIR, 'App'), os.path.join(os.path.dirname(__file__), os.path.normpath('../../App')))
    elif shell_ENV == "Linux" or shell_ENV == "Darwin":
        dbg = "sudo mkdir -p {} && sudo cp -rpv {}/. {}".format(DEST_DIR, SRC_DIR, DEST_DIR)
        cli = "sudo mv -v {} {}".format(os.path.join(DEST_DIR, 'App'), os.path.join(os.path.dirname(__file__), os.path.normpath('../../App')))
    else:
       raise Exception("This script cannot run on {}".format(shell_ENV))

    print("Demo ... {}{}{}[{}E2Studio{}]".format(CLR["GREEN"], BRD, CLR["ENDC"], CLR["RED"], CLR["ENDC"]))
    ret = subprocess.check_output(dbg, shell=True)
    print("{}{}{}".format(CLR["RED"], ret, CLR["ENDC"]))

    print("Demo ... {}{}{}[{}CLI1{}]".format(CLR["GREEN"], BRD, CLR["ENDC"], CLR["RED"], CLR["ENDC"]))
    ret = subprocess.check_output(cli, shell=True)
    print("{}{}{}".format(CLR["RED"], ret, CLR["ENDC"]))
else:
    print("Unrecognized target: {}{}{} !!!".format(CLR["RED"], BRD, CLR["ENDC"]))