#include <SoftwareSerial.h>
#include <SIM900.h>
#include <Gprs.h>
#include <GprsSIM900.h>

SIM900 sim(2, 3);
GprsSIM900 gprs(&sim);

void setup() {
  unsigned char op;
  Serial.begin(9600);
  Serial.println("Setup initiated...");
  gprs.begin(19200);
  op = gprs.attach("zap.vivo.com.br", "vivo","vivo");
  op = gprs.bringUp();
  op = gprs.configureDns("8.8.8.8", "8.8.4.4");
  Serial.println("Done");
}

void loop() {
  delay(1000);
}
