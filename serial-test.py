import serial
import time

ser = serial.Serial("/dev/ttyACM4",115200)
time.sleep(1);
print ser.readline();
ser.write('c');
time.sleep(1);
#while True:
ser.write('1');
time.sleep(0.5);

ser.close();
