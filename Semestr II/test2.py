import serial
import re

ser = serial.Serial('/dev/ttyACM0', 9600)
ser.flush()

while(True):
    b = ser.readline()
    s = str(b, "ascii", "ignore")
    data = tuple(re.findall(r'(?:\-?\d+)(?:\.\d+)?', s))
    
    if len(data) == 0:
        print("Odp: " + s)
        continue
    
    if len(data) == 5 or len(data) == 6:
        print(data)
    
        if int(data[1]) > 50:
            ser.write(b"ACK")
    else:
        print("error")
    
    
ser.close()