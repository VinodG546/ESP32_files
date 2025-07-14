const int redPin = 14; // GPIO pin connected to the red LED
const int greenPin = 27; // GPIO pin connected to the green LED
const int bluePin = 26; // GPIO pin connected to the blue LED

void setup() {
  pinMode(redPin, OUTPUT); // Set the red LED pin as output
  pinMode(greenPin, OUTPUT); // Set the green LED pin as output
  pinMode(bluePin, OUTPUT); // Set the blue LED pin as output
}

void color(int r,int g,int b){
  // Set the LED to red
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  delay(500); 
}
void loop() {
 color(255,0,0);

  color(0,255,0);

  color(0,0,255);

  color(255,255,255);
}