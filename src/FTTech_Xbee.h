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

class FTTech_Xbee
{
public:
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
  void begin(Stream &serial);
  void begin(Stream &serial, int baudrate, int timeout);
  /* #endregion */

  /* #region Output Methods */
  void message(char* sensorName, float sensorValue1, float sensorValue2, float sensorValue3, float sensorValue4);
  void message(char* sensorName, float sensorValue1, float sensorValue2, float sensorValue3);
  void message(char* sensorName, int sensorValue1, int sensorValue2, float sensorValue3);
  void message(char* sensorName, float sensorValue1, float sensorValue2);
  void message(char* sensorName, float sensorValue1);
  void message(char* sensorName, char* sensorValue1);
  void messageClearPayload(void);
  void sendPayloadBoadcast(void);
  void sendPayload(int address_MS, int address_LS);
  /* #endregion */

  /* #region Input Methods */
  bool getResponse();
  bool getResponse(int timeout);
  bool findInCharArray(char inString[], char target[]);
  bool readAndFindData(char target[]);
  bool readAndFindData(char target[], int timeout);
  /* #endregion */

  /* #region AT commands Methods */
  bool sendAtCommand(uint8_t cmd[], bool debug, uint8_t cmdValue[] = {0}, uint8_t cmdValueLength = 0);
  bool writeEEPROM(bool debug = false);

  bool setEncryptionMode(bool mode, bool debug = false);
  bool setEncryptionKey(uint8_t key[], uint8_t keyLength, bool debug=false);
  bool setPowerLevel(uint8_t powerLevel, bool debug=false);

  bool receiveModuleAddress(bool debug=false);
  bool receivePowerLevel(bool debug=false);
  bool receiveEncryptionMode(bool debug=false);
  /* #endregion */

  /* #region other methods */
  void print64bitAddress();
  void print64bitAddress(uint8_t *address);
  /* #endregion */

private:
  int _baudrate = 115200;
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
