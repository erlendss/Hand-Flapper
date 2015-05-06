import pyfirmata
import time
 
# Adjust that the port match your system, see samples below:
# On Linux: /dev/tty.usbserial-A6008rIF, /dev/ttyACM0,
# On Windows: \\.\COM1, \\.\COM2
PORT = 'COM4'
 
 
# Creates a new board 
board = pyfirmata.Arduino(PORT)
print ("Setting up the connection to the board ...")
it = pyfirmata.util.Iterator(board)
it.start()
 
board.analog[0].enable_reporting()
board.analog[1].enable_reporting()
 
 
while True:
    print(board.analog[1].read(),board.analog[0].read())
    time.sleep(0.05)
 
 
 
board.exit()
