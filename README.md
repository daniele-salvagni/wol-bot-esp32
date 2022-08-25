<div align="center">

# Wake on Lan 🤖 ESP32 Telegram Bot

_An embedded telegram bot for M5Atom to send a WOL packet on the local network._  
_Blog post with more info: https://dan.salvagni.io/b/embedded-telegram-bot-for-wake-on-lan-pc/_

![Wake-on-Lan Telegram Bot](https://user-images.githubusercontent.com/6751621/186768682-c2f93451-0ac0-4df5-b549-1c00f8fbc918.png)

</div>

## 📄 Description
This is a sketch for the **M5Atom** ESP32 board. A telegram bot is hosted on the board and listens for messages, when the `/wol` command is received a Wake-on-Lan magic packet is broadcasted on the local network in order to turn on a target device.

🪙 You can keep it running for about **1$** in electricity per year, the power consumption is less than half a watt.

## ⚙️ Installation

- Install the following libraries from the Library Manager of the Arduino IDE:
  - [M5Atom](https://www.arduino.cc/reference/en/libraries/m5atom/): needed for the M5Atom board
  - [WakeOnLan](https://www.arduino.cc/reference/en/libraries/wakeonlan/): for sending the magic packet
  - [UniversalTelegramBot](https://www.arduino.cc/reference/en/libraries/universaltelegrambot/): for using the Telegram API
- Create a new Telegram bot and configure your `BOT_TOKEN` and `ALLOWED_ID`  
  _You can use [@Botfather](https://t.me/botfather) to create a new bot and [@userinfobot](https://t.me/userinfobot) to get your ID_
- Fill your _WiFi configuration_ and the _MAC address_ of the PC you want to power on
- Compile and flash

## 🔎 Usage

- Use `/start` to get a list of the available commands
- Use the `/wol` command or press the physical button to turn on your PC
- Use the `/ping` command to check if the bot is online
