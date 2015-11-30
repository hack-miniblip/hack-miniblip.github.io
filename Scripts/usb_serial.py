import serial
import sys
import os
import time

#Based on example leds_serial_potenciometro_buzzer
#A koala made this pretty
#Execute as sudo


def connect():
	try:
		dev=os.popen("ls /dev/ttyACM*").read();
		dev=dev.rstrip()
	except:
		return None	
	if len(dev)==0:
		return None
	try:
		ser = serial.Serial(dev, 9600)
	except:
		return None
	return ser

ser=None
while not ser:
	ser=connect()
	time.sleep(1);

while True:
	try:
		print ser.readline()
		time.sleep(0.01)
	except:
		print("Problem in connection");
		ser=connect()	
		time.sleep(1)
						
			
