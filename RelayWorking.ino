#include <RTClib.h>

RTC_DS3231 rtc;

const int RELAY_1 = 41;
const int RELAY_2 = 42;
const unsigned long RELAY_1_ON_TIME = 300; // 5 minutes in seconds
const unsigned long RELAY_2_ON_TIME = 180; // 3 minutes in seconds
unsigned long lastRelay1OnTime = 0;
unsigned long lastRelay2OnTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_1, OUTPUT);
  digitalWrite(RELAY_1, LOW); // turn off relay 1

  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_2, LOW); // turn off relay 2

  rtc.begin();
}

void loop() {
   if (Serial.available()) {
    // Read the incoming data from the Bluetooth module
    char incomingData = Serial.read();
    
    // If the incoming data is '1', turn on relay 1
    if (incomingData == '1') {
      digitalWrite(RELAY_1, HIGH);
      lastRelay1OnTime = rtc.now().unixtime(); // store the current time in seconds
      Serial.println("Relay 1 turned on");
    }
    // If the incoming data is '2', turn off relay 1
    else if (incomingData == '2') {
      digitalWrite(RELAY_1, LOW);
      Serial.println("Relay 1 turned off");
    }
    // If the incoming data is '3', turn on relay 2
    else if (incomingData == '3') {
      digitalWrite(RELAY_2, HIGH);
      lastRelay2OnTime = rtc.now().unixtime(); // store the current time in seconds
      Serial.println("Relay 2 turned on");
    }
    // If the incoming data is '4', turn off relay 2
    else if (incomingData == '4') {
      digitalWrite(RELAY_2, LOW);
      Serial.println("Relay 2 turned off");
    }
  }
  DateTime now = rtc.now();
  if(digitalRead(RELAY_1) == HIGH){
    unsigned long elapsedSeconds = now.unixtime() - lastRelay1OnTime; // calculate the elapsed time since the relay was turned on
    if (elapsedSeconds >= RELAY_1_ON_TIME) {
      digitalWrite(RELAY_1, LOW); // turn off relay 1
      Serial.println("Relay 1 turned OFF");
    }
    else {
      unsigned long remainingSeconds = RELAY_1_ON_TIME - elapsedSeconds; // calculate the remaining time
      Serial.print("Time remaining for Relay 1: ");
      Serial.print(remainingSeconds);
      Serial.println(" seconds");
    }
  }
  if(digitalRead(RELAY_2) == HIGH){
    unsigned long elapsedSeconds = now.unixtime() - lastRelay2OnTime; // calculate the elapsed time since the relay was turned on
    if (elapsedSeconds >= RELAY_2_ON_TIME) {
      digitalWrite(RELAY_2, LOW); // turn off relay 2
      Serial.println("Relay 2 turned OFF");
    }
    else {
      unsigned long remainingSeconds = RELAY_2_ON_TIME - elapsedSeconds; // calculate the remaining time
      Serial.print("Time remaining for Relay 2: ");
      Serial.print(remainingSeconds);
      Serial.println(" seconds");
    }
  }
  delay(1000);
}
