#!/bin/sh
DEVICE="/dev/sdb"
echo "Copiando "$1" a "$DEVICE

sudo dd if=$1 of=$DEVICE bs=512 seek=4 conv=notrunc
