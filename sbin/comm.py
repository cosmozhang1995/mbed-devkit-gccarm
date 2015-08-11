import sys
import select
import serial

port = sys.argv[1]
baudrate = int(sys.argv[2])

uarts = serial.Serial(port, baudrate, timeout = None)

stdin = sys.stdin

user_input = ""
ch = ''

def iseof(stream):
    _streams = select.select([stream], [], [], 0)[0]
    if _streams: return False
    else: return True

while True:
    while not iseof(stdin):
        user_input = stdin.readline()
        uarts.write(user_input)
    while not iseof(uarts):
        sys.stdout.write(uarts.read(1))
        sys.stdout.flush()