#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ThingSpeak.h>

// Define DHT11 pin
#define DHTPIN D5    
#define DHTTYPE DHT11 

// Define MQ2 pin
#define MQ2PIN A0

// WiFi credentials
const char* ssid = "Project";
const char* password = "22222222";

// ThingSpeak credentials
unsigned long myChannelNumber = 2702698;
const char* myWriteAPIKey = "HLNUYID3RK5VD3NL";

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize LCD (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// WiFi and ThingSpeak variables
WiFiClient client;

void setup() {
  // Start serial communication
  Serial.begin(9600);
  Wire.begin(2,0);

  // Initialize DHT11
  dht.begin();
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initialized");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read data from sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  //CO2 and acetone value
  int mq2_value = analogRead(MQ2PIN);
  //mq2_value = mq2_value*100;
  
    Serial.print("Temp:");
    Serial.println(temperature);
    Serial.print("Hum:");
    Serial.println(humidity);
    Serial.print("Gas:");
    Serial.println(mq2_value);

  // Display data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(mq2_value);
  lcd.print("PPM");

  // Prepare data for ThingSpeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, mq2_value);
  // Send data to ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  delay(1500);  // Upload every 15 seconds
}
