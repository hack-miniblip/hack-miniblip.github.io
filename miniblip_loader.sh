#!/bin/bash
#Simple miniblip loader
#by @demiurgosoft


if [ $# != 1 ]
then
	echo "Usage: bliploader + [firmaware.bin]";
else
	port=$(mount | grep "CRP DISABLD" | grep -Eo "^[^ ]+");
	if [ "$port" == "" ]
	then
		port=$(mount | grep "MINIBLIP" | grep -Eo "^[^ ]+");
	fi
	
	if [ "$port" == "" ]
	then
		echo "Not mounted"
	else
		sudo dd if=$1 of=$port bs=512 seek=4 conv=notrunc
		sudo umount $port
		echo "loaded"
	fi
fi
