/*
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp32/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/
#include <esp_now.h>
#include <WiFi.h>

#define IN1 26
#define IN2 18
#define IN3 19
#define IN4 23
#define BEEP 25
#define LEDF 22
#define LEDB 21

// Define variables to store incoming readings
float x;
float y;
bool button;

bool ledSwitch;
bool canSwitch;

int xDirection;
int yDirection;

//Must match the sender structure
typedef struct struct_message {
    float x;
    float y;
    bool button;
} struct_message;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

esp_now_peer_info_t peerInfo;

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  x = incomingReadings.x;
  y = incomingReadings.y;
  button = incomingReadings.button;
}
 
void setup() {
  ledSwitch = false;
  canSwitch = true;

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(BEEP, OUTPUT);
  pinMode(LEDF, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // // Init Serial Monitor
  //Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
 
void loop() {
  //printData();

  // // For LEDs
  // if(canSwitch && button) {
  //   canSwitch = false;
  //   ledSwitch = !ledSwitch;
  // } else if (!button) {
  //   canSwitch = true;
  // }

  // if(ledSwitch) {
  //   digitalWrite(LEDF, HIGH);
  //   digitalWrite(LEDB, HIGH);
  // } else {
  //   digitalWrite(LEDF, LOW);
  //   digitalWrite(LEDF, LOW);
  // }

  if(button) {
    digitalWrite(BEEP, HIGH);
  } else {
    digitalWrite(BEEP, LOW);
  }

  if(x < -50) {
    xDirection = -1;
  } else if(x < 50) {
    xDirection = 0;
  } else {
    xDirection = 1;
  }

  if(y < -50) {
    yDirection = -1;
  } else if(y < 50) {
    yDirection = 0;
  } else {
    yDirection = 1;
  }


  if(xDirection == 0) {
    if(yDirection == 0) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    } else if (yDirection == 1) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
  } else if(xDirection == 1) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    if(yDirection == 1) {
      digitalWrite(IN3, LOW);
    } else if (yDirection == -1) {
      digitalWrite(IN1, LOW);
    }
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    if(yDirection == 1) {
      digitalWrite(IN4, LOW);
    } else if (yDirection == -1) {
      digitalWrite(IN2, LOW);
    }
  }
}

// void printData(){
//   // Display Readings in Serial Monitor
//   Serial.println("INCOMING READINGS");
//   Serial.print("x: ");
//   Serial.println(xDirection);
//   Serial.print("y: ");
//   Serial.println(yDirection);
//   Serial.print("button: ");
//   Serial.println(button);
//   Serial.println();
// }