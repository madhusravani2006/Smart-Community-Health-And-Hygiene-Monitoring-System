#define BLYNK_TEMPLATE_ID "BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Demo"
#define BLYNK_AUTH_TOKEN "BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <ThingSpeak.h>

// DHT22
#define DHTPIN D5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ECG
#define ECG_PIN A0
#define ALERT_LED D6

// WiFi
char ssid[] = "WIFI_NAME";
char pass[] = "PASSWORD";

// ThingSpeak
unsigned long myChannelNumber = DEMO_CHANNEL_NAME;         
const char *myWriteAPIKey = "WRITE_API_KEY";   
WiFiClient client;

float temperature = 0;
float humidity = 0;
float heartRate = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(ALERT_LED, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Connected!");
  
 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  
  ThingSpeak.begin(client);
}

void loop() {
  Blynk.run();

 
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (!isnan(t)) temperature = t;
  if (!isnan(h)) humidity = h;

 
  int ecgValue = analogRead(ECG_PIN);
  heartRate = map(ecgValue, 0, 1023, 60, 120); // simple demo mapping

 
  if (ecgValue < 350 || ecgValue > 700) digitalWrite(ALERT_LED, HIGH);
  else digitalWrite(ALERT_LED, LOW);

 
  Blynk.virtualWrite(V0, temperature); 
  Blynk.virtualWrite(V1, humidity);      
  Blynk.virtualWrite(V2, heartRate);     
  Blynk.virtualWrite(V3, digitalRead(ALERT_LED));


  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, heartRate);
  ThingSpeak.setField(4, digitalRead(ALERT_LED));
  int response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (response == 200) Serial.println("ThingSpeak update successful.");
  else Serial.println("ThingSpeak update failed. Error code: " + String(response));

  delay(20000);
}
