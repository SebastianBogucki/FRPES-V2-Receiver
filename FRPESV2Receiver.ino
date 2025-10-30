#include <SPI.h>
#include <LoRa.h>
#include <Wire.h> 

char dataPackage;

int buzzer = 3;
int led1 = 4;
int led2 = 5;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setCodingRate4(8);
  LoRa.setSignalBandwidth(62.5E3);
  LoRa.enableCrc();
  LoRa.setSpreadingFactor(12);
  LoRa.setTxPower(10);
  Serial.println("LoRa has successfully started.");

  tone(3, 800);
  delay(200);
  noTone(3);
  delay(200);
  tone(3, 800);
  delay(200);
  noTone(3);
}

void loop() {
  // int i = 200;
  // for(i=200; i<900; i++){
  //   tone(3, i);
  //   delay(3);
  // }  
  // for(i=899; i>200; i--){
  //   tone(3, i);
  //   delay(3);
  // } 

  // delay(50);
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
      if(LoRa.packetRssi() > -50){
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
      }
      else{
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
      }
    }
    //Serial.print(", RSSI: ");
    //Serial.println(LoRa.packetRssi());

    tone(3, 800);
    delay(200);
    noTone(3);
  }
}
