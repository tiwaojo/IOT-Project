// #include <dht.h>
#include "DHT.h"
#include <SoftwareSerial.h>

#include <Servo.h>


#define DHTPIN A0
#define DHTTYPE DHT11

// dht DHT;
SoftwareSerial btSerial(4, 5);  // TX, RX
DHT dht(DHTPIN, DHTTYPE);


const int dht11 = A0;
float degreesC;
unsigned long timer = 0;
int sendStatus = 0;
Servo myservo;  // create servo object to control a servo

int pos = 0;  // variable to store the servo position
void setup() {

  //Setup and flush the serials to begin
  btSerial.begin(9600);
  Serial.begin(9600);
  btSerial.flush();
  Serial.flush();

  // Servo setup
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
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
    runFan();

  // Run Fan if cmd is received
  // int cmd;
  // if (btSerial.read(cmd) == 1) {
  // }
}

void runFan() {
  for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);           // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    myservo.write(pos);                  // tell servo to go to position in variable 'pos'
    delay(15);                           // waits 15 ms for the servo to reach the position
  }
}