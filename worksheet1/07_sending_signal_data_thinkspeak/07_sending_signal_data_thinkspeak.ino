#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "realme X";             
const char* password = "11111111";      
const char* apiKey = "LXUY4Q0K7K7E4F2J";         

const char* server = "http://api.thingspeak.com/update";

const int trigPin = 5;
const int echoPin = 18;

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

long readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;  // in cm
}

void loop() {
  long distance = readDistanceCM();
  if(distance < 30){
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(distance);
    http.begin(url);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("ThingSpeak response: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error in sending: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(15000); // ThingSpeak accepts updates every 15 seconds
  }
}
