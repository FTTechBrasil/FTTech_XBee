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
static const uint8_t xbee_click = 4
int BAUDRATE = 115200;                      // XBee and Serial boudrate, you can set diferent ones if you want but remmeber to check XBee configuration using XCTU
uint8_t powerLevel = 3;                     // XBee's PowerLevel, 4 is maximum
/* *****************************************
 * PROGRAM VARIABLES - AVOID CHANGING THEM
 */
FTTech_Xbee xbee();

void setup()
{
  FTClicks.begin();
  
  // Turn XBee power on
  FTClicks.turnON(xbee_click);
  
  Serial.begin(BAUDRATE);

  while (!Serial) delay(10);
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));
  Serial.println(F("FTTech - Test XBee Set PowerLevel"));
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));

  xbee.begin(BAUDRATE);
  
  delay(5000);
  if(xbee.receivePowerLevel())
  {
    Serial.print(F("PowerLevel is set to: ")); Serial.println(xbee.getPowerLevel());
  }
  
  // Set PowerLevel to desired value
  if(xbee.setPowerLevel(powerLevel))
  {
    Serial.print(F("Success!! PowerLevel is now set to: ")); Serial.println(xbee.getPowerLevel());
    
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
}
