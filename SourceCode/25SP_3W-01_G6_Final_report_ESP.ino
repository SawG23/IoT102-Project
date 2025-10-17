#define BLYNK_TEMPLATE_ID "TMPL6aJxrMgdM"
#define BLYNK_TEMPLATE_NAME "final"
#define BLYNK_AUTH_TOKEN "TClIS1GIqg6Q0pTUpZkQUiGKggSmIUcd"
// kết nối với Blynk

#include <SoftwareSerial.h>
#include <LoRa_E32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>  // kết nối mạch ESP8266 với mạng Wifi
#include <BlynkSimpleEsp8266.h>   // kết nối giao tiếp giữa Blynk và ESP8266

// Khởi tạo SoftwareSerial cho E32
SoftwareSerial mySerial(D2, D1); // RX, TX
LoRa_E32 e32ttl(&mySerial);

// Khởi tạo LCD I2C - địa chỉ thường gặp là 0x27 hoặc 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2); // (I2C address, columns, rows)
String str[4] = {"Temp: ", "Humidity: ", "Air Quality: ", "Dust: "};
int V[4] = {V3, V1, V2, V0};
float limit;
const char* ssid = "Minions";
const char* pass = "Trunghieu05";
ResponseStatus rs;

BLYNK_WRITE(V4)
{
  limit = param.asFloat();
  rs = e32ttl.sendMessage(String(limit));
}

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(500);
  e32ttl.begin();

  // Khởi tạo I2C với chân tùy chỉnh: SDA = D4 (GPIO2), SCL = D7 (GPIO13)
  Wire.begin(D4, D7);

  // Khởi động LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  WiFi.begin(ssid, pass); // kết nối mạng Wifi
  Blynk.config(BLYNK_AUTH_TOKEN); // kết nối với blynk thông qua mã xác thực của BLYNK_AUTH_TOKEN
}

void loop()
{
  Blynk.run();
  if (e32ttl.available())
  {
    ResponseContainer rc = e32ttl.receiveMessage();
    if (rc.status.code == E32_SUCCESS)
    {
      String data = rc.data;
      int dem = 0;
      for (int i = 0; i < data.length(); i++)
        if (data.charAt(i) == ',')
          dem++;
      
      lcd.clear();
      if (dem == 3)
      {
        for (int i = 0; i <= 3; i++)
        {
          int j = data.indexOf(',');
          
          if (i == 2)
            lcd.setCursor(0, 1);
          if (i == 0)
            lcd.setCursor(0, 0);
            
          lcd.print(str[i] + data.substring(0, j) + " ");
          float f = atof(data.c_str());
          Blynk.virtualWrite(V[i], f);
          data.remove(0, j + 1);
          delay(1000);
        }
      }
    }
  }
}
