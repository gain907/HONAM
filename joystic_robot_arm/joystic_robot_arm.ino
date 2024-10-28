#include <Wire.h>
#include "PS2X_lib.h"
#include "QGPMaker_MotorShield.h"
#include "Ultrasonic.h"
#define TRIGGER_PIN  A0
#define ECHO_PIN     A1

QGPMaker_MotorShield AFMS = QGPMaker_MotorShield();
PS2X ps2x;

long ARM_MIN[] = {10, 10, 40, 10, 10, 70};
long ARM_MAX[] = {170, 140, 170, 102, 170, 125};

// 기본 자세 각도 정의
long ARM_DEFAULT[] = {90, 90, 90, 90, 90, 90};

QGPMaker_Servo *Servo1 = AFMS.getServo(1);
QGPMaker_Servo *Servo2 = AFMS.getServo(2);
QGPMaker_Servo *Servo3 = AFMS.getServo(3);
QGPMaker_Servo *Servo4 = AFMS.getServo(4);
QGPMaker_Servo *Servo5 = AFMS.getServo(5);
QGPMaker_Servo *Servo6 = AFMS.getServo(6);  // 그리퍼 

// 그리퍼 제어 함수
void openGripper() {
  Servo6->writeServo(ARM_MIN[5]);
  delay(300);
}

void closeGripper() {
  Servo6->writeServo(ARM_MAX[5]);
  delay(300);
}

// 천천히 기본 자세로 이동하는 함수
void moveToDefaultPositionSlowly() {
  int stepDelay = 20;  // 각도 변경 후의 대기 시간 (ms)
  
  for (int i = 0; i < 6; i++) {
    long currentPos = 0;
    long targetPos = ARM_DEFAULT[i];
    switch (i) {
      case 0:
        currentPos = Servo1->readDegrees();
        while (currentPos != targetPos) {
          if (currentPos < targetPos) currentPos++;
          else if (currentPos > targetPos) currentPos--;
          Servo1->writeServo(currentPos);
          delay(stepDelay);
        }
        break;
      case 1:
        currentPos = Servo2->readDegrees();
        while (currentPos != targetPos) {
          if (currentPos < targetPos) currentPos++;
          else if (currentPos > targetPos) currentPos--;
          Servo2->writeServo(currentPos);
          delay(stepDelay);
        }
        break;
      case 2:
        currentPos = Servo3->readDegrees();
        while (currentPos != targetPos) {
          if (currentPos < targetPos) currentPos++;
          else if (currentPos > targetPos) currentPos--;
          Servo3->writeServo(currentPos);
          delay(stepDelay);
        }
        break;
      case 3:
        currentPos = Servo4->readDegrees();
        while (currentPos != targetPos) {
          if (currentPos < targetPos) currentPos++;
          else if (currentPos > targetPos) currentPos--;
          Servo4->writeServo(currentPos);
          delay(stepDelay);
        }
        break;
      case 4:
        currentPos = Servo5->readDegrees();
        while (currentPos != targetPos) {
          if (currentPos < targetPos) currentPos++;
          else if (currentPos > targetPos) currentPos--;
          Servo5->writeServo(currentPos);
          delay(stepDelay);
        }
        break;
      case 5:
        currentPos = Servo6->readDegrees();
        while (currentPos != targetPos) {
          if (currentPos < targetPos) currentPos++;
          else if (currentPos > targetPos) currentPos--;
          Servo6->writeServo(currentPos);
          delay(stepDelay);
        }
        break;
    }
  }
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Robot Arm Start!!");
  AFMS.begin(50);
  int error = 0;
  do {
    error = ps2x.config_gamepad(13, 11, 10, 12, true, true);
    if (error == 0) {
      break;
    } else {
      delay(100);
    }
  } while (1);
  Servo1->writeServo(90);
  Servo2->writeServo(90);
  Servo3->writeServo(90);
  Servo4->writeServo(90);
  Servo5->writeServo(90);
  Servo6->writeServo(90);
  // moveToDefaultPositionSlowly();  // 시작 시 기본 자세로 천천히 이동
}

void loop() {
  ps2x.read_gamepad(false, 0);

  if (ps2x.ButtonPressed(PSB_CIRCLE)) {   
    openGripper();
  }
  if (ps2x.ButtonPressed(PSB_SQUARE)) { 
    closeGripper();
  }

  // Triangle 버튼을 누르면 기본 자세로 천천히 이동
  if (ps2x.ButtonPressed(PSB_TRIANGLE)) {
    moveToDefaultPositionSlowly();
  }

  if (ps2x.Analog(PSS_LX) > 240) {
    if (Servo1->readDegrees() > ARM_MIN[0]) {
      Servo1->writeServo((Servo1->readDegrees() - 1));
    }
  } else if (ps2x.Analog(PSS_LX) < 10) {
    if (Servo1->readDegrees() < ARM_MAX[0]) {
      Servo1->writeServo((Servo1->readDegrees() + 1));
    }
  }

  // PSS_LY 방향 반대로 설정
  if (ps2x.Analog(PSS_LY) > 240) {
    if (Servo2->readDegrees() < ARM_MAX[1]) {  // 반대로 변경
      Servo2->writeServo((Servo2->readDegrees() + 1));
    }
  } else if (ps2x.Analog(PSS_LY) < 10) {
    if (Servo2->readDegrees() > ARM_MIN[1]) {  // 반대로 변경
      Servo2->writeServo((Servo2->readDegrees() - 1));
    }
  }

  if (ps2x.Analog(PSS_RY) > 240) {
    if (Servo3->readDegrees() > ARM_MIN[2]) {
      Servo3->writeServo((Servo3->readDegrees() - 1));
    }
  } else if (ps2x.Analog(PSS_RY) < 10) {
    if (Servo3->readDegrees() < ARM_MAX[2]) {
      Servo3->writeServo((Servo3->readDegrees() + 1));
    }
  }

  if (ps2x.Analog(PSS_RX) > 240) {
    if (Servo4->readDegrees() > ARM_MIN[3]) {
      Servo4->writeServo((Servo4->readDegrees() - 1));
    }
  } else if (ps2x.Analog(PSS_RX) < 10) {
    if (Servo4->readDegrees() < ARM_MAX[3]) {
      Servo4->writeServo((Servo4->readDegrees() + 1));
    }
  }

  // Servo5 제어 (D-pad UP/DOWN)
  if (ps2x.Button(PSB_PAD_UP)) {
    if (Servo5->readDegrees() < ARM_MAX[4]) {
      Servo5->writeServo((Servo5->readDegrees() + 1));
    }
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    if (Servo5->readDegrees() > ARM_MIN[4]) {
      Servo5->writeServo((Servo5->readDegrees() - 1));
    }
  }

  // Servo6 제어 (D-pad LEFT/RIGHT)
  if (ps2x.Button(PSB_PAD_LEFT)) {
    if (Servo6->readDegrees() > ARM_MIN[5]) {
      Servo6->writeServo((Servo6->readDegrees() - 1));
    }
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    if (Servo6->readDegrees() < ARM_MAX[5]) {
      Servo6->writeServo((Servo6->readDegrees() + 1));
    }
  }

  delay(10);
}
