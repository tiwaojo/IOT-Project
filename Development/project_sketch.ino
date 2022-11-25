// #include <dht.h>
#include "DHT.h"
#include <SoftwareSerial.h>



#define DHTPIN A4
#define DHTTYPE DHT11

// dht DHT;
SoftwareSerial btSerial(4, 5);  // TX, RX
DHT dht(DHTPIN, DHTTYPE);


const int dht11 = A0;
float degreesC;
unsigned long timer = 0;
int sendStatus = 0;

void setup() {

  //Setup and flush the serials to begin
  btSerial.begin(9600);
  Serial.begin(9600);
  btSerial.flush();
  Serial.flush();
}

void loop() {


  if ((timer == 0 || millis() >= timer) && sendStatus == 0) {
    dht.begin();
    String humidity = "Current Humidity = " + String(dht.readHumidity()) + "%\n";
    Serial.print(humidity);
    String deg = "Current Temperature = " + String(dht.readTemperature()) + "C\n";
    Serial.print(deg);

    // delay(1000);

    // Convert to byte array
    // degree in C
    char charArrayDeg[deg.length() + 1];
    deg.toCharArray(charArrayDeg, deg.length() + 1);
    btSerial.write(charArrayDeg);
    // Humidity in %
    // char charArrayHum[humidity.length() + 1];
    // humidity.toCharArray(charArrayHum, humidity.length() + 1);
    // btSerial.write(charArrayHum);

    //Reset the timer for another 10 seconds.
    timer = millis() + 10000;
  }
}