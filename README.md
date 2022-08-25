<div align="center">

# Wake on Lan 🤖 ESP32 Telegram Bot

An embedded telegram bot for M5Atom to send a WOL packet on the local network to power on a PC.

![Wake-on-Lan Telegram Bot](https://user-images.githubusercontent.com/6751621/186768682-c2f93451-0ac0-4df5-b549-1c00f8fbc918.png)

</div>

## ⚡Installation
- Install the missing libraries
- Create a new Telegram bot and fill your `BOT_TOKEN` and `ALLOWED_ID`  
  _You can use @Botfather to create a new bot and @userinfobot to get your ID_
- Fill your WiFi configuration and the MAC address of the PC you want to power on
- Compile and flash

## 📄 Usage

- Use the `/wol` command to turn on your PC
- Use the `/ping` command to check if the bot is online
