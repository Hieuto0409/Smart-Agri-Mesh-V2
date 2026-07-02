#ifndef INC_UART_UART_DRIVER_H_
#define INC_UART_UART_DRIVER_H_
#include "Arduino.h"

extern float real_temp;
extern float real_humi;
extern float real_soil_moisture;
extern float real_light;
extern float real_pump_status;

void Read_STM32_UART();
#endif /* INC_UART_UART_DRIVER_H_ */