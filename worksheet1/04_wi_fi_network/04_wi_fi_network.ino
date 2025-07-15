#include<WiFi.h>

const char *ssid="realme X";
const char *password="11111111";
void initWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  Serial.println("connecting to wifi..");
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.print("RSSI");
  Serial.println(WiFi.RSSI());
}
void setup() {
  Serial.begin(115200);
  initWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:

}
