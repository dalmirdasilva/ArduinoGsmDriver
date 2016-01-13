#include <Arduino.h>
#include <SIM900.h>
#include <GprsSIM900.h>

SIM900 sim = SIM900(2, 3, 5, 6);
GprsSIM900 gprs = GprsSIM900(&sim);
unsigned char ip[4];

void setup() {
    Serial.begin(19200);
    Serial.println("Setup initiated...");
    if (!gprs.begin(19200)) {
        Serial.println("Cannot initialize shield");
        return;
    }
    unsigned char op;


    op = gprs.useMultiplexer(false);
    Serial.print("useMultiplexer: ");
    Serial.println(op);
    Serial.println("getLastResponse: ");
    Serial.println((const char*) sim.getLastResponse());

    op = gprs.attach((const char *) "tim.br", (const char *) "tim", (const char *) "tim");
    Serial.print("attach: ");
    Serial.println(op);
    Serial.println("getLastResponse: ");
    Serial.println((const char*) sim.getLastResponse());

    op = gprs.bringUp();
    Serial.print("bringUp: ");
    Serial.println(op);
    Serial.println("getLastResponse: ");
    Serial.println((const char*) sim.getLastResponse());
    Serial.println("Done");

    op = gprs.configureDns("8.8.8.8", "8.8.4.4");
    Serial.print("configureDns: ");
    Serial.println(op);
    Serial.println("getLastResponse: ");
    Serial.println((const char*) sim.getLastResponse());
    Serial.println("Done");

    op = gprs.obtainIp(ip);
    Serial.println(op);
    Serial.println("getLastResponse: ");
    Serial.println((const char*) sim.getLastResponse());
    Serial.println("---");
    Serial.print(ip[0], DEC);
    Serial.print(".");
    Serial.print(ip[1], DEC);
    Serial.print(".");
    Serial.print(ip[2], DEC);
    Serial.print(".");
    Serial.println(ip[3], DEC);


}

void loop() {
}

int main(void) {
    init();
#if defined(USBCON)
    USBDevice.attach();
#endif
    setup();
    for (;;) {
        loop();
        if (serialEventRun) {
            serialEventRun();
        }
    }
    return 0;
}
