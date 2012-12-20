#include <SoftwareSerial.h>
#include <SIM900.h>
#include <Gprs.h>
#include <GprsSIM900.h>

SIM900 sim(2, 3);
GprsSIM900 gprs(&sim);

void setup() {
  Serial.begin(9600);
  Serial.println("Setup initiated...");
  gprs.begin(19200);
  unsigned char op;
  op = gprs.startTask(
           (unsigned char *)"zap.vivo.com.br",
           (unsigned char *)"vivo",
           (unsigned char *)"vivo");
  Serial.print("startTask: ");
  Serial.println(op);
  Serial.println("getLastResponse: ");
  Serial.println((const char*)sim.getLastResponse());
  op = gprs.bringUp();
  Serial.print("bringUp: ");
  Serial.println(op);
  Serial.println("getLastResponse: ");
  Serial.println((const char*)sim.getLastResponse());
  Serial.println("Done");
}

void loop() {
  unsigned char ip[4];
  unsigned char op;  
  op = gprs.obtainIp(ip);
  Serial.println(op);
  Serial.println("getLastResponse: ");
  Serial.println((const char*)sim.getLastResponse());
  Serial.println("---");
  Serial.print(ip[0], DEC);
  Serial.print(".");
  Serial.print(ip[1], DEC);
  Serial.print(".");
  Serial.print(ip[2], DEC);
  Serial.print(".");
  Serial.println(ip[3], DEC);
  delay(1000);
}