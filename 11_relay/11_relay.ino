void setup() {
  pinMode(17, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  delay(1000); 
  digitalWrite(17, HIGH);
    delay(1000);
    digitalWrite(17,LOW);
}