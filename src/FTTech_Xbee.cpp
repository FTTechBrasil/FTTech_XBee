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
    uart_send_strln(F("FTTech_Xbee::getOutPayload(uint8_t *payload) DEBUG_V3:Function started"));
  #endif

  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    payload[i] = _payload[i];
  }
}

void FTTech_Xbee::getInPayload(char *payload)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::getInPayload(char *payload) DEBUG_V3:Function started"));
  #endif

  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    payload[i] = _in_payload[i];
  }
}

void FTTech_Xbee::begin(void)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::begin(void) DEBUG_V3:Function started"));
  #endif

  begin(_baudrate, _timeout);
}

void FTTech_Xbee::begin(int baudrate, int timeout)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::begin(int baudrate, int timeout) DEBUG_V3:Function started"));
  #endif

  _rx = ZBRxResponse();
  _baudrate = baudrate;
  _timeout = timeout;

  _xbee.setSerial(_serial);

  Serial.println(F("Parameters:"));
  Serial.print(F("\tBaudrate: ")); Serial.println(_baudrate);
  Serial.print(F("\tTimeout: ")); Serial.println(_timeout);
  Serial.print(F("\tPayload Size: ")); Serial.println(PAYLOAD_SIZE);
  Serial.println("\n");
}

void FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2, float sensorValue3, float sensorValue4)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2, float sensorValue3, float sensorValue4) DEBUG_V3:Function started"));
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
    uart_send_strln(F("FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2, float sensorValue3) DEBUG_V3:Function started"));
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
    uart_send_strln(F("FTTech_Xbee::message(char *sensorName, int sensorValue1, int sensorValue2, float sensorValue3) DEBUG_V3:Function started"));
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
    uart_send_strln(F("FTTech_Xbee::message(char *sensorName, float sensorValue1, float sensorValue2) DEBUG_V3:Function started"));
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
    uart_send_strln(F("FTTech_Xbee::message(char *sensorName, float sensorValue1) DEBUG_V3:Function started"));
  #endif

  char sensorValueCHR[15];
  String sensorValueSTR = String(sensorValue1, 4);
  sensorValueSTR.toCharArray(sensorValueCHR, 15);
  message(sensorName, sensorValueCHR);
}

void FTTech_Xbee::message(char *sensorName, char *sensorValue1)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::message(char *sensorName, char *sensorValue1) DEBUG_V3:Function started"));
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
    uart_send_strln(F("FTTech_Xbee::messageClearPayload(void) DEBUG_V3:Function started"));
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
    uart_send_strln(F("FTTech_Xbee::sendPayloadBoadcast(void) DEBUG_V3:Function started"));
  #endif

  sendPayload(0x00000000, 0x0000ffff);
}

void FTTech_Xbee::sendPayload(int address_MS, int address_LS)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::sendPayload(int address_MS, int address_LS) DEBUG_V3:Function started"));
  #endif

  XBeeAddress64 addr64 = XBeeAddress64(address_MS, address_LS);
  ZBTxStatusResponse txStatus = ZBTxStatusResponse();

  ZBTxRequest zbTx = ZBTxRequest(addr64, _payload, _payload_len);
  _xbee.send(zbTx);
  _serial.flush();
  delay(100);
}

bool FTTech_Xbee::getResponse()
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::getResponse() DEBUG_V3:Function started"));
  #endif

  return getResponse(_timeout);
}

bool FTTech_Xbee::getResponse(int timeout)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::getResponse(int timeout) DEBUG_V3:Function started"));
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
      return true;
    } else
    {
      // not something we were expecting
      Serial.print(F("Receive a different kind os packet. Received: ")); Serial.println(_xbee.getResponse().getApiId(), HEX);
      return false;
    }
  } else if (_xbee.getResponse().isError())
  {
    Serial.print(F("Error reading packet.  Error code: ")); Serial.println(_xbee.getResponse().getErrorCode());
    return false;
  }
  //Serial.println(F("Didn't receive any packet"));
  return false;
}

bool FTTech_Xbee::findInCharArray(char inString[], char target[])
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::findInCharArray(char inString[], char target[]) DEBUG_V3:Function started"));
  #endif

  if (strstr(inString, target))
    return true;
  else
    return false;
}

bool FTTech_Xbee::readAndFindData(char target[])
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::readAndFindData(char target[]) DEBUG_V3:Function started"));
  #endif

  return readAndFindData(target, _timeout);
}

bool FTTech_Xbee::readAndFindData(char target[], int timeout)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::readAndFindData(char target[], int timeout) DEBUG_V3:Function started"));
  #endif

  if (getResponse(timeout))
  {
    return findInCharArray(_in_payload, target);
  }
  return false;
}

bool FTTech_Xbee::sendAtCommand(uint8_t cmd[], bool debug, uint8_t cmdValue[], uint8_t cmdValueLength) 
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::sendAtCommand(uint8_t cmd[], bool debug, uint8_t cmdValue[], uint8_t cmdValueLength) DEBUG_V3:Function started"));
  #endif

  bool success = false;

  atRequest.setCommand(cmd);
  if(cmdValueLength > 0)
  {
    atRequest.setCommandValue(cmdValue);
    atRequest.setCommandValueLength(cmdValueLength);
  }

  if(debug)
  {
    Serial.println(F("Sending command to the XBee"));
  }

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
        if(debug)
        {
          Serial.print(F("Command ["));
          Serial.print(atResponse.getCommand()[0]);
          Serial.print(atResponse.getCommand()[1]);
          Serial.println(F("] was successful!"));

          if (atResponse.getValueLength() > 0) {
            Serial.print(F("Command value length is "));
            Serial.println(atResponse.getValueLength(), DEC);

            Serial.print(F("Command value: "));
            
            for (int i = 0; i < atResponse.getValueLength(); i++) {
              Serial.print(atResponse.getValue()[i], HEX);
              Serial.print(" ");
            }

            Serial.println("");
          }
        }
      } else 
      {
        success = false;
        if(debug)
        {
          Serial.print(F("Command return error code: "));
          Serial.println(atResponse.getStatus(), HEX);
        }
      }
    } else 
    {
      success = false;
      if(debug)
      {
        Serial.print(F("Expected AT response but got "));
        Serial.print(_xbee.getResponse().getApiId(), HEX);
      }
    }   
  } else 
  {
    success = false;
    if(debug)
    {
      if (_xbee.getResponse().isError()) {
        Serial.print(F("Error reading packet.  Error code: "));  
        Serial.println(_xbee.getResponse().getErrorCode());
      } 
      else {
        Serial.print(F("No response from radio"));  
      }
    }
  }

  return success;
}

bool FTTech_Xbee::writeEEPROM(bool debug)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::writeEEPROM(bool debug) DEBUG_V3:Function started"));
  #endif
  
  uint8_t cmd[] = {'W','R'};
  return sendAtCommand(cmd, debug);
}

bool FTTech_Xbee::setEncryptionMode(bool mode, bool debug)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::setEncryptionMode(bool mode, bool debug) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'E','E'};
  uint8_t cmdValue[1] = {0};
  uint8_t cmdValueLength = 1;

  if(mode)
  {
    cmdValue[0] = 1;
  }

  return sendAtCommand(cmd, debug, cmdValue, cmdValueLength);
}

bool FTTech_Xbee::setEncryptionKey(uint8_t key[], uint8_t keyLength, bool debug)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::setEncryptionKey(uint8_t key[], uint8_t keyLength, bool debug) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'K','Y'};

  return sendAtCommand(cmd, debug, key, keyLength);
}

bool FTTech_Xbee::receiveModuleAddress(bool debug)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::receiveModuleAddress(bool debug) DEBUG_V3:Function started"));
  #endif

  bool success = false;
  // serial high
  uint8_t shCmd[] = {'S','H'};
  // serial low
  uint8_t slCmd[] = {'S','L'};

  if (sendAtCommand(shCmd, debug)) {    
    for (int i = 0; i < atResponse.getValueLength(); i++) {
      _address[i] = atResponse.getValue()[i];
    }
    if(sendAtCommand(slCmd, debug))
    {
      for (int i = 0; i < atResponse.getValueLength(); i++) {
        _address[i+4] = atResponse.getValue()[i];
      }
      success = true;
    }
  }

  return success;
}

bool FTTech_Xbee::receivePowerLevel(bool debug)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::receivePowerLevel(bool debug) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'P','L'};

  if(sendAtCommand(cmd, debug))
  {
    _powerLevel = atResponse.getValue()[0];
    return true;
  }
  return false;
}

bool FTTech_Xbee::receiveEncryptionMode(bool debug)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::receiveEncryptionMode(bool debug) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'E','E'};

  if(sendAtCommand(cmd, debug))
  {
    _encryptionMode = atResponse.getValue()[0];
    return true;
  }
  return false;
}

bool FTTech_Xbee::setPowerLevel(uint8_t powerLevel, bool debug)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::setPowerLevel(uint8_t powerLevel, bool debug) DEBUG_V3:Function started"));
  #endif

  uint8_t cmd[] = {'P','L'};
  uint8_t cmdValue[1] = {0};
  uint8_t cmdValueLength = 1;

  cmdValue[0] = powerLevel;
  bool result = sendAtCommand(cmd, debug, cmdValue, cmdValueLength);

  receivePowerLevel();

  return result;
}

void FTTech_Xbee::print64bitAddress()
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::print64bitAddress() DEBUG_V3:Function started"));
  #endif

  print64bitAddress(_address);
}

void FTTech_Xbee::print64bitAddress(uint8_t address[8])
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::print64bitAddress(uint8_t address[8]) DEBUG_V3:Function started"));
  #endif

  Serial.print("64 bit Address: ");
  for (int i = 0; i < 8; i++) {
    if (address[i] <= 0x0F) Serial.print(F("0"));
    Serial.print(address[i],HEX);
  }
  Serial.println(F(" "));
}

void FTTech_Xbee::messageAppendValue(char *sensorValue, float sensorValue1, bool last)
{
  #if ACTLOGLEVEL>=LOG_DEBUG_V3
    uart_send_strln(F("FTTech_Xbee::messageAppendValue(char *sensorValue, float sensorValue1, bool last) DEBUG_V3:Function started"));
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
    uart_send_strln(F("FTTech_Xbee::messageAppendValue(char *sensorValue, int sensorValue1, bool last) DEBUG_V3:Function started"));
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
    uart_send_strln(F("FTTech_Xbee::messageAddString(char *string) DEBUG_V3:Function started"));
  #endif

  memcpy(&_payload[_payload_len], string, strlen(string));
  _payload_len += strlen(string);
}