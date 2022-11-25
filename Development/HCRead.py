import serial, time
import sys

ser = serial.Serial()
ser.port = "/dev/rfcomm0"
ser.baudrate = 115200
ser.timeout = 1
ser.setDTR(False)
ser.setRTS(False)
ser.open()
old_data = 0
new_data = 0
ser.flushInput()
ser.flush()
ser.flushOutput()
time.sleep(1)

print("Start")
while True:
  raw_data = ser.readline()
  try:
    ser.flushInput()
    new_data = int(raw_data)
    ser.flush()
  except ValueError:
    pass
  print(raw_data)
  if (old_data != new_data -1 and old_data != 0):
    print('ERROR#####################################################')
  old_data = new_data

  time.sleep(0.01)