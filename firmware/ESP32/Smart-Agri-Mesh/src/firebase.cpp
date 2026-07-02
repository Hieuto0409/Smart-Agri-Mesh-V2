#include "firebase.h"
#include "Firebase_ESP_Client.h"
// Cung cấp các thông tin trợ giúp giao thức mã hóa và token của Firebase
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#include <cstdlib> // Thư viện chứa hàm rand(), srand()
#include <ctime>

int nhiet_do = 0;
int do_am = 0;

#define WIFI_SSID "Hieu"
#define WIFI_PASSWORD "toquanghieu"

// 2. Cấu hình Firebase (API Key lấy từ thông tin dự án)
#define API_KEY "AIzaSyBL5R2bybBW2wauvfFIce6cDO7g21-CshY"

// 3. Đường dẫn URL của Realtime Database
// Sau khi nhấn "Create Database", bạn copy đường dẫn URL dạng "https://...firebasedatabase.app/" dán vào đây
#define DATABASE_URL "https://smart-agri-mesh-f9235-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void Firebase_Init()
{
    // Kết nối WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Đang kết nối WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Đã kết nối WiFi thành công với IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    // Cấu hình các thông số Firebase
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    // Đăng ký tài khoản ẩn danh (Annonymous) hoặc sử dụng chế độ Test Mode dữ liệu tự do
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("Kết nối Firebase thành công!");
        signupOK = true;
    }
    else
    {
        Serial.printf("Lỗi kết nối Firebase: %s\n", config.signer.signupError.message.c_str());
    }

    // Khởi tạo thư viện
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

void Firebase_Loop()
{
    // Gửi dữ liệu mỗi 10 giây một lần (tránh gửi quá liên tục làm nghẽn băng thông)
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 10000 || sendDataPrevMillis == 0))
    {
        sendDataPrevMillis = millis();

        // Giả lập dữ liệu đọc từ cảm biến
        srand(time(0));
        nhiet_do = 1 + rand() % 100;
        do_am = 1 + rand() % 100;

        // Gửi giá trị nhiệt độ lên nhánh "/smart-agri/nhiet_do"
        if (Firebase.RTDB.setInt(&fbdo, "/smart-agri/nhiet_do", nhiet_do))
        {
            Serial.print("Đã gửi Nhiệt độ: ");
            Serial.println(nhiet_do);
        }
        else
        {
            Serial.print("Lỗi gửi dữ liệu nhiệt độ: ");
            Serial.println(fbdo.errorReason());
        }

        // Gửi giá trị độ ẩm lên nhánh "/smart-agri/do_am"
        if (Firebase.RTDB.setInt(&fbdo, "/smart-agri/do_am", do_am))
        {
            Serial.print("Đã gửi Độ ẩm: ");
            Serial.println(do_am);
        }
        else
        {
            Serial.print("Lỗi gửi dữ liệu độ ẩm: ");
            Serial.println(fbdo.errorReason());
        }
    }
}