/*
 * light_sensor.c
 *
 *  Created on: Jun 29, 2026
 *      Author: MSI PC
 */
#include "Light_Sensor/light_sensor.h"
extern uint16_t adc_buffer[2];
uint16_t cover_light(){
	uint16_t light_raw = adc_buffer[0];      // Giá trị ánh sáng (Rank 1)

	// 2. Ví dụ: Tính toán phần trăm ánh sáng (nếu cần)
	// 0 tương ứng trời tối nhất, 4095 tương ứng trời sáng nhất (hoặc ngược lại tùy loại mạch cảm biến)
	if (light_raw > 4064) light_raw = 4064;
	if (light_raw < 54)   light_raw = 54;
	uint16_t Light_value = ((4064 - light_raw)/4010)*100;

	HAL_Delay(1000); // Đọc và gửi định kỳ mỗi 1 giây
	return Light_value;
}

