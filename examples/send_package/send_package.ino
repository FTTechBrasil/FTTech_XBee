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
 * This is an example to test sending messages from your FTClick with an XBee
 * and find a target message inside it.
 * 
 * Please report if you find any issue when using this code so when can
 * keep improving it
 */
#include "FTTech_Xbee.h"
#include "FTTech_SAMD51_Clicks.h"


/* *****************************************
 * USER DEFINED VARIABLES
 */
#define XBEE_SERIAL Serial2           // XBee Serial port. If you're using FTClicks board it will be one Serial4
static const uint8_t xbee_click = 2
int BAUDRATE = 115200;                // XBee and Serial boudrate, you can set diferent ones if you want but remmeber to check XBee configuration using XCTU
int address_HB = 0x0013A200;          // Most significant bytes from XBee's address
int address_LB = 0x40F67850;          // Least significant bytes from XBee's address
uint8_t payload[100] = {0};
/* *****************************************
 * PROGRAM VARIABLES - AVOID CHANGING THEM
 */
FTTech_Xbee xbee(XBEE_SERIAL);


void setup()
{
  FTClicks.begin();
  Serial.begin(BAUDRATE);

  while (!Serial) delay(10);
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));
  Serial.println(F("FTTech - XBee Sending Test"));
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));

  XBEE_SERIAL.begin(BAUDRATE);
  xbee.begin();
  
  // All the other arduments will be loaded by default, you can chance them by calling begin(Stream &serial, int baudrate, int timeout, int payload_size)
  xbee.setChipID(FTClicks.ChipID);

  // Turn XBee power on
  FTClicks.turnON(xbee_click);

}

void loop()
{
    xbee.messageClearPayload();
    xbee.message("TEST_STR", "12345");
    xbee.sendPayloadBroadcast();

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