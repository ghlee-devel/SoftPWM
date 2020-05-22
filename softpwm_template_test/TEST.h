#define TEST(CHANNEL) \
  template<> inline void test<CHANNEL>(int value) {\
    a = value; \
  }

#include <Arduino.h>
int aa = 10;

template <int channel> inline void bitWriteStatic(bool value) {}
#define SOFTPWM_DEFINE_CHANNEL(CHANNEL, PMODE, PORT, BIT) \
  template <> inline void bitWriteStatic<CHANNEL>(bool value) { \
    bitWrite( PORT, BIT, value ); \
    aa = BIT;\
  } 
  
  //SOFTPWM_DEFINE_PINMODE(CHANNEL, PMODE, PORT, BIT)


#define SOFTPWM_DEFINE_PINMODE(CHANNEL, PMODE, PORT, BIT) \
  template <> inline void pinModeStatic<CHANNEL>(uint8_t const mode) { \
    if (mode == INPUT) { bitClear(PMODE, BIT); bitClear(PORT, BIT); } \
    else if (mode == INPUT_PULLUP) { bitClear(PMODE, BIT); bitSet(PORT, BIT); } \
    else { bitSet(PMODE, BIT); }\
  } \


//namespace Palatis {

template <int channel> inline void pinModeStatic(uint8_t mode) {}
template <int channel> inline void test(int value) {}
//}
