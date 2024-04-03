

/**
 * @file Untitled-1
 * @brief This file contains the code for an Arduino project that uses the UniversalTelegramBot library to create a Telegram bot.
 * The bot can control an LED and read sensor data such as temperature, humidity, and light level.
 * It connects to a WiFi network and communicates with the Telegram API to send and receive messages.
 * 
 * @note This code requires the following libraries: WiFi, WiFiClientSecure, UniversalTelegramBot, and DHT.
 * 
 * @note Before running the code, make sure to set the WiFi SSID, password, and Telegram bot token.
 * 
 * @note The code assumes that the LED is connected to pin 4, the DHT sensor is connected to pin 14, and the LDR sensor is connected to pin 27.
 * 
 * @note The code uses the DHT11 sensor, but you can change the DHT_TYPE constant to DHT21 or DHT22 if you are using a different sensor.
 * 
 * @note The code also requires a root certificate for api.telegram.org. Make sure to add the certificate using the setCACert() function.
 * 
 * @note The handleNewMessages() function handles incoming messages from the Telegram bot and performs the corresponding actions based on the message content.
 * 
 * @note The setup() function initializes the serial communication, sensors, pins, and connects to the WiFi network.
 * 
 * @note The loop() function continuously checks for new messages from the Telegram bot and calls the handleNewMessages() function to process them.
 */
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>




// Wifi network station credentials
#define WIFI_SSID "******************"
#define WIFI_PASSWORD "***********+"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "*************************"


#include <DHT.h> // Biblioteca para el sensor DHT


// Definiciones de los pines para los sensores
#define DHT_PIN 14 // Pin al que está conectado el sensor DHT
#define DHT_TYPE DHT11 // Tipo de sensor DHT (DHT11, DHT21, DHT22)
const int LDR_PIN =27; // Pin del sensor LDR

const int LED_RED = 2;
const int LED_GREEN = 4;


DHT dht(DHT_PIN, DHT_TYPE); // Inicialización del sensor DHT


const unsigned long BOT_MTBS = 1000;  // mean time between scan messages
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;  // last time messages' scan has been done
//const int ledPin = 27;
int ledStatus = 0;




void handleNewMessages(int numNewMessages) {
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

      if (text == "/start") {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/ledon : to switch the Led ON\n";
      welcome += "/ledoff : to switch the Led OFF\n";
      welcome += "/status : Returns current status of LED\n";
      welcome += "/sensores : Returns current status of sonsor\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }

    if (text == "/ledon") {
      digitalWrite(LED_GREEN, HIGH);  // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led is ON", "");
    }
    if (text == "/ledoff") {
      ledStatus = 0;
      digitalWrite(LED_GREEN, LOW);  // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led is OFF", "");
    }
    if (text == "/status") {
      if (ledStatus) {
        bot.sendMessage(chat_id, "Led is ON", "");
      } else {
        bot.sendMessage(chat_id, "Led is OFF", "");
      }
    }
    

    if (text == "/sensores") {
        String sensorData = "Datos de los sensores:\n";
        // Lectura de temperatura y humedad
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();
        if (!isnan(temperature) && !isnan(humidity)) {
            digitalWrite(LED_GREEN, HIGH);
            sensorData += "Temperatura: " + String(temperature) + "°C\n";
            sensorData += "Humedad: " + String(humidity) + "%\n";
            delay(1000);
            digitalWrite(LED_GREEN, LOW);
        } else {
            sensorData += "Error al leer la temperatura y humedad\n";
            digitalWrite(LED_RED, HIGH);
            delay(1000);
            digitalWrite(LED_RED, LOW);
        }
        // Lectura de luz
        float lightLevel = analogRead(LDR_PIN);
        Serial.println(lightLevel);
        if (!isnan(lightLevel)) {
            sensorData += "Nivel de luz: " + String(lightLevel) + " lx\n";
            digitalWrite(LED_GREEN, HIGH);
            delay(1000);
            digitalWrite(LED_GREEN, LOW);
        } else {
            sensorData += "Error al leer el nivel de luz\n";
            digitalWrite(LED_RED, HIGH);
            delay(1000);
            digitalWrite(LED_RED, LOW);
        }
        bot.sendMessage(chat_id, sensorData, "");
    }
  }
}


void setup() {
  Serial.begin(115200);
  Serial.println();
  dht.begin();
  //pinMode(ledPin, OUTPUT);  // initialize digital ledPin as an output.

  //verificar sensores
//

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  delay(10);
  //digitalWrite(ledPin, HIGH);  // initialize pin as off (active LOW)
  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}
void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}



// end of code.
