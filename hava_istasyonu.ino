#include <Adafruit_BMP085.h>

#include <DHT.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;
int upButton = 10;
int downButton = 11;
int selectButton = 12;
int menu = 1;

void setup() {
  dht.begin();
  bmp.begin();
  lcd.init();
  lcd.backlight();
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  
  updateMenu();
}

void loop() {
  
  if (!digitalRead(downButton)){
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)){
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
}

void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">sicaklik:");
      lcd.setCursor(10,0);
      lcd.println();
      
      lcd.setCursor(0, 1);
      lcd.print("Nem");
      break;
    case 2: //readPressure(
      lcd.clear();
      lcd.print(" sicaklik");
      lcd.setCursor(0, 1);
      lcd.print(">Nem:");
      lcd.setCursor(7,1);
      //lcd.print(dht.readHumidity());
      break;
    case 3:
      lcd.clear();
      lcd.print(">Basinc:");
      lcd.setCursor(9,0);
      //lcd.print(c());
      lcd.setCursor(0, 1);
      lcd.print(" Rakim");
      break;
    case 4:
      lcd.clear();
      lcd.print(" Basinc");
      lcd.setCursor(0, 1);
      lcd.print(">Rakim");
      lcd.setCursor(7,1);
     // lcd.print(bmp.readAltitude());
      break;
    case 5:
      menu = 4;
      break;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
  }
}

void action1() {
  lcd.clear();
  lcd.home();
  lcd.print("bugunku sicaklik");
  lcd.setCursor(7,1);
  lcd.print(dht.readTemperature());
  delay(2000);
}
void action2() {
  lcd.clear();
  lcd.home();
  lcd.print("bugunku nem");
  lcd.setCursor(5,1);
  lcd.print(dht.readHumidity());
  delay(2000);
}
void action3() {
  lcd.clear();
  lcd.home();
  lcd.print("bugunku basinc");
  lcd.setCursor(5,1);
  lcd.print(bmp.readPressure());
  delay(1500);
}
void action4() {
  lcd.clear();
  lcd.home();
  lcd.print("bugunku rakim");
  lcd.setCursor(5,1);
  lcd.print(bmp.readAltitude());
  delay(1500);
}
