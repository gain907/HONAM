#include <Wire.h>
#include "QGPMaker_MotorShield.h"

QGPMaker_MotorShield AFMS = QGPMaker_MotorShield(); // 모터 쉴드 객체 생성
QGPMaker_Servo *Servo1 = AFMS.getServo(1); // 1번 서보모터 객체 생성

int currentAngle = 90;  // 서보모터의 초기 각도

void setup() {
  Serial.begin(9600);           // 시리얼 통신 시작 (속도: 9600bps)
  Serial.println("Servo Motor Control Test!");

  AFMS.begin(50);  // PWM 주파수 설정

  Servo1->writeServo(currentAngle); // 초기 위치를 90도로 설정
}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.parseInt();  // 시리얼 입력 값 읽기

    if (command == 1) {
      currentAngle += 10;  // 10도씩 증가
      if (currentAngle > 170) currentAngle = 170; // 각도 최대값을 170도로 제한
      Servo1->writeServo(currentAngle);  // 각도 증가
      Serial.println("Servo 1 increased by 1 degree.");
    } 
    else if (command == 2) {
      currentAngle -= 10;
      if (currentAngle < 10) currentAngle = 10; // 각도 최소값을 10도로 제한
      Servo1->writeServo(currentAngle);  // 각도 감소
      Serial.println("Servo 1 decreased by 1 degree.");
    } 
    else if (command == 3) {
      currentAngle = 90;
      Servo1->writeServo(currentAngle);  // 각도를 90도로 설정
      Serial.println("Servo 1 moved to 90 degrees.");
    } 
    else {
      Serial.println("Invalid command. Please enter 1, 2, or 3.");
    }

    // 현재 서보모터의 각도 출력
    Serial.print("Current Servo 1 Angle: ");
    Serial.println(currentAngle);
  }
}
