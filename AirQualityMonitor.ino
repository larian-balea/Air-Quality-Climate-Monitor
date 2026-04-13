// 1. INCLUDE LIBRARIES
#include "DHT.h" // Brings in the DHT library we just downloaded

// 2. DEFINE PINS
// This tells the Arduino which wire is plugged into which pin.
#define DHTPIN 2       // DHT11 data pin is connected to D2
#define DHTTYPE DHT11  // Tells the library we are using a DHT11

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Gas Sensor Pin
const int mq135Pin = A0; // MQ-135 analog pin connected to A0

// Air Quality LEDs (Group 1)
const int airGreen = 10;
const int airYellow = 9;
const int airRed = 8;

// Humidity LEDs (Group 2)
const int humGreen = 7;
const int humYellow = 6;
const int humRed = 5;

// Buzzer Pin
const int buzzerPin = 3;

// =======
//  SETUP
// =======
void setup() {
  // Start the "Serial Monitor" so we can read the sensor values on the laptop screen
  Serial.begin(9600); 
  
  // Start the DHT sensor
  dht.begin();

  // Tell the Arduino that all our LED and Buzzer pins are OUTPUTS (sending electricity out)
  pinMode(airGreen, OUTPUT);
  pinMode(airYellow, OUTPUT);
  pinMode(airRed, OUTPUT);
  
  pinMode(humGreen, OUTPUT);
  pinMode(humYellow, OUTPUT);
  pinMode(humRed, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT);

  // A quick startup beep so you know it turned on successfully!
  digitalWrite(buzzerPin, HIGH);
  delay(200); // wait 200 milliseconds
  digitalWrite(buzzerPin, LOW);
  
  Serial.println("System Initialized! Warming up sensors...");
  delay(2000); // Give the sensors 2 seconds to warm up before the loop starts
}

// ======
//  LOOP
// ======
void loop() {
  // 1. READ THE SENSORS
  int airQualityValue = analogRead(mq135Pin); // Reads a number from 0 to 1023
  float humidityValue = dht.readHumidity();   // Reads the humidity percentage

  // If the DHT11 fails to read properly, print an error and try again
  if (isnan(humidityValue)) {
    Serial.println("Error reading from DHT sensor!");
    return; // skips the rest of the loop and starts over
  }

  // Print the exact numbers to the computer screen so you can see what is happening
  Serial.print("Air Quality: ");
  Serial.print(airQualityValue);
  Serial.print(" | Humidity: ");
  Serial.print(humidityValue);
  Serial.println("%");

  // 2. AIR QUALITY LOGIC (Using the thresholds we defined)
  if (airQualityValue < 300) {
    // GOOD AIR: Turn Green ON, others OFF
    digitalWrite(airGreen, HIGH);
    digitalWrite(airYellow, LOW);
    digitalWrite(airRed, LOW);
  } 
  else if (airQualityValue >= 300 && airQualityValue <= 700) {
    // WARNING AIR: Turn Yellow ON, others OFF
    digitalWrite(airGreen, LOW);
    digitalWrite(airYellow, HIGH);
    digitalWrite(airRed, LOW);
  } 
  else {
    // DANGER AIR: Turn Red ON, others OFF
    digitalWrite(airGreen, LOW);
    digitalWrite(airYellow, LOW);
    digitalWrite(airRed, HIGH);
  }

  // 3. HUMIDITY LOGIC
  if (humidityValue >= 40 && humidityValue <= 60) {
    // OPTIMAL HUMIDITY: Turn Green ON
    digitalWrite(humGreen, HIGH);
    digitalWrite(humYellow, LOW);
    digitalWrite(humRed, LOW);
  } 
  else if ((humidityValue > 60 && humidityValue <= 80) || (humidityValue >= 20 && humidityValue < 40)) {
    // HIGH/LOW HUMIDITY WARNING: Turn Yellow ON
    digitalWrite(humGreen, LOW);
    digitalWrite(humYellow, HIGH);
    digitalWrite(humRed, LOW);
  } 
  else {
    // EXTREME HUMIDITY DANGER: Turn Red ON
    digitalWrite(humGreen, LOW);
    digitalWrite(humYellow, LOW);
    digitalWrite(humRed, HIGH);
  }

  // 4. BUZZER ALARM LOGIC
  // If EITHER the air is dangerous OR the humidity is extreme, sound the alarm!
  if (airQualityValue > 700 || humidityValue < 20 || humidityValue > 80) {
    digitalWrite(buzzerPin, HIGH); // Turn buzzer ON
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn buzzer OFF
  }

  // 5. PAUSE
  // The DHT11 is a slow sensor. It requires at least 2 seconds between readings.
  delay(2000); // Wait 2000 milliseconds (2 seconds) before repeating the loop
}