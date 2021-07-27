#! /usr/bin/env python2

import os
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

SRC_DIR   = os.path.join(os.path.dirname(__file__), "mbed-os")
DEST_DIR  = os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.normcase("../../mbed-os")))

ret = subprocess.check_output('cd {} && mbed releases'.format(DEST_DIR), shell=True)

for line in ret[ret.index('*'):].splitlines():
    if line.find("<-") > -1:
        OSv = line.strip(" *").split(' ', 1)[0]

if OSv == "mbed-os-6.12.0":
    if shell_ENV == "Windows":
        cmd = "XCOPY {}\* {} /Y /S /I".format(SRC_DIR, DEST_DIR)
    elif shell_ENV == "Linux" or shell_ENV == "Darwin":
        cmd = "sudo cp -v -R {}/. {}".format(SRC_DIR, DEST_DIR)
    else:
        raise Exception("This script cannot run on {}".format(shell_ENV))
    print("{}Patching{} ... {}{}{}".format(CLR["GREEN"], CLR["ENDC"], CLR["RED"], OSv, CLR["ENDC"]))
    ret = subprocess.check_output(cmd, shell=True)
    print("{}{}{}Patch Applied successfully!".format(CLR["RED"], ret, CLR["ENDC"]))
else:
    print("This Patch is for {}mbed-os-6.12.0{}, but currently used version is {}{}{}. Either update it to 6.12.0, or patch it manually !!!".format(CLR["GREEN"], CLR["ENDC"], CLR["RED"], OSv, CLR["ENDC"]))
