import serial
import webbrowser


ser = serial.Serial('COM3',115200)

while True:
    if ser.in_waiting > 0:
        command = ser.readline().decode().strip()
        if command == "Youtube":
            webbrowser.open("https://www.youtube.com")

        if command == "Github":
            webbrowser.open("https://www.Github.com")


