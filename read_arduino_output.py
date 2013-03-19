# Requires pySerial
# Get from http://pyserial.sourceforge.net
import serial, csv

arduino = serial.Serial(port="COM3", baudrate=115200, timeout=0)

with open('sensor_output.csv', 'wb') as csv_file:
    writer = csv.writer(csv_file)
    writer.writerow(["Time", "Temperature"])
    
