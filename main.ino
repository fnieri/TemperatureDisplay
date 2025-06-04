#include <LiquidCrystal.h>
#include <dht11.h>

// DHT setup
#define DHTPIN 7
dht11 DHT;

//Display setup
//Pins
#define BACKLIGHT_PIN 5 //Replace LCD 15 + pin with digital to control backlight

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
//Lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//PIR setup
byte pinLed = 13;   
byte pinInput = 6;
bool valPIR = 0;

void setup() {
  Serial.begin(9600);
  setupLcd(); 
  setupPir(); 
}
 
void loop() {
    delay(5000);
    valPIR = digitalRead(pinInput);  
    if (valPIR) {
      digitalWrite(pinLed, HIGH);
      int chk = readDHT();
      float humidity = readHumidity(chk);
      float temp = readTemperature(chk);
      displayDHT(temp, humidity);
    }
    else
    {
        dimLCD();
    }
}

void setupLcd() {
  pinMode(BACKLIGHT_PIN, OUTPUT); //Set backlight pin to output to control HIGH OR LOW
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Pronto");
  }

void setupPir() {
  pinMode(pinLed, OUTPUT);   
  pinMode(pinInput, INPUT);   
}

int readDHT() {
  return DHT.read(DHTPIN);
}

float readHumidity(int chk) {
  return (float) DHT.humidity;
}

float readTemperature(int chk) {
  return (float) DHT.temperature;
}

void displayDHT(float temp, float humidity) {
    lcd.clear();
    lcd.setCursor(0,0);
    digitalWrite(BACKLIGHT_PIN, HIGH); 
    lcd.print("Temp (C): ");
    lcd.print(temp);
    lcd.setCursor(0,1);
    lcd.print("Umid (%): ");
    lcd.print(humidity);
}

void dimLCD() {
    digitalWrite(BACKLIGHT_PIN, LOW);
}
