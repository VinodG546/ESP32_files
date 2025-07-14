#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,2);  

void setup()
{
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("lcd project");
  lcd.setCursor(0,1);
  lcd.print("ESP32 programming");
  
}


void loop()
{
}