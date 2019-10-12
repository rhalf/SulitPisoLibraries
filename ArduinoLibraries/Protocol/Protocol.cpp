#include "Protocol.h"
#include "Arduino.h"
#include "Helper.h"
#include "SoftwareSerial.h"
#include "Storage.h"
#include "Timer.h"

typedef void (*Callback)();

Protocol::Protocol(uint8_t rx, uint8_t tx) : SoftwareSerial(rx, tx) {
  _storage = Storage();
  _helper = Helper();

  buffer.reserve(32);
  _delimeter = ",";
}

void Protocol::interpret(void) {
  uint8_t index[4];
  index[0] = buffer.indexOf(_delimeter);
  index[1] = buffer.indexOf(_delimeter, index[0] + 1);
  index[2] = buffer.indexOf(_delimeter, index[1] + 1);
  index[3] = buffer.indexOf(_delimeter, index[2] + 1);

  _spdu.cla = _helper.parseInt(buffer.substring(0, index[0]));
  _spdu.com = _helper.parseInt(buffer.substring(index[0] + 1, index[1]));
  _spdu.p1 = _helper.parseInt(buffer.substring(index[1] + 1, index[2]));
  _spdu.p2 = _helper.parseInt(buffer.substring(index[2] + 1, index[3]));
  _spdu.sta = _helper.parseInt(buffer.substring(index[3] + 1));

  Protocol::execute();
}

void Protocol::execute(void) {
  switch (_spdu.cla) {
    case Protocol::CLASS_RUNTIME:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = Timer::getSeconds();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_FIRMWARE:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getFirmware();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_MODE:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getMode();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_SET) {
        _storage.setMode(_spdu.p1);
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_PIN:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getPin();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_SET) {
        _storage.setPin(_spdu.p1);
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_CMP) {
        _spdu.p1 = (_spdu.p1 == _storage.getPin()) ? 0 : 1;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_RATE:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getRate();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_SET) {
        _storage.setRate(_spdu.p1);
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_MIN:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getMinimum();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_SET) {
        _storage.setMinimum(_spdu.p1);
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_LIM:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getLimit();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_SET) {
        _storage.setLimit(_spdu.p1);

        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_PKWH:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getPkwh();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_SET) {
        _storage.setPkwh(_spdu.p1);

        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_TRANSA:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getCurrentTransA();
        _spdu.p2 = _storage.getLifetimeTransA();
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_AMOUNT:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getCurrentAmount();
        _spdu.p2 = _storage.getLifetimeAmount();
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_TRANSC:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getCurrentTransC();
        _spdu.p2 = _storage.getLifetimeTransC();
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_CREDIT:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getCurrentCredit();
        _spdu.p2 = _storage.getLifetimeCredit();
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_EXE) {
        if (_spdu.p2 > 0) {
          _storage.incrementCredit(_spdu.p2);
          terminals[_spdu.p1].set(_spdu.p2 * _storage.getRate());
        } else {
          terminals[_spdu.p1].reset();
        }
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_TRANSF:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getCurrentTransF();
        _spdu.p2 = _storage.getLifetimeTransF();
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_FREE:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getCurrentFree();
        _spdu.p2 = _storage.getLifetimeFree();
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_SERVE:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.sta = Protocol::STATE_SUCCESS;
        _spdu.p1 = _storage.getCurrentServe();
        _spdu.p2 = _storage.getLifetimeServe();
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_TIME:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getCurrentTime();
        _spdu.p2 = _storage.getLifetimeTime();
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_POWER:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getCurrentPower();
        _spdu.p2 = _storage.getLifetimePower();
        _spdu.sta = Protocol::STATE_SUCCESS;

      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_CLR:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getClearDate();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;

      } else if (_spdu.com == Protocol::COM_EXE) {
        _storage.clear(_spdu.p1);
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_RST:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getResetDate();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_EXE) {
        _storage.reset(_spdu.p1);
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_FMT:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p1 = _storage.getFormatDate();
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else if (_spdu.com == Protocol::COM_EXE) {
        _storage.format(_spdu.p1);
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_REBOOT:
      if (_spdu.com == Protocol::COM_EXE) {
        while (true) {
          // make arduino hang
        };
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    case Protocol::CLASS_TERMINALS:
      if (_spdu.com == Protocol::COM_GET) {
        _spdu.p2 = terminals[_spdu.p1].timeLapse;
        _spdu.sta = Protocol::STATE_SUCCESS;
      } else {
        _spdu.p1 = _zero;
        _spdu.p2 = _zero;
        _spdu.sta = Protocol::STATE_ERR_WRONG_COM;
      }
      break;

    default:
      _spdu.com = _zero;
      _spdu.p1 = _zero;
      _spdu.p2 = _zero;
      _spdu.sta = Protocol::STATE_ERR_WRONG_CLA;
  }

  buffer = String(_spdu.cla) + _delimeter + String(_spdu.com) + _delimeter +
           String(_spdu.p1) + _delimeter + String(_spdu.p2) + _delimeter +
           String(_spdu.sta) + "\n";
}

void Protocol::onReceived(Callback onReceived) { _onReceived = onReceived; }

void Protocol::run(void) {
  if (available()) {
    if (available()) {
      char chr = (char)read();
      buffer += chr;
      if (chr == '\n') {
        _onReceived();
        buffer = "";
        return;
      }
    }
  }
}