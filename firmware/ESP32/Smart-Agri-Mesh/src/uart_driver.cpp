#include "uart_driver.h"

#pragma pack(push, 1) // Cực kỳ quan trọng: Ép trình biên dịch không được tự động chèn byte trống (memory padding)
typedef struct
{
    uint8_t header[2]; // 2 Byte cố định đánh dấu bắt đầu (vd: 0xAA, 0x55)
    uint8_t node_id;   // ID của node STM32 (vd: Node số 1)

    int16_t temp_x10;       // Nhiệt độ x10 (vd: 27.5 độ -> gửi số nguyên 275)
    uint16_t humi_x10;      // Độ ẩm kk x10 (vd: 68.2% -> gửi 682)
    uint16_t soil_moisture; // Giá trị ADC độ ẩm đất (0 - 4095)
    uint16_t battery_mv;    // Điện áp pin (vd: pin 3750 mV)

    uint8_t status_flags; // Cờ trạng thái (Bit 0: Bơm đang bật/tắt, Bit 1: Lỗi cảm biến...)
    uint8_t checksum;     // Mã kiểm tra toàn vẹn dữ liệu
} AgriPacket;
#pragma pack(pop)

AgriPacket rx_data;
uint8_t raw_buf[sizeof(AgriPacket)];

void Read_STM32_UART()
{
    if (Serial2.available() >= sizeof(AgriPacket))
    {
        if (Serial2.read() == 0xAA)
        {
            if (Serial2.peek() == 0x55)
            {

                raw_buf[0] = 0xAA;
                Serial2.readBytes(&raw_buf[1], sizeof(AgriPacket) - 1);

                // Kiểm tra Checksum
                uint8_t calc_sum = 0;
                for (int i = 2; i < sizeof(AgriPacket) - 1; i++)
                {
                    calc_sum += raw_buf[i];
                }

                if (calc_sum == raw_buf[sizeof(AgriPacket) - 1])
                {
                    // DỮ LIỆU CHUẨN 100%! Ép kiểu ngược lại
                    memcpy(&rx_data, raw_buf, sizeof(AgriPacket));

                    float real_temp = rx_data.temp_x10 / 10.0;
                    float real_humi = rx_data.humi_x10 / 10.0;

                    // Xử lý đẩy lên Mesh hoặc đưa vào AI Model ở đây
                }
                else
                {
                    // Dữ liệu bị nhiễu trên đường truyền -> Bỏ qua gói này, không được kích bơm bậy bạ
                }
            }
        }
    }
}