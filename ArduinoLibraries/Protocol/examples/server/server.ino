#include<Protocol.h>

Protocol protocol = Protocol(2, 3);

uint8_t display(uint8_t * data, uint8_t length) {
  for (uint8_t index = 0; index < length; index++) {
    Serial.print(data[index], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void onReceived() {
  if (protocol.verifySum()) {
    display(protocol.buffer, Protocol::LENGTH);

    uint32_t key = 1234;
    uint8_t bytes[] = { key >> 24, key >> 16 , key >> 8 , key};

    protocol.buffer[0] = 0xAA;
    protocol.buffer[1] = 0x10;
    protocol.buffer[2] = 0x10;
    protocol.buffer[3] = bytes[0];
    protocol.buffer[4] = bytes[1];
    protocol.buffer[5] = bytes[2];
    protocol.buffer[6] = bytes[3];
    protocol.buffer[7] = protocol.generateSum();

    if (protocol.verifySum()) {
      display(protocol.buffer, Protocol::LENGTH);
      protocol.send();
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  protocol.setOnReceived(onReceived);
  protocol.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  protocol.run();
}
