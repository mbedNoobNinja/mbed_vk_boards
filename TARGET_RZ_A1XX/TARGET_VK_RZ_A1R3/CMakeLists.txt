# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

if(${MBED_TOOLCHAIN} STREQUAL "ARM")
    set(LINKER_FILE device/TOOLCHAIN_ARM_STD/VKRZA1R3.sct)
    set(STARTUP_FILE device/TOOLCHAIN_ARM_STD/startup_VKRZA1R3.S)
    set(WEAK_HANDLER_FILE device/TOOLCHAIN_ARM_STD/weak_handler.S)
elseif(${MBED_TOOLCHAIN} STREQUAL "GCC_ARM")
    set(LINKER_FILE device/TOOLCHAIN_GCC_ARM/VKRZA1R3.ld)
    set(STARTUP_FILE device/TOOLCHAIN_GCC_ARM/startup_VKRZA1R3.S)
    set(WEAK_HANDLER_FILE device/TOOLCHAIN_GCC_ARM/weak_handler.S)
endif()

add_library(mbed-vk-rz-a1r3 INTERFACE)


target_include_directories(mbed-vk-rz-a1r3
    INTERFACE
        .
        device
        device/inc
        device/inc/iobitmasks
        device/inc/iodefines
)

target_sources(mbed-vk-rz-a1r3
    INTERFACE
    PeripheralPins.c

    device/RZ_A1_Init.c
    device/cmsis_nvic.c
    device/w25q128jv_boot.c
    device/mmu_RZ_A1LU.c
    device/nvic_wrapper.c
    device/os_tick_ostm.c
    device/system_RZ_A1LU.c

    ${STARTUP_FILE}
    ${WEAK_HANDLER_FILE}
)

mbed_set_linker_script(mbed-vk-rz-a1r3 ${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_FILE})

target_link_libraries(mbed-vk-rz-a1r3 INTERFACE mbed-rz-a1xx)
