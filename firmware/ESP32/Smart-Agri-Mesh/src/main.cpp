#include <Arduino.h>
#include "uart_driver.h"
// #include "Smart-Agri_mesh_inferencing.h"

#define UART_TX 17
#define UART_RX 16
#define baud 9600

HardwareSerial SerialPort(2);

void setup()
{
  Serial.begin(baud);
  SerialPort.begin(baud, SERIAL_8N1, UART_RX, UART_TX);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
