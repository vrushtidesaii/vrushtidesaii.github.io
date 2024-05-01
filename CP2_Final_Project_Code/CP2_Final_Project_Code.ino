#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT22 // Change this to match your DHT sensor type

DHT dht(DHTPIN, DHTTYPE);

const int potPin = A0;
const int fanPin = 3; // Connect the fan to this pin
const int trigPin = 8; 
const int echoPin = 7; 
const int ledPin = 11; 
const int ledPin2 = 12; 
const int ledPin3 = 13; 
long duration;
int distance;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address and dimensions

void setup() {
  Serial.begin(9600);
  
  dht.begin();
  pinMode(fanPin, OUTPUT);
  lcd.init();         // Initialize the LCD
  lcd.backlight();    // Turn on the backlight
  
  Serial.println("LCD initialized successfully.");
  
  lcd.setCursor(0, 0);
  lcd.print("Temp/Humidity Fan");
  lcd.setCursor(0, 1);
  lcd.print("Vrushti Desai");
  delay(2000);
  lcd.clear();

 //ultrasonic+bulb
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
pinMode(ledPin, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
}

void loop() {
  int thresholdTemp = map(analogRead(potPin), 0, 1023, 20, 40); // Map potentiometer value to temperature range

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Failed to read DHT");
    lcd.setCursor(0, 1);
    lcd.print("sensor!");
    Serial.println("Failed to read DHT sensor!");
    delay(2000);
    return;
  }

  int thresholdHumidity = 20; // Adjust this threshold as needed

  if (temperature > thresholdTemp || humidity > thresholdHumidity) {
    // digitalWrite(fanPin, HIGH); // Turn on the fan
        digitalWrite(ledPin, HIGH);
    Serial.println("Fan turned ON.");
  } else {
        digitalWrite(ledPin, LOW);
    // digitalWrite(fanPin, LOW); // Turn off the fan
    Serial.println("Fan turned OFF.");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("C  Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(1000);

//ultrasonic+light
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  

  Serial.print("Distance: ");
  Serial.println(distance);

  // If distance is less than 20 cm, turn on the LED, otherwise turn it off
  if (distance < 10) {

    // digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else {
    // digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }
  

}


