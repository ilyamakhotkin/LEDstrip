import serial

port = serial.Serial(
    port='/dev/ttyUSB1',
    baudrate=9600
)
port.isOpen()
port.write(0)
