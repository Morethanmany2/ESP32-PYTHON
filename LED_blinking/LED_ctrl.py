import serial

ser = serial.Serial('COM3', 9600)  # change COM port

while True:
    cmd = input("Enter 1 (ON) or 0 (OFF): ")
    ser.write(cmd.encode())