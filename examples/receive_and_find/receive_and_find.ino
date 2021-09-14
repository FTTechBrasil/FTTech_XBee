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
 * This is an example to test receiving messages from your FTClick with an XBee
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
static const uint8_t xbee_click = 4
int BAUDRATE = 115200;                //XBee and Serial boudrate, you can set diferent ones if you want but remmeber to check XBee configuration using XCTU
char target_rick[] = "Never Gonna";   //Message to be found inside received package


/* *****************************************
 * PROGRAM VARIABLES - AVOID CHANGING THEM
 */
FTTech_Xbee xbee();

void setup()
{
  FTClicks.begin();
  Serial.begin(BAUDRATE);

  while (!Serial) delay(10);
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));
  Serial.println(F("FTTech - XBee Receiving Test"));
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));

  xbee.begin(BAUDRATE);

  // Turn XBee power on
  FTClicks.turnON(xbee_click);

}

void loop()
{
  // Read message and try to find target_rick inside it
  if (xbee.readAndFindData(target_rick))
  {
    Serial.println(F("Target found"));
  }
  else if(xbee.getInLength()>0)
  {
    Serial.println(F("Target not found in received string"));
  }
  
  if(xbee.getInLength()>0)
  {
    Serial.print(F("Received String: ")); Serial.print(xbee.getInPayload());
    Serial.print(F("\tLength: ")); Serial.println(xbee.getInLength());
    Serial.println();  
  }
}