//header에서 정의한 함수를 사용해야하기 때문에 inline함수 쓰는거
//헤더에서 함수를 정의해도 main에서만 include를 한다면 에러가 없을텐데
//여러 파일에서 헤더를 정의하게되면 해당 함수가 여러번 정의되어 에러발생
//한 줄을 건너뛰어도 안됨

//전처리문은 한줄만 처리하기 때문에 backspace를 사용하여 전처리가 처리할 수 있는 형태로 define을 만들어 주어야함

#include "TEST.h"
//using namespace Palatis;
  1
int a = 0;
extern int aa;
int b;
template<int xx> inline int foo(int x) {
  return xx + x;
}

//TEST(7);
//SOFTPWM_DEFINE_CHANNEL(5, DDRF, PORTF, PORTF3);  //Arduino pin 0

void setup() {
  int c = foo<3>(5);
  Serial.begin(115200);
  Serial.println(c);
}

void loop() {

}
