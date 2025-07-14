//project 1 - have to display the time stamps with distance of the object discoverd with different light for different range like < 10cm-red,< 20cm-green ,<30cm -blue
#include <WiFi.h>
#include <time.h>
 
const int trigPin = 5;
const int echoPin = 18;
const int redPin=14;
const int greenPin=27;
const int bluePin=26;

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
  pinMode(redPin, OUTPUT); // Set the red LED pin as output
  pinMode(greenPin, OUTPUT); // Set the green LED pin as output
  pinMode(bluePin, OUTPUT); // Set the blue LED pin as output
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
 void color(int r,int g,int b){
  // Set the LED to red
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  delay(500);
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
  if (distanceCm < 30){
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    if (distanceCm < 10){
      if(getLocalTime(&timeinfo)){
      Serial.print(&timeinfo , "%H:%M:%S");
      }
      Serial.println(distanceCm);
      color(255,0,0);
    }
    else if(distanceCm < 20){
      if(getLocalTime(&timeinfo)){
      Serial.print(&timeinfo , "%H:%M:%S");
      }
      Serial.println(distanceCm);
      color(0,255,0);
    }
    else{
      if(getLocalTime(&timeinfo)){
      Serial.print(&timeinfo , "%H:%M:%S");
      }
      Serial.println(distanceCm);
      color(0,0,255);
    }
  }
  else{
    color(0,0,0);
  }
}
 