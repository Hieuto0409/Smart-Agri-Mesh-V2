/*
 * soil_humi.c
 *
 *  Created on: Jun 29, 2026
 *      Author: MSI PC
 */
#include "soil_moisture.h"

extern uint16_t adc_buffer[2];
uint16_t cover_soil(){
	uint16_t soild_raw = adc_buffer[1];      // Giá trị độ ẩm đất (Rank 2)

	// 2. Ví dụ: Tính toán phần trăm ánh sáng (nếu cần)
	// 1756 tương ứng khô nhất, 4095 tương ứng ướt nhất
	if (soild_raw > 4095) soild_raw = 4095;
	if (soild_raw < 0)   soild_raw = 0;
	uint16_t Soild_value = ((4095 - soild_raw)/2339)*100;

	HAL_Delay(1000); // Đọc và gửi định kỳ mỗi 1 giây
	return Soild_value;
}
