/* -----------------------------------------
 * The MIT License (MIT)
 * 
 * Copyright (c) 2021 FTTech
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * -----------------------------------------
 */

#include "Arduino.h"
#include "FTTech_Xbee.h"
#include "XBee.h"
#include "utility/logging.h"

FTTech_Xbee::FTTech_Xbee(Stream &serial) : _serial(serial)
{
  _serial.setTimeout(2000);
}

void FTTech_Xbee::getOutPayload(uint8_t *payload)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::getOutPayload(uint8_t *payload) DEBUG_V3:Function started"));
  #endif

  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    payload[i] = _payload[i];
  }
}

void FTTech_Xbee::getInPayload(char *payload)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::getInPayload(char *payload) DEBUG_V3:Function started"));
  #endif

  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    payload[i] = _in_payload[i];
  }
}

void FTTech_Xbee::begin(void)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::begin(void) DEBUG_V3:Function started"));
  #endif

  begin(_timeout);
}

void FTTech_Xbee::begin(int timeout)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::begin(int baudrate, int timeout) DEBUG_V3:Function started"));
  #endif

  _rx = ZBRxResponse();
  _timeout = timeout;

  _xbee.setSerial(_serial);

  first_uart_send_str(F("Parameters:"));
  first_uart_send_str(F("\tTimeout: ")); uart_send_strln(_timeout);
  first_uart_send_str(F("\tPayload Size: ")); uart_send_strln(PAYLOAD_SIZE);
  first_uart_send_strln("\n");
}

void FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2, float sensorValue3, float sensorValue4)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2, float sensorValue3, float sensorValue4) DEBUG_V3:Function started"));
  #endif

  uint8_t len = 15 + 1 + 15 + 1 + 15 + 1 + 15; //sensor + sep + sensor + sep + sensor + sep + sensor
  char sensorValueCHR[len] = {0};

  messageAppendValue(sensorValueCHR, sensorValue1, false);
  messageAppendValue(sensorValueCHR, sensorValue2, false);
  messageAppendValue(sensorValueCHR, sensorValue3, false);
  messageAppendValue(sensorValueCHR, sensorValue4, true);

  message(sensorName, sensorValueCHR);
}

void FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2, float sensorValue3)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2, float sensorValue3) DEBUG_V3:Function started"));
  #endif

  uint8_t len = 15 + 1 + 15 + 1 + 15; //sensor + sep + sensor + sep + sensor
  char sensorValueCHR[len] = {0};

  messageAppendValue(sensorValueCHR, sensorValue1, false);
  messageAppendValue(sensorValueCHR, sensorValue2, false);
  messageAppendValue(sensorValueCHR, sensorValue3, true);

  message(sensorName, sensorValueCHR);
}

void FTTech_Xbee::message(char *sensorName, int sensorValue1, int sensorValue2, float sensorValue3)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::message(char *sensorName, int sensorValue1, int sensorValue2, float sensorValue3) DEBUG_V3:Function started"));
  #endif

  uint8_t len = 15 + 1 + 15 + 1 + 15; //sensor + sep + sensor + sep + sensor
  char sensorValueCHR[len] = {0};

  messageAppendValue(sensorValueCHR, sensorValue1, false);
  messageAppendValue(sensorValueCHR, sensorValue2, false);
  messageAppendValue(sensorValueCHR, sensorValue3, true);

  message(sensorName, sensorValueCHR);
}

void FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2) DEBUG_V3:Function started"));
  #endif

  uint8_t len = 15 + 1 + 15; //sensor + sep + sensor + sep + sensor
  char sensorValueCHR[len] = {0};

  messageAppendValue(sensorValueCHR, sensorValue1, false);
  messageAppendValue(sensorValueCHR, sensorValue2, true);

  message(sensorName, sensorValueCHR);
}

void FTTech_Xbee::message(char *sensorName, float sensorValue1)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::message(char *sensorName, float sensorValue1) DEBUG_V3:Function started"));
  #endif

  char sensorValueCHR[15];
  String sensorValueSTR = String(sensorValue1, 4);
  sensorValueSTR.toCharArray(sensorValueCHR, 15);
  message(sensorName, sensorValueCHR);
}

void FTTech_Xbee::message(char *sensorName, char *sensorValue1)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::message(char *sensorName, char *sensorValue1) DEBUG_V3:Function started"));
  #endif

  char separatorLv1[] = "#";
  char separatorLv2[] = ":";

  if (_payload_len == 0)
  {
    // Frame Init identification
    _payload[0] = '<';
    _payload[1] = '+';
    _payload[2] = '>';
    _payload_len += 3;

    // Add UniqueID from SAMD51 Board
    messageAddString(_ChipID);

    // Add Block Separator
    messageAddString(separatorLv1);
  }
  messageAddString(sensorName);
  messageAddString(separatorLv2);
  messageAddString(sensorValue1);
  messageAddString(separatorLv1);
}

void FTTech_Xbee::messageClearPayload(void)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::messageClearPayload(void) DEBUG_V3:Function started"));
  #endif

  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    _payload[i] = '\0';
  }
  _payload_len = 0;
}

void FTTech_Xbee::sendPayloadBoadcast(void)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::sendPayloadBoadcast(void) DEBUG_V3:Function started"));
  #endif

  sendPayload(0x00000000, 0x0000ffff);
}

void FTTech_Xbee::sendPayload(int address_MS, int address_LS)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::sendPayload(int address_MS, int address_LS) DEBUG_V3:Function started"));
  #endif

  XBeeAddress64 addr64 = XBeeAddress64(address_MS, address_LS);
  ZBTxStatusResponse txStatus = ZBTxStatusResponse();

  ZBTxRequest zbTx = ZBTxRequest(addr64, _payload, _payload_len);
  _xbee.send(zbTx);
  _serial.flush();
  delay(100);
}

// return uint8_t "1" if no error, "0" if error
uint8_t FTTech_Xbee::getResponse()
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::getResponse() DEBUG_V3:Function started"));
  #endif

  return getResponse(_timeout);
}

// return uint8_t "1" if no error, "0" if error
uint8_t FTTech_Xbee::getResponse(int timeout)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::getResponse(int timeout) DEBUG_V3:Function started"));
  #endif

  uint8_t rssi;
  uint8_t option;

  memset(&_in_payload[0], 0, PAYLOAD_SIZE);
  _in_length = 0;

  _xbee.readPacket(_timeout);

  if (_xbee.getResponse().isAvailable())
  {
    // got something
    // ZB_RX_RESPONSE = 0x90, to test send a packet type 0x10 using XCTU
    if (_xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
    {
      // got a rx packet
      _xbee.getResponse().getZBRxResponse(_rx);
      option = _rx.getOption();

      int i = 0;
      char c;
      while (i < _rx.getDataLength() && i < PAYLOAD_SIZE)
      {
        c = _rx.getData(i);
        _in_payload[i] = c;
        i++;
      }
      _in_length = _rx.getDataLength();
      return 1;
    } else
    {
      // not something we were expecting
      #if ACTLOGLEVEL>=LOG_ERR
        first_uart_send_str(F("Receive a different kind os packet. Received: "));
        uart_send_hexln(_xbee.getResponse().getApiId());
      #endif
    }
  } else if (_xbee.getResponse().isError())
  {
    #if ACTLOGLEVEL>=LOG_ERR
      first_uart_send_str(F("Error reading packet.  Error code: "));
      uart_send_strln(_xbee.getResponse().getErrorCode());
    #endif
  }
  //Serial.println(F("Didn't receive any packet"));
  return 0;
}


// return uint8_t "1" if no error, "0" if error
uint8_t FTTech_Xbee::findInCharArray(char inString[], char target[])
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::findInCharArray(char inString[], char target[]) DEBUG_V3:Function started"));
  #endif

  if (strstr(inString, target))
    return 1;
  else
    return 0;
}

// return uint8_t "1" if no error, "0" if error
uint8_t FTTech_Xbee::readAndFindData(char target[])
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::readAndFindData(char target[]) DEBUG_V3:Function started"));
  #endif

  return readAndFindData(target, _timeout);
}

// return uint8_t "1" if no error, "0" if error
uint8_t FTTech_Xbee::readAndFindData(char target[], int timeout)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::readAndFindData(char target[], int timeout) DEBUG_V3:Function started"));
  #endif

  if (getResponse(timeout))
  {
    return findInCharArray(_in_payload, target);
  }
  return 0;
}

bool FTTech_Xbee::sendAtCommand(uint8_t cmd[], uint8_t cmdValue[], uint8_t cmdValueLength) 
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::sendAtCommand(uint8_t cmd[], uint8_t cmdValue[], uint8_t cmdValueLength) DEBUG_V3:Function started"));
  #endif

  bool success = false;

  atRequest.setCommand(cmd);
  if(cmdValueLength > 0)
  {
    atRequest.setCommandValue(cmdValue);
    atRequest.setCommandValueLength(cmdValueLength);
  }

  #if ACTLOGLEVEL>=LOG_INFO
    first_uart_send_strln(F("Sending command to the XBee"));
  #endif

  // send the command
  _xbee.send(atRequest);

  // wait up to 5 seconds for the status response
  if (_xbee.readPacket(5000)) {
    // got a response!

    // should be an AT command response
    if (_xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) {
      _xbee.getResponse().getAtCommandResponse(atResponse);

      if (atResponse.isOk()) {
        success = true;
        #if ACTLOGLEVEL>=LOG_DEBUG
          first_uart_send_str(F("Command ["));
          uart_send_str(atResponse.getCommand()[0]);
          uart_send_str(atResponse.getCommand()[1]);
          uart_send_strln(F("] was successful!"));

          if (atResponse.getValueLength() > 0) {
            first_uart_send_str(F("Command value length is "));
            uart_send_decln(atResponse.getValueLength());

            first_uart_send_str(F("Command value: "));
            
            for (int i = 0; i < atResponse.getValueLength(); i++) {
              uart_send_hex(atResponse.getValue()[i]);
              uart_send_str(" ");
            }

            uart_send_strln("");
          }
        #endif
      } else {
        success = false;
        #if ACTLOGLEVEL>=LOG_ERR
          first_uart_send_str(F("Command return error code: "));
          uart_send_hexln(atResponse.getStatus());
        #endif
      }
    } else 
    {
      success = false;
      #if ACTLOGLEVEL>=LOG_ERR
        first_uart_send_str(F("Expected AT response but got "));  
        uart_send_hexln(_xbee.getResponse().getApiId());
      #endif
    }   
  } else  
  {
    success = false;
    #if ACTLOGLEVEL>=LOG_ERR
      if (_xbee.getResponse().isError()) {
        first_uart_send_str(F("Error reading packet.  Error code: "));  
        uart_send_strln(_xbee.getResponse().getErrorCode());
      } 
      else {
        first_uart_send_strln(F("No response from radio"));  
      }
    #endif  
  }

  return success;
}

bool FTTech_Xbee::writeEEPROM(void)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::writeEEPROM(void) DEBUG_V3:Function started"));
  #endif
  
  uint8_t cmd[] = {'W','R'};
  return sendAtCommand(cmd);
}

bool FTTech_Xbee::setEncryptionMode(bool mode)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::setEncryptionMode(bool mode) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'E','E'};
  uint8_t cmdValue[1] = {0};
  uint8_t cmdValueLength = 1;

  if(mode)
  {
    cmdValue[0] = 1;
  }

  return sendAtCommand(cmd, cmdValue, cmdValueLength);
}

bool FTTech_Xbee::setEncryptionKey(uint8_t key[], uint8_t keyLength)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::setEncryptionKey(uint8_t key[], uint8_t keyLength) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'K','Y'};

  return sendAtCommand(cmd, key, keyLength);
}

bool FTTech_Xbee::receiveModuleAddress(void)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::receiveModuleAddress(void) DEBUG_V3:Function started"));
  #endif

  bool success = false;
  // serial high
  uint8_t shCmd[] = {'S','H'};
  // serial low
  uint8_t slCmd[] = {'S','L'};

  if (sendAtCommand(shCmd)) {    
    for (int i = 0; i < atResponse.getValueLength(); i++) {
      _address[i] = atResponse.getValue()[i];
    }
    if(sendAtCommand(slCmd))
    {
      for (int i = 0; i < atResponse.getValueLength(); i++) {
        _address[i+4] = atResponse.getValue()[i];
      }
      success = true;
    }
  }

  return success;
}

bool FTTech_Xbee::receivePowerLevel(void)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::receivePowerLevel(void) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'P','L'};

  if(sendAtCommand(cmd))
  {
    _powerLevel = atResponse.getValue()[0];
    return true;
  }
  return false;
}

bool FTTech_Xbee::receiveEncryptionMode(void)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::receiveEncryptionMode(void) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'E','E'};

  if(sendAtCommand(cmd))
  {
    _encryptionMode = atResponse.getValue()[0];
    return true;
  }
  return false;
}

bool FTTech_Xbee::setPowerLevel(uint8_t powerLevel)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::setPowerLevel(uint8_t powerLevel) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'P','L'};
  uint8_t cmdValue[1] = {0};
  uint8_t cmdValueLength = 1;

  cmdValue[0] = powerLevel;
  bool result = sendAtCommand(cmd, cmdValue, cmdValueLength);

  receivePowerLevel();

  return result;
}

void FTTech_Xbee::print64bitAddress()
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::print64bitAddress() DEBUG_V3:Function started"));
  #endif

  print64bitAddress(_address);
}

void FTTech_Xbee::print64bitAddress(uint8_t address[8])
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::print64bitAddress(uint8_t address[8]) DEBUG_V3:Function started"));
  #endif

  uart_send_str("64 bit Address: ");
  for (int i = 0; i < 8; i++) {
    if (address[i] <= 0x0F) uart_send_str(F("0"));
    uart_send_hex(address[i]);
  }
  uart_send_strln(F(" "));
}

void FTTech_Xbee::messageAppendValue(char *sensorValue, float sensorValue1, bool last)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::messageAppendValue(char *sensorValue, float sensorValue1, bool last) DEBUG_V3:Function started"));
  #endif

  char separatorLv3[] = ";";
  char tempValue[15] = {0};

  if (ceilf(sensorValue1) == sensorValue1)
    itoa((int)sensorValue1, tempValue, 10);
  else
  {
    String sensorValueSTR = String(sensorValue1, 4);
    sensorValueSTR.toCharArray(tempValue, 15);
  }

  memcpy(&sensorValue[strlen(sensorValue)], tempValue, strlen(tempValue));

  if (!last)
  {
    memcpy(&sensorValue[strlen(sensorValue)], separatorLv3, strlen(separatorLv3));
  }
}

void FTTech_Xbee::messageAppendValue(char *sensorValue, int sensorValue1, bool last)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::messageAppendValue(char *sensorValue, int sensorValue1, bool last) DEBUG_V3:Function started"));
  #endif

  char separatorLv3[] = ";";
  char tempValue[15] = {0};

  itoa(sensorValue1, tempValue, 10);

  memcpy(&sensorValue[strlen(sensorValue)], tempValue, strlen(tempValue));

  if (!last)
  {
    memcpy(&sensorValue[strlen(sensorValue)], separatorLv3, strlen(separatorLv3));
  }
}

void FTTech_Xbee::messageAddString(char *string)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    first_uart_send_strln(F("FTTech_Xbee::messageAddString(char *string) DEBUG_V3:Function started"));
  #endif

  memcpy(&_payload[_payload_len], string, strlen(string));
  _payload_len += strlen(string);
}