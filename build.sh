#!/bin/bash
make CROSS_COMPILE=arm-eabi-4.7/bin/arm-eabi- clean
make CROSS_COMPILE=arm-eabi-4.7/bin/arm-eabi- mrproper
make CROSS_COMPILE=arm-eabi-4.7/bin/arm-eabi- m8_defconfig
make CROSS_COMPILE=arm-eabi-4.7/bin/arm-eabi- -j16
find . -name '*.ko' -exec cp {} output/  \;
