import serial
import sys
import time

dev = "/dev/ttyACM0"

ser = serial.Serial(dev, 9600)
while True:
	try:
		var=ser.readline()
	except Exception, e:
	    print "Failed to read in the usual spot: ", e
	    continue
	print var
	time.sleep(0.4)
