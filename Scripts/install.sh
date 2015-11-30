#!/bin/sh
sudo dd if=$1 of=/dev/sdc bs=512 seek=4 conv=notrunc
