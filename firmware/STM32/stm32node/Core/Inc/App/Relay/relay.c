/*
 * relay.c
 *
 *  Created on: Jun 29, 2026
 *      Author: MSI PC
 */

#include "relay.h"

uint8_t is_relay = 1; //  trạng thái ban đầu là tắt

void Relay_Init(){
	HAL_GPIO_WritePin(GPIOA, Relay_Pin, is_relay);

	HAL_Delay(100);
}
