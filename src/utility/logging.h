#ifndef __LOGGING_H__
#define __LOGGING_H__

/*
 * This logging was taken from UIPEthernet on https://github.com/UIPEthernet/UIPEthernet.
 *
 */

#if defined(ARDUINO)
  #include <Arduino.h>
#endif

#define	LOG_NONE		   -1	  /* Logging nothing */
#define	LOG_EMERG		    0	  /* system is unusable */
#define	LOG_ALERT		    1	  /* action must be taken immediately */
#define	LOG_CRIT		    2	  /* critical conditions */
#define	LOG_ERR			    3	  /* error conditions */
#define	LOG_WARNING		  4	  /* warning conditions */
#define	LOG_NOTICE		  5	  /* normal but significant condition */
#define	LOG_INFO		    6	  /* informational */
#define	LOG_DEBUG		    7	  /* debug-level messages */
#define	LOG_DEBUG_V1		8	  /* debug-verbose-level (v) messages */
#define	LOG_DEBUG_V2		9	  /* debug-verbose-level (vv) messages */
#define	LOG_DEBUG_V3		10	/* debug-verbose-level (vvv) messages */

/**
 * To see the warnings, you have to go to 
 * File>Prefences>Compile Warning>(Choose any level diferent from None)
 * in your Arduino IDE. 
 */
#warning "You can configure LogObject and ACTLOGLEVEL in 'utility/logging.h'. More verbosity more memory usage."
//#define ACTLOGLEVEL     LOG_DEBUG_V3
#define ACTLOGLEVEL     LOG_INFO

#if ACTLOGLEVEL>LOG_NONE 
   #if defined(ARDUINO)
     #define default_message                    Serial.print(F("[FT-XBEE] "));

     #define first_uart_send_str(x)             default_message Serial.print(x)
     #define first_uart_send_strln(x)           default_message Serial.println(x)
     #define first_uart_send_dec(x)             default_message Serial.print(x)
     #define first_uart_send_decln(x)           default_message Serial.println(x)
     #define first_uart_send_hex(x)             default_message Serial.print(x,HEX)
     #define first_uart_send_hexln(x)           default_message Serial.println(x,HEX)
     #define first_uart_send_bin(x)             default_message Serial.print(x,BIN)
     #define first_uart_send_binln(x)           default_message Serial.println(x,BIN)
     #define first_uart_send_buf_len(buf,len)   default_message Serial.write(buf,len)

     #define uart_send_str(x)             Serial.print(x)
     #define uart_send_strln(x)           Serial.println(x)
     #define uart_send_dec(x)             Serial.print(x)
     #define uart_send_decln(x)           Serial.println(x)
     #define uart_send_hex(x)             Serial.print(x,HEX)
     #define uart_send_hexln(x)           Serial.println(x,HEX)
     #define uart_send_bin(x)             Serial.print(x,BIN)
     #define uart_send_binln(x)           Serial.println(x,BIN)
     #define uart_send_buf_len(buf,len)   Serial.write(buf,len)
   #endif
#endif

#endif
