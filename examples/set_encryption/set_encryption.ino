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
 * 
 * This is an example to test setting the encryption mode on and the desired 
 * encryption key
 * 
 * Please report if you find any issue when using this code so when can
 * keep improving it
 */
#include "FTTech_Xbee.h"
#include "FTTech_SAMD51_Clicks.h"


/* *****************************************
 * USER DEFINED VARIABLES
 */
#define XBEE_SERIAL Serial4                 // XBee Serial port. If you're using FTClicks board it will be one Serial4
int BAUDRATE = 115200;                      // XBee and Serial boudrate, you can set diferent ones if you want but remmeber to check XBee configuration using XCTU
int address_HB = 0x0013A200;                // Most significant bytes from XBee's address
int address_LB = 0x40F67850;                // Least significant bytes from XBee's address
uint8_t kyCmdValue[] = "WaspmoteLinkKey!";  // Encryption key, remmeber to set it in all your devices
uint8_t keyLength = 16;                     // Key Length
uint8_t payload[100] = {0};
/* *****************************************
 * PROGRAM VARIABLES - AVOID CHANGING THEM
 */
FTTech_Xbee xbee;


void setup()
{
  FTClicks.begin();
  
  // Turn XBee power on
  FTClicks.ON(4);
  
  Serial.begin(BAUDRATE);

  while (!Serial) delay(10);
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));
  Serial.println(F("FTTech - Test XBee Encryption Mode ON"));
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));

  XBEE_SERIAL.begin(BAUDRATE);
  // All the other arduments will be loaded by default, you can chance them by calling begin(Stream &serial, int baudrate, int timeout, int payload_size)
  xbee.begin(XBEE_SERIAL);
  
  delay(5000);
  if(xbee.receiveEncryptionMode(false))
  {
    Serial.print(F("Encryption Mode is set to: ")); Serial.println(xbee.getEncryptionMode());
  }
  
  // Set encryption mode to true and send the encryption key
  if(xbee.setEncryptionMode(true, false) && xbee.setEncryptionKey(kyCmdValue, keyLength, false))
  {
    Serial.println(F("Success! Encryption mode and encryption key were configured."));
    
    // Save comands to XBee so it doesn't lose them after reboot
    if(xbee.writeEEPROM(false))
    {
      Serial.println(F("Commands saved to EEPROM"));
    }
  }

  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));
}

void loop()
{
    xbee.messageClearPayload();
    xbee.message("TEST_STR", "12345");
    xbee.sendPayload(address_HB, address_LB);

    xbee.getOutPayload(payload);
    printData(payload, xbee.getOutPayloadLengh());

    delay(5000);
}


void printData(uint8_t *payloa, uint16_t payload_length)
{
   Serial.print(F("Payload: "));
   for (int i = 0; i < payload_length; i++)
   {
     Serial.write(payloa[i]);
   }
   Serial.print(F("\tLength: "));
   Serial.print(payload_length);
   Serial.println("");
}