const int ledpin =16;

const int freq = 5000;
const int resolution = 8;
void setup() {
  ledcAttach(ledpin,freq,resolution);
}

void loop() {
  for(int dutycycle=0;dutycycle<=255;dutycycle++){
    ledcWrite(ledpin,dutycycle);
    delay(15);
  }
  for(int dutycycle=255;dutycycle>=0;dutycycle--){
    ledcWrite(ledpin,dutycycle);
    delay(15);
  }
}
