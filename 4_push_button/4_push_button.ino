#define ledpin 5
#define button 4

int buttonstate = 0; 
void setup() {
  Serial.begin(9600);
  pinMode(button,INPUT);

  pinMode(ledpin,OUTPUT);
}

void loop() {
  buttonstate = digitalRead(button);
  Serial.println(buttonstate);
  if (buttonstate==HIGH){
    digitalWrite(ledpin,HIGH);

  }
  else{
    digitalWrite(ledpin,LOW);
  }
}
