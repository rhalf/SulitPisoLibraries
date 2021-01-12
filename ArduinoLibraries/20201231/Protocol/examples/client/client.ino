#include<Protocol.h>
Protocol protocol = Protocol(2, 3);

void display(uint8_t * data, uint8_t length) {
  for (uint8_t index = 0; index < length; index++) {
    Serial.print(data[index], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void onReceived() {
  if (protocol.verifySum()) {
    display(protocol.buffer, Protocol::LENGTH);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  protocol.begin(9600);
  protocol.setOnReceived(onReceived);
}

void loop() {
  // put your main code here, to run repeatedly:
  protocol.buffer[0] = 0xff; //client
  protocol.buffer[1] = 0x10; //method
  protocol.buffer[2] = 0x11; //status
  protocol.buffer[3] = 0x00; //d3
  protocol.buffer[4] = 0x00; //d2
  protocol.buffer[5] = 0x00; //d1
  protocol.buffer[6] = 0x00; //d0
  protocol.buffer[7] = protocol.generateSum(); //checkSum

  if (protocol.verifySum()) {
    display(protocol.buffer, Protocol::LENGTH);
    protocol.send();
  }
  protocol.run();
  delay(3000);
}
