#include <SoftwareSerial.h>

SoftwareSerial serial(2, 3);

void setup() {
  Serial.begin(9600);
  serial.begin(19200);
}

void loop() {
  
  if (serial.available()) {
    Serial.write(serial.read());
  }
  if (Serial.available()) {
    serial.write(Serial.read());
  }
}