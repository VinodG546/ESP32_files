#include<ESP32Servo.h>

int servopin=18;

servo servo1;

void setup() {
  servo1.attach(servopin,500,2400);
}

void loop() {
  int pos=0;
  for ( pos=0;pos<=180;pos+=1){
    servo1.write(pos);
    delay(10);
  }

  for(pos =180;pos>=0;pos-=1){
    servo1.write(pos);
    delay(10);
  }

}
