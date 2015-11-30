#!/bin/bash
#Simple miniblip loader
#by @demiurgosoft


if [ $# != 1 ] 
then 
	echo "Usage: bliploader + [firmaware.bin]";
else
	port=$(mount | grep "CRP DISABLD1" | grep -Eo "^[^ ]+");

	if [$port -eq ""] 
	then 
		echo "Not mounted";
	else
	sudo dd if=$1 of=$port bs=512 seek=4 conv=notrunc
	umount $port
	echo "loaded"
	fi
fi



