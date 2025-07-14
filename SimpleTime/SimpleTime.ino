#include <WiFi.h>
#include <time.h>
 
 
#define  trigPin   5
#define  echoPin   18
#define ssid "realme X"
#define password "11111111"
 
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
long duration;
float distanceCm;
 
const long gmtOffset=19800 ; // 5.5*3600
 
void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  configTime(gmtOffset,0 , "pool.ntp.org","time.nist.gov");
  struct tm timeinfo ;
  Serial.println(&timeinfo ,"time is: %A,%B %d %Y %H:%M:%S");
 
}
 
void loop() {
  struct tm timeinfo ;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
 
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
 
  if ( distanceCm < 30){
    if(getLocalTime(&timeinfo)){
      Serial.print(&timeinfo , "%H:%M:%S");
 
    }
    Serial.print(" object in target range 30cm ");
    Serial.println(distanceCm);
 
  }
 
}
 