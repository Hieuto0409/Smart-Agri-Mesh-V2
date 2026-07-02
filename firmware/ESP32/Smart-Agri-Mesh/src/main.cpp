#include <Arduino.h>
// #include "uart_driver.h"
#include "firebase.h"

#define UART_TX 17
#define UART_RX 16
#define baud 115200

HardwareSerial SerialPort(2);

void setup()
{
  Serial.begin(baud);
  SerialPort.begin(baud, SERIAL_8N1, UART_RX, UART_TX);
  Firebase_Init();
}

void loop()
{
  Firebase_Loop();
}
