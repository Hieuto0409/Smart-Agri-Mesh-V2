/*
 * uart_driver.c
 *
 *  Created on: Jun 29, 2026
 *      Author: MSI PC
 */

#include <UART/uart_driver.h>
extern UART_HandleTypeDef huart2;

AgriPacket tx_data;

void Send_Data_To_Gateway(float temp, float humi, uint16_t soil_moisture, uint16_t light, uint8_t flags) {
    tx_data.header[0] = 0xAA;
    tx_data.header[1] = 0x55;
    tx_data.node_id   = 0x01;
    tx_data.temp_x10  = (int16_t)(temp * 10);
    tx_data.humi_x10  = (uint16_t)(humi * 10);
    tx_data.soil_moisture = soil_moisture;
    tx_data.light    = light;
    tx_data.status_flags  = flags; // Ví dụ cờ báo bơm đang chạy

    // Tính Checksum = tổng các byte từ node_id đến hết status_flags
    uint8_t *ptr = (uint8_t*)&tx_data;
    tx_data.checksum = 0;
    for(int i = 2; i < sizeof(AgriPacket) - 1; i++) {
        tx_data.checksum += ptr[i];
    }

    // Gửi bay qua UART bằng DMA
    HAL_UART_Transmit_DMA(&huart2, (uint8_t*)&tx_data, sizeof(AgriPacket));
}
