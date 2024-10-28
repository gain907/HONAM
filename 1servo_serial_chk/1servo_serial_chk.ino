#include <Wire.h>
#include "QGPMaker_MotorShield.h"

QGPMaker_MotorShield AFMS = QGPMaker_MotorShield(); // 모터 쉴드 객체 생성
QGPMaker_Servo *Servo1 = AFMS.getServo(1); // 1번 서보모터 객체 생성

void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작 (속도: 9600bps)
  Serial.println("Servo Motor Control Test!");

  AFMS.begin(50);  // PWM 주파수 설정

  Servo1->writeServo(90); // 초기 위치를 90도로 설정
}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.parseInt();  // 시리얼 입력 값 읽기

    if (command == 1) {
      Servo1->writeServo(40);  // 40도로 이동
      Serial.println("Servo 1 moved to 40 degrees.");
    } 
    else if (command == 2) {
      Servo1->writeServo(140);  // 140도로 이동
      Serial.println("Servo 1 moved to 140 degrees.");
    } 
    else if (command == 3) {
      Servo1->writeServo(90);  // 90도로 이동
      Serial.println("Servo 1 moved to 90 degrees.");
    } 
    else {
      Serial.println("Invalid command. Please enter 1, 2, or 3.");
    }

    // 현재 서보모터의 각도 출력
    int currentAngle = Servo1->readDegrees();
    Serial.print("Current Servo 1 Angle: ");
    Serial.println(currentAngle);
  }
}
