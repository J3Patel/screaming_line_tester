#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

const byte address[6] = "00001";
const int buttonPin = 3;     // the number of the pushbutton pin
int buttonState = 0;    
const int led = 5;
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(led, OUTPUT);
   Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {
  int payload = 0;
  buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      payload = 0;
      digitalWrite(led, LOW);
    } else {
      payload = 1;
      digitalWrite(led, HIGH);
    }
    
  radio.writeFast(&payload, sizeof(payload));
  delay(2);
}
