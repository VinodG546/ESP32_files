#include<WiFi.h>
#include<WebServer.h>

const char *ssid="realme X";
const char *password="11111111";

WebServer server(80);

void handleRoot(){
  server.send(200,"text/plain","ESP32 Web server is running");  
}
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nconected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
