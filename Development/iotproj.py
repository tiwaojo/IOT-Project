# Grabs temperature and humidity from dht sensors.
# Doesn't work due to PI not haivng Analog Pins

import time
import board
import adafruit_dht

sensor = adafruit_dht.DHT11(pin=board.GPIo14,use_pulseio=True)
while True:
    try:
        temp = sensor._temperature
        humidity = sensor._humidity
        print("Temperature: {}*C   Humidity: {}% ".format(args=temp, kwargs=humidity))
    except RuntimeError as error:
        print(error.args[0])
        time.sleep(2.0)
        continue
    except Exception as error:
        sensor.exit()
        raise error
    time.sleep(2.0)