#include "DHT.h"
#include <SoftwareSerial.h>
#include <LoRa_E32.h>
// Khởi tạo SoftwareSerial cho E32
SoftwareSerial mySerial(10, 11); // RX, TX
LoRa_E32 e32ttl(&mySerial);

#define DHTPIN 5      // Pin where the sensor is connected
#define DHTTYPE DHT11 // Sensor type

int measurePin = A5;
int mq135 = A0;
int data = 0;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
float tempC = 0;
float limit;

int IN3 = 13;
int IN4 = 12;
ResponseStatus rs;
String se = "";

DHT dht(DHTPIN, DHTTYPE); 

void setup(){
  Serial.begin(9600);
  dht.begin();        // Initialize the sensor
  e32ttl.begin();     
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  if (e32ttl.available()) 
  {
    ResponseContainer rc = e32ttl.receiveMessage();
    if (rc.status.code == E32_SUCCESS) 
      limit = atoi(rc.data.c_str());
  }
  Temp_Humidity();  
  AirQuality();  
  Dust();
  Send();
  se = "";
  
  delay(3000);
  CheckWarning();
}

void Dust()
{
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(deltaTime);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;

  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }

  se += "," + String(dustDensity);
}

void AirQuality()
{
  data = analogRead(mq135);
  se += "," + String(data);
}

void Temp_Humidity()
{
  float humidity = dht.readHumidity();           // Read humidity
  tempC = dht.readTemperature();   // Temperature in Celsius

  if (isnan(humidity) || isnan(tempC)) {
    Serial.println("Error reading data!");
    return;
  }
  
  se += String(tempC);
  se += "," + String(humidity);
}

void Send()
{
  rs = e32ttl.sendMessage(se);
  if (rs.code == E32_SUCCESS)
    Serial.println("Message sent successfully.");
  else
    Serial.println("Failed to send message.");
}

void CheckWarning()
{
    if (tempC>=limit)
    {
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
    }
    else
    {
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
    }
}
