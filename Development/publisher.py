# MQTT Publishers

# Publish MQTT messages from the serial(Arduino) to Django.
# It will publish the temperature and humidity data

import serial
import numpy as np
import time
import paho.mqtt.publish as publish

ser = serial.Serial('/dev/rfcomm0', 9600)
#start out the mqtt client with port 1883
def saveReading(topic,data):
    # publish.single(topic, data, hostname="9511cb223d8c4115921ca0e7542cc769.s2.eu.hivemq.cloud") # publishing to webserver. topic name=/cmd
    publish.single(topic, data, hostname="mqttClient-MQTT_5_0-54ea3e4c-1d1a-4ed3-b5d5-5e752925e136") # publishing to webserver. topic name=/cmd
    print('Saving new reading: ' + data)

print("Waiting for data...")
temp = []
start = False

while (True):
    raw_data = ser.readline()
    try:
        ser.flushInput()
        new_data = int(raw_data)
        ser.flush()
    except ValueError:
        pass
    print (raw_data)
    data = ''.join([i for i in raw_data if i.isdigit()])
    if(data == 'C'):
        saveReading('/temperature',raw_data)
    else:
        saveReading('/humidity',raw_data)

    if (old_data != new_data - 1 and old_data != 0):
        print('ERROR#####################################################')
    old_data = new_data

    time.sleep(0.01)

