/*
 SD Card Interface code for ESP32
  SPI Pins of ESP32 SD card as follows:
  CS    = 5;
  MOSI  = 23;
  MISO  = 19;
  SCK   = 18; 
*/
#include <WiFi.h>
#include <time.h>
#include <SPI.h>
#include <SD.h>

//Ultrasonic sensor 
#define  trigPin   27
#define  echoPin   26

//Wifi crendtials 
/*#define ssid "OnePlus"
#define password "subhash33"
*/
#define ssid "realme X"
#define password "11111111"
File myFile; //myfile is File object
const int CS = 5; //Chipselect pin for SSD 


//define sound speed in cm/uS
#define SOUND_SPEED 0.034
long duration;
float distanceCm;


//time variables
const long gmtOffset=19800 ; // 5.5*3600


String getCurrentTime(){
  struct tm timeinfo ; // structure to hold time 

  if(!getLocalTime(&timeinfo)){ //Get time from NTP server 
    return "Time not set ";

  }
  char timestr[30];
  strftime(timestr , sizeof(timestr), "%Y-%m-%d %H:%M:%S",&timeinfo);
  return String(timestr); //return time in string 

}


//Function to Write file in SSD 

void WriteFile(const char * path,  String message){
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(path, FILE_WRITE); 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.printf("Writing to %s ", path);
    myFile.seek(myFile.size());  // Move to end
    myFile.print(message);       // use print (not println if \n is already added)
    myFile.close();
    Serial.println("completed.");
  } 
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening file ");
    Serial.println(path);
  }
}



/*
Function to Read from file in SSD 
*/
void ReadFile(const char * path){
  // open the file for reading:
  myFile = SD.open(path);
  if (myFile) {
     Serial.printf("Reading file from %s\n", path);
     // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close(); // close the file:
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test2.txt");
  }
}

void setup() {
  
  Serial.begin(9600);    // Set serial baud rate to 9600
  delay(500);
 
  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  //pinMode(CS , LOW );
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input


   //configure wifi 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  configTime(gmtOffset,0 , "pool.ntp.org","time.nist.gov");

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
  
  if ( distanceCm > 400 || distanceCm < 2) {
  // Ignore invalid readings
    return;
  }
  
  
  if ( distanceCm < 30){
    
    Serial.print("object in target range 30cm ");
    Serial.println(distanceCm);
    String str="Object in target range 30cm "+getCurrentTime()+"\n";//create string with timestamp   
    WriteFile("/UltrasonicSensorLogfile.txt", str);
  }
  delay(100);

}