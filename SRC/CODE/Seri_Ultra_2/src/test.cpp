#include <Wire.h>

// Địa chỉ I2C của các PCF8575 (thay đổi nếu cần)
#define PCF8575_POWER 0x25 // Điều khiển chân POWER
#define PCF8575_TRIG  0x27 // Điều khiển chân TRIG
#define PCF8575_ECHO  0x26 // Điều khiển chân ECHO

// Số lượng cảm biến
#define NUM_SENSORS 16

// Thời gian chờ tối đa (us) để đo khoảng cách
#define TIMEOUT 25000 // ~4m khoảng cách tối đa

// Hàm ghi dữ liệu vào PCF8575
void writePCF8575(uint8_t address, uint16_t data) {
    Wire.beginTransmission(address);
    Wire.write(lowByte(data)); // Gửi byte thấp
    Wire.write(highByte(data)); // Gửi byte cao
    Wire.endTransmission();
}

// Hàm đọc dữ liệu từ PCF8575
uint16_t readPCF8575(uint8_t address) {
    //
    Wire.requestFrom((uint8_t)address, (uint8_t)2);
    uint16_t data = Wire.read(); // Byte thấp
    data |= (Wire.read() << 8); // Byte cao
    return data;
}

// Điều khiển chân POWER của cảm biến thứ index
void setPower(uint8_t index, bool state) {
    static uint16_t powerState = 0x0000; // Trạng thái hiện tại của PCF8575_POWER
    if (state) {
        powerState |= (1 << index); // Bật chân
    } else {
        powerState &= ~(1 << index); // Tắt chân
    }
    writePCF8575(PCF8575_POWER, powerState);
}

// Điều khiển chân TRIG của cảm biến thứ index
void setTrig(uint8_t index, bool state) {
    static uint16_t trigState = 0x0000; // Trạng thái hiện tại của PCF8575_TRIG
    if (state) {
        trigState |= (1 << index); // Bật chân
    } else {
        trigState &= ~(1 << index); // Tắt chân
    }
    writePCF8575(PCF8575_TRIG, trigState);
}

// Đọc trạng thái chân ECHO của cảm biến thứ index
bool readEcho(uint8_t index) {
    uint16_t echoState = readPCF8575(PCF8575_ECHO);
    return (echoState & (1 << index)) != 0; // Trả về trạng thái chân ECHO
}

// Đo khoảng cách từ cảm biến thứ index (đơn vị: cm)
float measureDistance(uint8_t index) {
    // Bật nguồn cảm biến
    setPower(index, HIGH);
    delay(10); // Chờ cảm biến ổn định

    // Gửi xung TRIG
    setTrig(index, HIGH);
    delayMicroseconds(10); // Xung 10us
    setTrig(index, LOW);

    // Đo thời gian ECHO
    unsigned long startTime = micros();
    while (!readEcho(index)) { // Chờ ECHO HIGH
        if (micros() - startTime > TIMEOUT) {
        setPower(index, LOW); // Tắt cảm biến
        return -1; // Timeout
        }
    }

    unsigned long echoStart = micros();
    while (readEcho(index)) { // Chờ ECHO LOW
        if (micros() - echoStart > TIMEOUT) {
        setPower(index, LOW); // Tắt cảm biến
        return -1; // Timeout
        }
    }
    unsigned long echoTime = micros() - echoStart;

    // Tắt nguồn cảm biến
    setPower(index, LOW);

    // Tính khoảng cách (cm) = (thời gian * tốc độ âm thanh) / 2
    float distance = (echoTime * 0.034) / 2;
    return distance;
}

// Hàm khởi tạo I2C và PCF8575
void setup() {
    // Khởi tạo I2C
    Wire.begin();
    Serial.begin(9600); // Khởi tạo Serial để debug
  
    // Khởi tạo tất cả các chân PCF8575 ở trạng thái LOW
    for (int i = 0; i < NUM_SENSORS; i++) {
        //
        setPower(i, LOW); // Tắt nguồn cảm biến
        setTrig(i, LOW);  // Tắt TRIG
  }
}

// Vòng lặp chính
void loop() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        //
        float distance = measureDistance(i); // Đo khoảng cách từ cảm biến thứ i
        Serial.print("Sensor ");
        Serial.print(i);
        Serial.print(": ");
        if (distance >= 0) {
            Serial.print(distance);
            Serial.println(" cm");
        } else {
            Serial.println("Error");
        }
        delay(100); // Chờ trước khi đo cảm biến tiếp theo
    }
    Serial.println("----------------");
    delay(500); // Chờ trước khi lặp lại
}