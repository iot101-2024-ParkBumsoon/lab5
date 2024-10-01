#include <Arduino.h>
#include <TFT_eSPI.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHT_PIN 18  // 18번 핀 사용
#define DHT_TYPE DHT22  // DHT 센서 타입

TFT_eSPI tft = TFT_eSPI();  // 디스플레이 설정 
DHT temperatureSensor(DHT_PIN, DHT_TYPE);  

unsigned long previousMillis = 0;  
int interval = 2000;  // 2초 간격

void setup() {
    Serial.begin(115200);  

    tft.init();  // TFT 디스플레이 초기화
    tft.setRotation(3);  // 화면 회전 설정
    tft.fillScreen(TFT_BLACK);  // 화면을 검은색으로 초기화

    temperatureSensor.begin();  // DHT 센서 초기화
}

void loop() {
    unsigned long currentMillis = millis();  // 현재 시간 가져오기

    // 지정된 간격마다 센서 데이터를 읽기
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  // 시간 기록 업데이트

        // DHT 센서에서 온도와 습도 읽기
        float humidity = temperatureSensor.readHumidity();
        float temperature = temperatureSensor.readTemperature();

        //디스플레이에 데이터 출력
        tft.fillScreen(TFT_BLACK);  
        tft.setCursor(10, 10);  
        tft.setTextColor(TFT_WHITE);  
        tft.setTextSize(2);  
        tft.print("Temp: "); tft.print(temperature); tft.println(" C");
        tft.print("Humidity: "); tft.print(humidity); tft.println(" %");

        // 시리얼 모니터에 데이터 출력
        Serial.print("Temperature: "); Serial.print(temperature); Serial.print(" C ");
        Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
    }
}
