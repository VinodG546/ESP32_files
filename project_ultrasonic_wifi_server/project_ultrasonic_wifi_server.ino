#include <WiFi.h>
#include <time.h>
#include <WebServer.h>
#include <SPIFFS.h> //Serial Peripheral Interface Flash File System  

#define  trigPin   5
#define  echoPin   18

// WiFi credentials
#define ssid "realme X"
#define password "11111111"

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
long duration;
float distanceCm;

//time variables
const long gmtOffset=19800 ; // 5.5*3600

//bluetooth variables
//BluetoothSerial SerialBT;

// create web server object on port 80 (HTTP default port) 
WebServer server(80); 
//syntax : Webserver server(port);

//Maximum history entries to store and display 
#define MAX_HISTORY 10


//buffer to store sensor reading history 
String history[MAX_HISTORY]; //Circular buffer to store message 
unsigned int historyIndex=0; //Tracks the next write position in buffer 

/*
  Function return current time 
*/

String getCurrentTime(){
  struct tm timeinfo ; // structure to hold time 

  if(!getLocalTime(&timeinfo)){ //Get time from NTP server 
    return "Time not set ";

  }
  char timestr[30];
  strftime(timestr , sizeof(timestr), "%Y-%m-%d %H:%M:%S",&timeinfo);
  return String(timestr); //return time in string 

}


/* 
 * This function Creates a web page that displays the ultrasonic sensor history
 * Syntax:
 *    server.send(status_code, "content_type", content);
 */

 void Server_page() {
  String html = "<html><head><title>ESP32 Ultrasonic Sensor</title>";
  html += "<meta http-equiv='refresh' content='2'>";  // Auto-refresh page every 2 seconds
  html += "</head><body>";
  html += "<h2>Ultrasonic History:</h2><ul>";

  // Display all history entries in HTML list
  for (int i = 0; i < MAX_HISTORY; i++) {
  int index = (historyIndex + i) % MAX_HISTORY;
    if (history[index] != "") {
      html += "<li>" + history[index] + "</li>";
    }
  }
  html += "</ul></body></html>";
  server.send(200, "text/html", html);  // Send HTML page to client

}


/*
this function used to store the history of sensor in buffer
 */
void add_to_history(String msg ){
  history[historyIndex % MAX_HISTORY]=msg;
  historyIndex++;
}



void setup() {
  Serial.begin(9600); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  
  //configure wifi 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("\nConnected! IP address:");
  Serial.println(WiFi.localIP());  // Print the IP address assigned to ESP32

  configTime(gmtOffset,0 , "pool.ntp.org","time.nist.gov");
  

  server.on("/", Server_page);  // Assign the web page handler to root URL
  server.begin();               // Start the HTTP server
  Serial.println("HTTP server started");
 
  
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

  server.handleClient();  // Handle incoming HTTP client requests
  
  if ( distanceCm < 30 && distanceCm>2){
    
    Serial.print("object in target range 30cm ");
    Serial.println(distanceCm);
    String str = "Object in target range " + String(distanceCm, 2) + " cm at " + getCurrentTime();
  add_to_history(str );
  }
  
  delay(200);
}