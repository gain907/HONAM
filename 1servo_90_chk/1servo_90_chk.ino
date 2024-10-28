#include <Wire.h>
#include "QGPMaker_MotorShield.h"

QGPMaker_MotorShield AFMS = QGPMaker_MotorShield(); // 모터 쉴드 객체 생성
QGPMaker_Servo *Servo1 = AFMS.getServo(1); // 1번 서보모터 객체 생성

void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작 (속도: 9600bps)
  Serial.println("Servo Motor Test!");

  AFMS.begin(50);  // PWM 주파수 설정

  Servo1->writeServo(90); // 1번 서보모터를 90도 위치로 이동
}

void loop() {
  // 메인 루프는 비어 둡니다. setup()에서 이미 서보모터를 90도로 이동시켰습니다.
}

