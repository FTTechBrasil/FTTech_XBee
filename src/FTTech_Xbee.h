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

// this prevents problems if someone accidently #include's the library twice.
#ifndef FTTech_Xbee_h
#define FTTech_Xbee_h

#include "Arduino.h"
#include "XBee.h"

#define PAYLOAD_SIZE 100

#ifdef _VARIANT_SAMD51_SWARM
    #define _XBEESERIAL Serial2
#endif

#ifdef _VARIANT_SAMD51_1S_OLD
    #define _XBEESERIAL Serial2
#endif

#ifdef _VARIANT_SAMD51_1S
    #define _XBEESERIAL Serial2
#endif

#ifdef _VARIANT_SAMD51_3S
    #define _XBEESERIAL Serial4
#endif

class FTTech_Xbee
{
public:
  FTTech_Xbee();
  /* #region Get Methods */
  void getAddress(uint8_t *address);
  void getOutPayload(uint8_t *payload);
  void getInPayload(char *payload);
  uint8_t getPowerLevel() {return _powerLevel; }
  uint8_t getInLength() { return _in_length; }
  uint8_t getEncryptionMode(){return _encryptionMode; }
  uint16_t getPayloadMaxSize() { return PAYLOAD_SIZE; }  
  uint16_t getOutPayloadLengh() { return _payload_len; }
  /* #endregion */

  /* #region Set Methods */
  void setChipID(char *ChipID){ strncpy(_ChipID, ChipID, strlen(ChipID));}
  /* #endregion */

  /* #region Begin Methods */
  void begin(uint32_t _baudrate);
  void begin(int timeout, uint32_t __baudrate);
  /* #endregion */

  /* #region Output Methods */
  void message(char* sensorName, float sensorValue1, float sensorValue2, float sensorValue3, float sensorValue4);
  void message(char* sensorName, float sensorValue1, float sensorValue2, float sensorValue3);
  void message(char* sensorName, int sensorValue1, int sensorValue2, float sensorValue3);
  void message(char* sensorName, float sensorValue1, float sensorValue2);
  void message(char* sensorName, float sensorValue1);
  void message(char* sensorName, char* sensorValue1);
  void messageClearPayload(void);
  void sendPayloadBroadcast(void);
  void sendPayload(int address_MS, int address_LS);
  /* #endregion */

  /* #region Input Methods */
  uint8_t getResponse();
  uint8_t getResponse(int timeout);
  uint8_t findInCharArray(char inString[], char target[]);
  uint8_t readAndFindData(char target[]);
  uint8_t readAndFindData(char target[], int timeout);
  /* #endregion */

  /* #region AT commands Methods */
  bool sendAtCommand(uint8_t cmd[], uint8_t cmdValue[] = {0}, uint8_t cmdValueLength = 0);
  bool writeEEPROM(void);

  bool setEncryptionMode(bool mode);
  bool setEncryptionKey(uint8_t key[], uint8_t keyLength);
  bool setPowerLevel(uint8_t powerLevel);

  bool receiveModuleAddress(void);
  bool receivePowerLevel(void);
  bool receiveEncryptionMode(void);
  /* #endregion */

  /* #region other methods */
  void print64bitAddress(void);
  void print64bitAddress(uint8_t *address);
  /* #endregion */

private:
  int _timeout = 500;
  char _ChipID[33] = {0};
  uint8_t _encryptionMode;
  uint8_t _address[8] = {0};
  uint8_t _powerLevel;
  uint16_t _payload_len = 0;
  uint8_t _in_length;
  // TODO: Remove one of those two payloads
  uint8_t _payload[PAYLOAD_SIZE];
  char _in_payload[PAYLOAD_SIZE];
//  Stream& _XBEESERIAL;
  
  XBee _xbee;
  ZBRxResponse _rx;
  AtCommandRequest atRequest = AtCommandRequest();
  AtCommandResponse atResponse = AtCommandResponse();

  /* #region Output Methods */
  void messageAppendValue(char* sensorValue, float sensorValue1, bool last);
  void messageAppendValue(char* sensorValue, int sensorValue1, bool last);
  void messageAddString(char* string);
  /* #endregion */
};

#endif
