#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "Arduino.h"
#include "Helper.h"
#include "SoftwareSerial.h"
#include "Storage.h"
#include "Terminal.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
typedef void (*Callback)();
typedef struct Spdu {
  uint8_t cla = 0;
  uint8_t com = 0;
  uint32_t p1 = 0;
  uint32_t p2 = 0;
  uint8_t sta = 0;
};

// CLASS,COMMAND,P1,P2,STATE
class Protocol : public SoftwareSerial {
 public:
  // classes
  static const uint8_t CLASS_FIRMWARE = 1;
  static const uint8_t CLASS_MODE = 2;
  static const uint8_t CLASS_RUNTIME = 3;

  static const uint8_t CLASS_PIN = 10;
  static const uint8_t CLASS_RATE = 11;
  static const uint8_t CLASS_MIN = 12;
  static const uint8_t CLASS_LIM = 13;

  static const uint8_t CLASS_TRANSA = 20;
  static const uint8_t CLASS_AMOUNT = 21;
  static const uint8_t CLASS_TRANSC = 22;
  static const uint8_t CLASS_CREDIT = 23;

  static const uint8_t CLASS_SERVE = 30;
  static const uint8_t CLASS_POWER = 31;

  static const uint8_t CLASS_CLR = 40;
  static const uint8_t CLASS_RST = 41;
  static const uint8_t CLASS_FMT = 42;

  static const uint8_t CLASS_REBOOT = 50;
  static const uint8_t CLASS_TERMINALS = 51;

  // command
  static const uint8_t COM_GET = 1;
  static const uint8_t COM_SET = 2;
  static const uint8_t COM_EXE = 3;
  static const uint8_t COM_CMP = 4;

  // states
  static const uint8_t STATE_SUCCESS = 10;
  static const uint8_t STATE_ERR_WRONG_FMT = 50;
  static const uint8_t STATE_ERR_WRONG_CLA = 51;
  static const uint8_t STATE_ERR_WRONG_COM = 52;

  void interpret(void);

  Terminal *terminals;
  String buffer;

  Protocol(uint8_t rx, uint8_t tx);
  void onReceived(Callback onReceived);
  void run(void);
  void execute();

 private:
  Spdu _spdu;

  String _delimeter = ",";

  Callback _onReceived;
  uint8_t _index = 0;
  uint8_t _zero = 0;

  Storage _storage;
  Helper _helper;
};

#endif  // _PROTOCOL_H
