#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(3,4);
const int ledPin =  5; 
const int spk =  7; 
const int buzzer = 2;
const byte address[6] = "00001";
unsigned long lastMills = 0;
const long interval = 20;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
    pinMode(ledPin, OUTPUT);
    pinMode(spk, OUTPUT);
  pinMode(buzzer, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  lastMills = millis();
}

void loop() {
  int payload = 0;
  
  
  if (radio.available()) {
    radio.read(&payload, sizeof(payload));
    
      if (payload == 0) {
         unsigned long current = millis();
         if (current - lastMills >= interval) {
            lastMills = current;
            digitalWrite(ledPin, LOW);
            digitalWrite(spk, LOW);
            Serial.println("LOW");
         }
      } else {
        unsigned long current = millis();
        lastMills = current;
        digitalWrite(ledPin, HIGH);
        digitalWrite(spk, HIGH);
        Serial.println("HIGH");
      }   
    
  }
}
