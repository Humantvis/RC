/*
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp32/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/
#include <esp_now.h>
#include <WiFi.h>

#define ANALOG_X_PIN 36
#define ANALOG_Y_PIN 39
#define ANALOG_BUTTON_PIN 32

//Default values when axis not actioned
#define ANALOG_X_CORRECTION 128
#define ANALOG_Y_CORRECTION 128

// Receiver MAC
uint8_t broadcastAddress[] = {0xA4, 0xCF, 0x12, 0x44, 0xd9, 0x58};

// Variables to send
float x;
float y;

// Variable to store if sending data was successful
//String success;

//Must match the receiver structure
typedef struct struct_message {
    float x;
    float y;
    bool button;
} struct_message;

struct_message joystickReadings;

esp_now_peer_info_t peerInfo;
 
void setup() {
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  esp_now_init();
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  esp_now_add_peer(&peerInfo);

  pinMode(ANALOG_BUTTON_PIN, INPUT_PULLUP);
}
 
void loop() {
  joystickReadings.button = !digitalRead(ANALOG_BUTTON_PIN);
	joystickReadings.x = readAnalogAxisLevel(ANALOG_X_PIN) - ANALOG_X_CORRECTION;
	joystickReadings.y = readAnalogAxisLevel(ANALOG_Y_PIN) - ANALOG_Y_CORRECTION;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &joystickReadings, sizeof(joystickReadings));
}

byte readAnalogAxisLevel(int pin) {
	 return map(analogRead(pin), 0, 4095, 0, 255);
}