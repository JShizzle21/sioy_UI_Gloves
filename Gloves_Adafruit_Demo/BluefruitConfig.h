//Pin Definitions
#define VOL_UP_PIN A3
#define VOL_DOWN_PIN A2
#define PLAY_PAUSE_PIN A1
#define NEXT_SONG_PIN A0
#define LED LED_BUILTIN

//Pre-defined commands
#define AT_CMD "AT+BleHidControlKey="
#define VOL_UP_CMD "VOLUME+"
#define VOL_DOWN_CMD "VOLUME-"
#define PLAY_PAUSE_CMD "PLAYPAUSE"
#define NEXT_SONG_CMD "MEDIANEXT"

//Analog read values
#define OPERATING_VOLTAGE 3.3
#define THRESHOLD OPERATING_VOLTAGE/2
#define VOLTAGE_CONVERSION OPERATING_VOLTAGE/1023


// COMMON SETTINGS
// ----------------------------------------------------------------------------------------------
// These settings are used in both SW UART, HW UART and SPI mode
// ----------------------------------------------------------------------------------------------
#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   true  // If set to 'true' enables debug output


// SOFTWARE UART SETTINGS
// ----------------------------------------------------------------------------------------------
// The following macros declare the pins that will be used for 'SW' serial.
// You should use this option if you are connecting the UART Friend to an UNO
// ----------------------------------------------------------------------------------------------
#define BLUEFRUIT_SWUART_RXD_PIN       3//7//9    // Required for software serial!
#define BLUEFRUIT_SWUART_TXD_PIN       4//8//10   // Required for software serial!
#define BLUEFRUIT_UART_CTS_PIN         2//9//11   // Required for software serial!
#define BLUEFRUIT_UART_RTS_PIN         -1   // Optional, set to -1 if unused


// HARDWARE UART SETTINGS
// ----------------------------------------------------------------------------------------------
// The following macros declare the HW serial port you are using. Uncomment
// this line if you are connecting the BLE to Leonardo/Micro or Flora
// ----------------------------------------------------------------------------------------------
#ifdef Serial1    // this makes it not complain on compilation if there's no Serial1
  #define BLUEFRUIT_HWSERIAL_NAME      Serial1
#endif


// SHARED UART SETTINGS
// ----------------------------------------------------------------------------------------------
// The following sets the optional Mode pin, its recommended but not required
// ----------------------------------------------------------------------------------------------
#define BLUEFRUIT_UART_MODE_PIN        -1 //12    // Set to -1 if unused


// HARDWARE SPI SETTINGS
// ----------------------------------------------------------------------------------------------
// The following macros declare the pins to use for HW SPI communication.
// SCK, MISO and MOSI should be connected to the HW SPI pins on the Uno, etc.
// This should be used with nRF51822 based Bluefruit LE modules that use SPI.
// ----------------------------------------------------------------------------------------------
#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4    // Optional but recommended, set to -1 if unused
