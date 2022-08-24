#include "M5Atom.h"
#include "WiFiMulti.h"
#include "WiFiClientSecure.h"
#include "WiFiUDP.h"

#include "WakeOnLan.h"
#include "UniversalTelegramBot.h"
#include "ArduinoJson.h"

// LED Colors
#define WHITE  0xFFFFFF
#define RED    0x800000
#define GREEN  0x008000
#define PURPLE 0x800080
#define AMBER  0xFF4000
#define OFF    0x000000

// Telegram Bot Token
#define BOT_TOKEN  "0000000000:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define ALLOWED_ID "000000000"

// WiFi configuration
#define WIFI_SSID ""
#define WIFI_PASS ""

// MAC address of the target device
#define MAC_ADDR "FF:FF:FF:FF:FF:FF"


WiFiMulti wifiMulti;
WiFiClientSecure secured_client;
WiFiUDP UDP;
WakeOnLan WOL(UDP);

const unsigned long BOT_MTBS = 1000; // mean time between scan messages
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done


void sendWOL() {
  M5.dis.drawpix(0, WHITE);
  WOL.sendMagicPacket(MAC_ADDR); // send WOL on default port (9)
  delay(300);
  M5.dis.drawpix(0, AMBER);
}


void handleNewMessages(int numNewMessages) {
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    Serial.println(bot.messages[i].from_id);
    if (bot.messages[i].from_id != ALLOWED_ID) continue;
    
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/wol") {
      sendWOL();
      bot.sendMessage(chat_id, "Magic Packet sent!", "");
    } else if (text == "/ledon") {
      M5.dis.drawpix(0, AMBER); // turn the LED on
      bot.sendMessage(chat_id, "Led is ON.", "");
    } else if (text == "/ledoff") {
      M5.dis.drawpix(0, OFF); // turn the LED off)
      bot.sendMessage(chat_id, "Led is OFF.", "");
    } else if (text == "/ping") {
      bot.sendMessage(chat_id, "Pong.", "");
    } else if (text == "/start") {
      String welcome = "Welcome to **WoL Bot**, " + from_name + ".\n";
      welcome += "Use is restricted to the bot owner.\n\n";
      welcome += "/ledon : Switch the Led ON\n";
      welcome += "/ledoff : Switch the Led OFF\n";
      welcome += "/wol : Send the Magic Packet\n";
      welcome += "/ping : Check the bot status\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


/* =================================== SETUP =================================== */

void setup(){
  // Configure WiFI
  wifiMulti.addAP(WIFI_SSID, WIFI_PASS);
  // Clear the serial port buffer and set the serial port baud rate to 115200.
  // Do not Initialize I2C. Initialize the LED matrix.
  M5.begin(true, false, true); delay(25);
    
  M5.dis.drawpix(0, RED); delay(100);

  // Add root certificate for api.telegram.org
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  Serial.print("Connecting to WiFI...");
  while ((wifiMulti.run() != WL_CONNECTED)) { // wait for WiFi connection.
    delay(500);
    Serial.print(".");
  }
  Serial.println("OK");

  // Attention: 255.255.255.255 is denied in some networks
  WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask()); 

  M5.dis.drawpix(0, GREEN); delay(100);
    
  Serial.print("Retrieving time...");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(150);
    now = time(nullptr);
  }
  Serial.println(now);
  
  M5.dis.drawpix(0, AMBER); delay(100);
}


/* =================================== LOOP =================================== */

void loop() {
  // Send WoL on button press
  if (M5.Btn.wasPressed()) sendWOL();

  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("Response received");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }

  delay(10);
  M5.update();
}
