# RC

This project implements a **Wi-Fi–based remote-controlled car** using two ESP32 boards:

- **Controller ESP32** – reads joystick/switch inputs and sends commands  
- **Car ESP32** – receives commands and drives the motors, piezo buzzer and LEDs

The code is based on examples from Random Nerd Tutorials on how to connect two ESP32s toether usingg esp now, but has been extended and customized for a complete RC car system.

### 🚗 Car (Receiver)
- Receives control packets via Wi-Fi  
- PWM motor control (forward, reverse, turning)  
- LED on/off control  
- Configurable pin layout for your motor driver  

### 🎮 Controller (Transmitter)
- Reads joystick analog values  
- Maps inputs to 0–255 motion values  
- Sends movement + LED status to the car  
- button for horn and LEDs
