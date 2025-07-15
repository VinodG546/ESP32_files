const int ppin=26;
const int ledpin=5;

void setup() {
  Serial.begin(115200);
  pinMode(ppin, INPUT);
  pinMode(ledpin, OUTPUT);
}

void loop() {
  int value = analogRead(ppin);
  float voltage=(6.0*value/4096.0);
  analogWrite(ledpin,value);
  Serial.print("potentiometer:");
  Serial.print(value);
  Serial.print("| voltage:");
  Serial.println(voltage);

  delay(500);
}
