import serial
ser = serial.Serial("/dev/ttyACM10", 9600)
while True:
  print ser.readline()
