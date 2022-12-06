#MQTT Subscribers

#Subscribe to MQTT messages from the Django app and publish to serial(Arduino)

import serial
import numpy as np
import time
import paho.mqtt.client as mqtt

# Run to expose serial port. remember to replace mac address: sudo rfcomm bind /dev/rfcomm0 00:14:03:05:09:E5 1

ser = serial.Serial('/dev/rfcomm0', 9600)
#The callback for when the client receive a connack response from the server
def on_connect(client, uesrdata, flags, rc):
	print ("connectd with result code " +str(rc))

	#subscribe in on connectd() if we loss the connection and
	#reconnect thn subscription will be renewed
	client.subscribe("/mode")
	client.subscribe ("/state")

#The callback for when a PUBLISH message is received from the server
def on_message(client, userdata, msg):
    print (msg.topic+ "" +str(msg.payload))
    raw_data = msg.payload

    if (msg.payload == 1):
        print("Received message #1, do something")
        ser.write(raw_data)

#create an MQTT client and attach our routines to it

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect ("MQTT_5_0-8c3ef6c3-42b7-476d-9464-4fa862509496", 8883, 60)



client.loop_forever()





