# import RPi.GPIO as GPIO
from Arduino import Arduino
import time
import sqlite3 as lite
import serial

con = lite.connect('database.sqlite')
cur = con.cursor()

ser = serial.Serial('COM10', 9600)

LED_PIN = 13 # LED_PIN is 13
PHOTO_CELL = 0 # PHOTO_CELL is A0

arduino = Arduino(baud=9600)
arduino.pinMode(LED_PIN,"OUTPUT")
arduino.pinMode(PHOTO_CELL,"INPUT")

threshold = 650 # The threshold to swithc the bulb on or off

def readldr(PIN):
    reading=0
    arduino.pinMode(pin=PHOTO_CELL,val="INPUT")
    cellVal=arduino.analogRead(pin=PHOTO_CELL)
    time.sleep(0.1)

    while (cellVal < 650):
        reading=reading+1
    return reading
def switchOnLight():
    arduino.pinMode(pin=LED_PIN,val="OUTPUT")
    arduino.digitalWrite(pin=LED_PIN,val="HIGH")
def switchOffLight():
    arduino.pinMode(pin=LED_PIN,val="OUTPUT")
    arduino.digitalWrite(pin=LED_PIN,val="LOW")
def runAutoMode():
    ldr_reading = readldr()
    if ldr_reading < threshold:
        switchOnLight(PHOTO_CELL)
        setCurrentState('on')
    else:
        switchOffLight()
        setCurrentState('off')
def runManualMode():
    state = getCurrentState()
    if state=='on':
        switchOnLight()
        setCurrentState('on')
    elif state=='off':
        switchOffLight()
        setCurrentState('off')
def getCurrentMode():
    cur.execute('SELECT * FROM myapp_mode')
    data = cur.fetchone() #(1, u'auto')
    return data[1]
def getCurrentState():
    cur.execute('SELECT * FROM myapp_state')
    data = cur.fetchone() #(1, u'on')
    return data[1]
def setCurrentState(val):
    query='UPDATE myapp_state set name="'+val+'"'
    cur.execute(query)
    while True:
        currentMode=getCurrentMode()
        if currentMode=='auto':
            runAutoMode()
        elif currentMode=='manual':
            runManualMode()
        time.sleep(5)