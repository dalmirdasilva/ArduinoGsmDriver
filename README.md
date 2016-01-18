# Arduino Gsm Driver

[Documentation.pdf](Documentation.pdf)

## Instalation

NOTE: Instalation will only make sym links from your cloned path to ~/Arduino/libraries folder.

```bash
$ git clone https://github.com/dalmirdasilva/ArduinoGsmDriver
$ make install
```


## Example of code for sending data through GPRS wireless network.

```cpp

    #include <Arduino.h>
    #include <SoftwareSerial.h>
    #include <SIM900.h>
    #include <Gprs.h>
    #include <GprsSIM900.h>
    
    SIM900 sim = SIM900(2, 3, 5, 6);
    GprsSIM900 gprs = GprsSIM900(&sim);
    unsigned char ip[4];
    
    void setup() {
        Serial.begin(19200);
        Serial.println(F("Setup initiated..."));
        if (!gprs.begin(19200)) {
            Serial.println(F("Cannot initialize shield"));
            return;
        }
        unsigned char op;
    
        op = gprs.shutdown();
        if (op != GprsSIM900::OK) {
            Serial.println("Cannot shutdown.");
            return;
        }
    
        op = gprs.useMultiplexer(false);
        if (op != GprsSIM900::OK) {
            Serial.println("Cannot set multiplex.");
            return;
        }
    
        op = gprs.attach("tim.br", "tim", "tim");
        if (op != GprsSIM900::OK) {
            Serial.println("Cannot attach.");
            return;
        }
    
        do {
            op = gprs.status();
            Serial.print("Waiting IP_START status: ");
            Serial.println(op);
        } while(op != GprsSIM900::IP_START);
        
        op = gprs.bringUp();
        if (op != GprsSIM900::OK) {
            Serial.println("Cannot bring it up.");
            return;
        }
    
        op = gprs.obtainIp(ip);
        if (op != GprsSIM900::OK) {
            Serial.println("Cannot obtain ip.");
            return;
        }
    
        op = gprs.configureDns("8.8.8.8", "8.8.4.4");
        if (op != GprsSIM900::OK) {
            Serial.println("Cannot configure dns.");
            return;
        }
    
        unsigned char d[256] = { 1 };
        GprsSIM900::TransmittingState transmittingState;
    
        for (int i = 0; i < 5; i++) {
    
            op = gprs.status();
            if (op != GprsSIM900::IP_STATUS && op != GprsSIM900::IP_INITIAL && op != GprsSIM900::CLOSED) {
                Serial.println("Status is different from IP_STATUS or IP_INITIAL or CLOSED.");
                return;
            }
    
            op = gprs.open("TCP", "www.dalmirdasilva.com", 3000);
            if (op != GprsSIM900::OK) {
                Serial.println("Cannot open.");
                return;
            }
            d[0] = '0' + i;
            op = gprs.send((unsigned char *) d, 256);
            if (op != GprsSIM900::OK) {
                Serial.println("Cannot send.");
                return;
            }
    
            do {
                gprs.transmittingState(&transmittingState);
                Serial.print("sent: ");
                Serial.print(transmittingState.txlen);
            } while (transmittingState.txlen != 256);
    
            op = gprs.close();
            if (op != GprsSIM900::OK) {
                Serial.println("Cannot close. Possibly it is already closed.");
            }
        }
    }
    
    void loop() {
        while (sim.available()) {
            Serial.write(sim.read());
        }
        while (Serial.available()) {
            unsigned char c = Serial.read();
            switch(c) {
                case '0':
                    gprs.status();
                    Serial.println((const char *) sim.getLastResponse());
                    break;
                case '1':
                    gprs.attach("tim.br", "tim", "tim");
                    Serial.println((const char *) sim.getLastResponse());
                    break;
                case '2':
                    gprs.bringUp();
                    Serial.println((const char *) sim.getLastResponse());
                    break;
                default:
                    sim.write(c);
            }
        }
    }

```

