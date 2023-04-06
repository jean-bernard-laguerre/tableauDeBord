#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 6
#define DHTTYPE DHT11
#define MOTORPIN 7
#define ECHOPIN 12
#define TRIGPIN 13
#define BUTTONPIN A5
#define BUZZERPIN A2


float temp;
float hum;
long duration;
int status = 0;
int button_state;
int dist;
int lum;
int led_pins[4] = {8,9,10,11};

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

void setup()
{
  pinMode(MOTORPIN, OUTPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  lcd.begin(16, 2);
  dht.begin();
}

void loop()
{
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  lum = analogRead(A0);

  button_state = digitalRead(BUTTONPIN);
  
  if (button_state == HIGH) {
    
    if (status == 0) {
    	status = 1;
    }
    else {
    	status = 0;
    }
    delay(100);
  }

    // Temperature LED
  if (10 < temp && temp < 18) {
  	digitalWrite(led_pins[1], HIGH);
  } else if (18 < temp && temp < 22){
  	digitalWrite(led_pins[0], HIGH);
  } else if (temp > 22){
    analogWrite(MOTORPIN, 255);
  }

      // Humidité LED
  if (hum < 50) {
  	digitalWrite(led_pins[2], HIGH);
  } else {
  	digitalWrite(led_pins[3], HIGH);
  }
      
      //Distance
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHOPIN, HIGH);
    // Calculating the distance
  dist = duration * 0.034 / 2;

  if (dist < 20) {
      tone(BUZZERPIN, 500);
      delay(100);
      noTone(BUZZERPIN);
  }

  if (status == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Temp: "+ String(dht.readTemperature())+"       ");
      lcd.setCursor(0, 1);
      lcd.print("Hum: "+ String(dht.readHumidity())+"       ");
  }
  else {
      lcd.setCursor(0, 0);
      lcd.print("Lum: "+ String(lum)+"         ");
      lcd.setCursor(0, 1);
      lcd.print("Dist: "+ String(dist)+"         ");
  }
  
  delay(10);
}