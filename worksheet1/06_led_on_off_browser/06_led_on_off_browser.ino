#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "realme X";      
const char *password = "11111111";   
const int ledPin = 2; // Pin connected to LED

WebServer server(80); // Create web server on port 80

void handleRoot() {
  String html = "<html>\
  <head><title>ESP32 LED Control</title></head>\
  <body>\
    <h2>ESP32 Web Server</h2>\
    <p><a href=\"/on\"><button>LED ON</button></a></p>\
    <p><a href=\"/off\"><button>LED OFF</button></a></p>\
  </body>\
  </html>";

  server.send(200, "text/html", html);
}

void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303); // Redirect to homepage
}

void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303); // Redirect to homepage
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleLEDOn);
  server.on("/off", handleLEDOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Handle web requests
}