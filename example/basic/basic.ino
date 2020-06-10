#include <SoftPWM.h>
SOFTPWM_DEFINE_CHANNEL(A3); //SoftPWM으로 사용할 핀 설정

void setup() {
  SoftPWM.begin(490); //PWM frequency 설정
}

void loop() {
  int a = map(analogRead(A0), 0, 1023, 0, 100); //duty rate 조절 (0~100%)
  SoftPWM.set(a); 
}
