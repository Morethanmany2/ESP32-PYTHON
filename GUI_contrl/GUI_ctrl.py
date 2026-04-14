import tkinter as tk
import serial
import time

# Setup serial
ser = serial.Serial('COM3', 9600)  # change COM
time.sleep(2)

# Functions
def laser_on():
    ser.write(b'ON\n')

def laser_off():
    ser.write(b'OFF\n')

def laser_blink():
    ser.write(b'BLINK\n')

# Create window
root = tk.Tk()
root.title("Laser Control Panel")
root.geometry("300x200")

# Buttons
btn_on = tk.Button(root, text="LASER ON", command=laser_on, height=2, width=20)
btn_on.pack(pady=10)

btn_off = tk.Button(root, text="LASER OFF", command=laser_off, height=2, width=20)
btn_off.pack(pady=10)

btn_blink = tk.Button(root, text="BLINK", command=laser_blink, height=2, width=20)
btn_blink.pack(pady=10)

# Run app
root.mainloop()