#include <Arduino.h>
#include <LiquidCrystal.h>
#define LedGreen 1
#define LedBlue 2
#define LedRed 3
#define buttonUp    11
#define buttonDown  13
#define buttonOK  12
#define wentylator 10
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
int menu=1;
bool psButtonUp = LOW;
bool psButtonDown = LOW;
float temperature;

void lcdClear(void);

void changeMenu(void){
  if(digitalRead(buttonUp) == HIGH && psButtonUp == LOW){
    psButtonUp = HIGH;
    menu=menu+1;
    if(menu>3){
      menu=1;
    }
    lcd.clear();
  }
  if(digitalRead(buttonDown) == HIGH && psButtonDown == LOW) {
    psButtonDown = HIGH;
    menu=menu-1;
    if(menu<1){
      menu=3;
    }
    lcd.clear();
  }
  psButtonUp = digitalRead(buttonUp);
  psButtonDown = digitalRead(buttonDown);
}

void setup(void){
  lcd.begin(16, 2);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonOK, INPUT_PULLUP);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(LedBlue, OUTPUT);
  pinMode(wentylator,OUTPUT);
  analogWrite(wentylator,0);
}

void loop(void) {
  dispMenu();
  changeMenu();
  readTemperature();
  changeRGBLed();
  runFUN();
}
void changeRGBLed(void){
  float change = (temperature + 40.0f) * 255.0f / (125.0f + 40.0f);
  analogWrite(LedRed, 0+change);
  analogWrite(LedGreen, 0);
  analogWrite(LedBlue, 255+change);
}
  
void readTemperature(void){
  unsigned int digital = analogRead(A5);
  float resolution = (5.0f / 1024.0f);
  float voltage = resolution * digital;
  temperature = (voltage-0.1f) * (125.0f+40.0f) / (1.75f-0.1f) - 40.0f;
}

void runFUN(void){
if(temperature>40)
{
  analogWrite(wentylator, 255);
}
}

void dispMenu(void){
  switch(menu){
  case 1:
    lcd.setCursor(0,0);
    lcd.print("Temperatura:");
    lcd.setCursor(0,1);
    lcd.print(temperature);
    break;
  case 2:
    lcd.setCursor(0,0);
    lcd.print("Menu 2");
    break;
  case 3:
    lcd.setCursor(0,0);
    lcd.print("Menu 3");
    break;
  }
}