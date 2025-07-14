void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(4, INPUT);

}
void loop() {
  int lightState=digitalRead(4 );
  int lightIntensity=analogRead(2);
 
  if (lightState == 1){
    Serial.println("no light dark ");
    Serial.print("intensity : ");
    Serial.println(lightIntensity);
  }else{
    Serial.println("bright light ");
    Serial.print("intensity : ");
    Serial.println(lightIntensity);
  }
  delay(1000);
}
