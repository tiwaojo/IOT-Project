/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Osoyoo W5100 web server lesson 2
 * Send DHT11 temperature data to remote browser
 * tutorial url: https://osoyoo.com/?p=9988
 */
#include <DHT.h>
#include <Servo.h>
#include <ArduinoHttpClient.h>

#include <WiFi101.h>
#define DHT11_PIN A2
#define DHTTYPE DHT11

// dht DHT;
#include "WiFiEsp.h"
#include <Ethernet.h>
#include "SoftwareSerial.h"
SoftwareSerial softserial(4, 5);  // D4 to ESP_TX, D5 to ESP_RX by default

char ssid[] = "TheCrucible";   // replace *** with your wifi network SSID (name)
char pass[] = "2547EC274D76";  // replace *** with your wifi network password
int status = WL_IDLE_STATUS;   // the Wifi radio's status

unsigned int local_port = 8888;   // local port to listen for UDP packets
unsigned int remote_port = 8888;  // remote port to listen for UDP packets


// IPAddress ip(127, 0, 0, 1);

int port = 8000;

char server[] = "127.0.0.1";
// Other endpoints u could try: https://ventilation-system-dashboard-ndrgz.ondigitalocean.app/dashboard/

WiFiEspClient client;
// WiFiClient wifi;
HttpClient httpClient = HttpClient(client, server, port);
// HttpClient httpClient = HttpClient(client, ip, port);


unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10000L;  // delay between updates, in milliseconds

// A UDP instance to let us send and receive packets over UDP
// WiFiEspUDP Udp;


DHT dht(DHT11_PIN, DHTTYPE);  // DHT instance


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;  // variable to store the servo position

void setup() {
  // httpClient.beginRequest()gin("https://localhost:8080/dashboard");

  Serial.begin(9600);  // initialize serial for debugging
  softserial.begin(115200);
  softserial.write("AT+CIOBAUD=9600\r\n");
  softserial.write("AT+RST\r\n");
  softserial.begin(9600);  // initialize serial for ESP module
  WiFi.init(&softserial);  // initialize ESP module

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true)
      ;
  }

  // attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  printWifiStatus();
  // you're connected now, so print out the data
  Serial.println("You're connected to the network,press any key in APP to get remote data!");
    httpClient.setTimeout(10000);

  // Servo setup
  // myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  // Udp.begin(local_port);
}

void loop() {

  dht.begin();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  String temp = String(temperature);
  // String humid = String(humidity)

  String msg = "Temperature:" + temp + "C, Humid:" + humidity + "%" + '\n';
  Serial.print(msg);

  char ReplyBuffer[60];
  msg.toCharArray(ReplyBuffer, 60);
  Serial.println(msg);

  // httpPost(temp);
  // httpGet();

  Serial.println("making GET request");
  // httpClient.get("dashboard/");
  if ( httpClient.get("/dashboard/")) {
  // read the status code and body of the response
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  Serial.println("Wait five seconds");
  delay(5000);
  }else {
  Serial.println(httpClient.available());
  }
  // httpPost(msg);
}

// this method makes a HTTP connection to the server
void httpGet() {
  Serial.println();

  // close any connection before send a new request
  // this will free the socket on the WiFi shield
  // client.stop();
  httpClient.get("/dashboard");

  // if there's a successful connection
  // if (client.connect(ip, port)) {
  if (httpClient.connect(server, port)) {
    httpClient.println("Connecting...");

    // send the HTTP PUT request
    client.println(F("GET /asciilogo.txt HTTP/1.1"));
    client.println(F("Host: arduino.cc"));
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection
    Serial.println("Connection failed");
  }
}

void httpPost(String payload) {
  Serial.println("Payload: " + payload);

  Serial.println("making POST request");
  String contentType = "application/x-www-form-urlencoded";
  String postData = "name=" + payload;

  httpClient.post("/dashboard", contentType, postData);

  // read the status code and body of the response
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Wait five seconds");
  delay(5000);

  // Serial.println();

  // // close any connection before send a new request
  // // this will free the socket on the WiFi shield
  // client.stop();

  // // if there's a successful connection
  // if (client.connect(server, port)) {
  //   // if (client.connect(server, 80)) {
  //   Serial.println("Connecting...");

  //   // send the HTTP PUT request
  //   client.println(F("POST /asciilogo.txt HTTP/1.1"));
  //   client.println(F("Host: arduino.cc"));
  //   client.println("Connection: close");
  //   client.println();
  //   // client.write(payload); // TODO: Write payload to Django app

  //   // note the time that the connection was made
  //   lastConnectionTime = millis();
  // } else {
  //   // if you couldn't make a connection
  //   Serial.println("Connection failed");
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

void printWifiStatus() {
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ipAddr = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ipAddr);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}