#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int pirSensorPin = 2; 

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  pinMode(pirSensorPin, INPUT);
  
  lcd.init();            // initialize the LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("       PIR      ");
  lcd.setCursor(0, 1);
  lcd.print(" Motion Sensor  ");
  delay(3000);
  lcd.clear();

  Serial.begin(9600);
}

void loop() {
  int pirValue = digitalRead(pirSensorPin);
 
  if (pirValue == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Welcome home :)");
    Serial.println("Motion detected!");
  } 
  else 
  {   
    lcd.clear();
  }

  delay(1000);
}
