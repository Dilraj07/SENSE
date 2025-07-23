#define BLYNK_TEMPLATE_ID "TMPL3c-iewHs6"
#define BLYNK_TEMPLATE_NAME "temperature and humidity monitor"
#define BLYNK_AUTH_TOKEN "Dn6Jkr7PS81u-YqHh39XPzMi5rQ4tlXq"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Aarush's S24+";
char pass[] = "@arush galaxy";

BlynkTimer timer;

// DHT11 Pins
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Sensor Pins
#define SMOKE_PIN 34
#define SOUND_PIN 35
#define PIR_PIN 32

// Thresholds
#define SMOKE_THRESHOLD 200       //  Smoke Threshold
#define SOUND_THRESHOLD_DB 60     // in dB

// Convert raw sound sensor value to approximate dB
float convertToDB(int rawValue) {
  // 2224 ~30dB, 4095 ~90dB
  return ((rawValue - 2224.0) * 60.0 / (4095.0 - 2224.0)) + 30.0;
}

void sendSensor() {
  // --- Temperature & Humidity ---
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) && !isnan(t)) {
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperature: "); Serial.print(t);
    Serial.print("°C  Humidity: "); Serial.println(h);
  }

  // --- Smoke Sensor with Air Quality Gradient ---
  int smokeValue = analogRead(SMOKE_PIN);
  Blynk.virtualWrite(V2, smokeValue);  // Normal smoke gauge

  // ✅ Smoke Alert LED based on threshold
  if (smokeValue > SMOKE_THRESHOLD) {
    Blynk.virtualWrite(V4, 1);
  } else {
    Blynk.virtualWrite(V4, 0);
  }

  // Smooth gradient mapping (0.2 = Green ~ Good, 1 = Red ~ Hazardous)
  float aqiGradient = 0.2 + (((smokeValue - 100) / 1023.0) * (1.0 - 0.2));
  if (aqiGradient < 0.2) aqiGradient = 0.2;
  if (aqiGradient > 1.0) aqiGradient = 1.0;
  Blynk.virtualWrite(V7, aqiGradient);

  // Air Quality Category (Text)
  String airQuality;
  if (smokeValue <= 200) airQuality = "Good";
  else if (smokeValue <= 400) airQuality = "Moderate";
  else if (smokeValue <= 600) airQuality = "Poor";
  else airQuality = "Hazardous";
  Blynk.virtualWrite(V8, airQuality);

  Serial.print("Smoke: "); Serial.print(smokeValue);
  Serial.print(" | Air Quality: "); Serial.print(airQuality);
  Serial.print(" | Gradient: "); Serial.println(aqiGradient);

  // --- Sound Sensor ---
  int soundRaw = analogRead(SOUND_PIN);
  float soundDB = convertToDB(soundRaw);

  Blynk.virtualWrite(V3, soundDB);  // Send dB value
  Serial.print("Sound Level (raw): "); Serial.print(soundRaw);
  Serial.print(" ~ "); Serial.print(soundDB); Serial.println(" dB");

  if (soundDB > SOUND_THRESHOLD_DB) {
    Blynk.virtualWrite(V5, 1);  // Virtual LED ON
  } else {
    Blynk.virtualWrite(V5, 0);  // Virtual LED OFF
  }

  // --- PIR Motion Sensor ---
  int motionDetected = digitalRead(PIR_PIN);
  if (motionDetected == HIGH) {
    Blynk.virtualWrite(V6, 1);  // Virtual LED ON
    Serial.println("Motion Detected!");
  } else {
    Blynk.virtualWrite(V6, 0);  // Virtual LED OFF
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  Blynk.begin(auth, ssid, pass);
  dht.begin();

  timer.setInterval(2000L, sendSensor); // every 2 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}
