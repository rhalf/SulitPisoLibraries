#include<Storage.h>

Storage storage = Storage();

const char s1[] PROGMEM = "Storage Class";
const char s2[] PROGMEM = "rhalfcaacbay@gmail.com";
const char s3[] PROGMEM = "commands : ";
const char s4[] PROGMEM = "c : create structure, d : delete structure, r : reset memories to zero, s : show data";
const char s5[] PROGMEM = "1 : increment values by 1; 2 : increment values by 2";

char * const messages[] PROGMEM = {
  s1, s2, s3, s4, s5
};

void display(void) {
  Serial.println("pinCode : " + String(storage.getPinCode()));
  Serial.println("rate : " + String(storage.getRate()));

  Serial.println("transaction (c) : " + String(storage.getCurrentTransaction()));
  Serial.println("transaction (l) : " + String(storage.getLifetimeTransaction()));

  Serial.println("gross (c) : " + String(storage.getCurrentGross()));
  Serial.println("gross (l) : " + String(storage.getLifetimeGross()));

  Serial.println("coin1 (c) : " + String(storage.getCurrentCoin1()));
  Serial.println("coin1 (l) : " + String(storage.getLifetimeCoin1()));
  Serial.println("coin5 (c) : " + String(storage.getCurrentCoin5()));
  Serial.println("coin5 (l) : " + String(storage.getLifetimeCoin5()));
  Serial.println("coin10 (c) : " + String(storage.getCurrentCoin10()));
  Serial.println("coin10 (l) : " + String(storage.getLifetimeCoin10()));

  Serial.println("term0 (c) : " + String(storage.getCurrentTerm0()));
  Serial.println("term0 (l) : " + String(storage.getLifetimeTerm0()));
  Serial.println("term1 (c) : " + String(storage.getCurrentTerm1()));
  Serial.println("term1 (l) : " + String(storage.getLifetimeTerm1()));
  Serial.println("term2 (c) : " + String(storage.getCurrentTerm2()));
  Serial.println("term2 (l) : " + String(storage.getLifetimeTerm2()));
  Serial.println("term3 (c) : " + String(storage.getCurrentTerm3()));
  Serial.println("term3 (l) : " + String(storage.getLifetimeTerm3()));
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  for (uint8_t index = 0; index < 5; index++) {
    char * ptr = (char *) pgm_read_word(&messages[index]);
    char buffer [80]; // must be large enough!
    strcpy_P (buffer, ptr);
    Serial.println(buffer);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}


void serialEvent(void) {
  if (Serial.available()) {
    char data = (char) Serial.read();
    switch (data) {
        break;
      case '1':
        increment(1);
        break;
      case '2':
        increment(2);
        break;
      case 's':
        display();
        break;
      case 'r':
        storage.reset();
        break;
      case 'c':
        storage.create();
        break;
      case 'd':
        storage.destroy();
        break;
    }
  }
}

void increment(uint32_t data) {
  storage.incrementTransaction(data);
  storage.incrementGross(data);
  storage.incrementCoin1(data);
  storage.incrementCoin5(data);
  storage.incrementTerm0(data);
  storage.incrementCoin10(data);
  storage.incrementTerm1(data);
  storage.incrementTerm2(data);
  storage.incrementTerm3(data);
}