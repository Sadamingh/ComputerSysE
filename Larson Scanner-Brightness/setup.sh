#!/bin/bash

arm-none-eabi-as brightness.s -o brightness.o
arm-none-eabi-objcopy brightness.o -O binary brightness.bin
rpi-install.py brightness.bin