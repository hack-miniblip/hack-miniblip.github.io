import serial
ser = serial.Serial("/dev/ttyACM13", 9600)
while True:
  print ser.readline()
