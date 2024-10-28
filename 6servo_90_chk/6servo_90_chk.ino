#include <Wire.h>
#include "QGPMaker_MotorShield.h"

QGPMaker_MotorShield AFMS = QGPMaker_MotorShield(); // 모터 쉴드 객체 생성

// 6개의 서보모터 객체 생성
QGPMaker_Servo *Servo1 = AFMS.getServo(1); 
QGPMaker_Servo *Servo2 = AFMS.getServo(2); 
QGPMaker_Servo *Servo3 = AFMS.getServo(3); 
QGPMaker_Servo *Servo4 = AFMS.getServo(4); 
QGPMaker_Servo *Servo5 = AFMS.getServo(5); 
QGPMaker_Servo *Servo6 = AFMS.getServo(6); 

void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작 (속도: 9600bps)
  Serial.println("Servo Motor Test!");

  AFMS.begin(50);  // PWM 주파수 설정

  // 각 서보모터를 90도 위치로 이동
  Servo1->writeServo(90);
  Servo2->writeServo(90);
  Servo3->writeServo(90);
  Servo4->writeServo(90);
  Servo5->writeServo(90);
  Servo6->writeServo(90);
}

void loop() {
  // 메인 루프는 비어 둡니다. setup()에서 이미 서보모터를 90도로 이동시켰습니다.
}
