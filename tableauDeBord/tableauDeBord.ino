#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 6
#define DHTTYPE DHT11
#define MOTORPIN 7
#define ECHOPIN 12
#define TRIGPIN 13


float temp;
float hum;
long duration;
int dist;
int lum;
int led_pins[4] = {8,9,10,11};


DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

void setup()
{
  pinMode(MOTORPIN, OUTPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  lcd.begin(16, 2);
  dht.begin();
}

void loop()
{
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  lum = analogRead(A0);

    // Temperature
  if (10 < temp && temp < 18) {
  	digitalWrite(led_pins[1], HIGH);
    digitalWrite(led_pins[0], LOW);
  } else if (18 < temp && temp < 22){
  	digitalWrite(led_pins[0], HIGH);
    digitalWrite(led_pins[1], LOW);
  } else if (temp > 22){
  	digitalWrite(led_pins[0], LOW);
    digitalWrite(led_pins[1], LOW);
    analogWrite(MOTORPIN, 255);
  }

      // Humidité
  if (hum < 50) {
  	digitalWrite(led_pins[2], HIGH);
    digitalWrite(led_pins[3], LOW);
  } else {
  	digitalWrite(led_pins[3], HIGH);
    digitalWrite(led_pins[2], LOW);
  }

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

  lcd.setCursor(0, 0);
  lcd.println("Lumiere "+ String(lum)+"  ");
  lcd.setCursor(0, 1);
  lcd.println("Distance "+ String(dist)+" ");
  delay(10);
}