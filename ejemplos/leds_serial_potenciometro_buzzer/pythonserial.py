import serial
import sys

if  len(sys.argv) > 1 :
  dev = sys.argv[1] 
else:
  dev = "/dev/ttyACM0"

ser = serial.Serial(dev, 9600)
while True:
  print ser.readline()
