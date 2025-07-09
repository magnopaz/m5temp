#include <M5Stack.h>          // Include M5Stack library
#include <DHT.h>

// Define the DHT sensor type and data pin connection.
#define DHTPIN 21             // M5Stack GROVE Port A (Yellow Wire)
#define DHTTYPE DHT22         // DHT 22 (AM2302)

// Create a DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    M5.begin();                // Initialize the M5Stack Core
    Serial.begin(115200);      // Begin serial communication for debugging

    dht.begin();               // Initialize the DHT22 sensor

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("DHT22 Sensor");
    M5.Lcd.println("Initializing...");
    delay(2000);
}

void loop() {
    // Read temperature as Celsius and humidity from the sensor
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // Temperature in Celsius

    // Check if any reads failed.
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextColor(YELLOW, BLACK);
        M5.Lcd.drawCentreString("Failed to read sensor!", 160, 110, 4); // Font 4 (26px)
        delay(2000);
        return;
    }

    // Display the readings on the screen
    M5.Lcd.fillScreen(BLACK);
    char buffer[16];

    // --- Display Temperature ---
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.drawCentreString("Temperature", 160, 20, 4); // Font 4 (26px)
    M5.Lcd.setTextColor(ORANGE, BLACK);
    // Format string with one decimal place and the degree symbol (char 247)
    sprintf(buffer, "%.1f %cC", t, 247);
    M5.Lcd.drawCentreString(buffer, 160, 65, 7); // Font 7 (75px seven-segment)

    // --- Display Humidity ---
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.drawCentreString("Humidity", 160, 130, 4); // Font 4 (26px)
    M5.Lcd.setTextColor(CYAN, BLACK);
    sprintf(buffer, "%.1f %%", h);
    M5.Lcd.drawCentreString(buffer, 160, 175, 7); // Font 7 (75px seven-segment)

    delay(30000); // Update every 30 seconds
}