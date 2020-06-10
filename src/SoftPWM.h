#ifndef _SOFTPWM_H_
#define _SOFTPWM_H_
#include <stdint.h>
#include <Arduino.h>

//#define SOFTPWM_PIN_DEFINE(PIN)\
//  CSoftPWM<PIN> SoftPWM;\
//  ISR(TIMER1_COMPA_vect) { \
//    interrupts(); \
//    SoftPWM.update(); \
//  }

#define SOFTPWM_DEFINE_CHANNEL(PIN)\
  CSoftPWM SoftPWM(PIN);\
  ISR(TIMER1_COMPA_vect) { \
    interrupts(); \
    SoftPWM.update(); \
  }

//template<uint8_t _pin>
class CSoftPWM {
  private:
    uint8_t _channels;
    uint8_t _count;
    unsigned int num_PWM_levels;
    uint8_t _pin;

  public:
    //    CSoftPWM()
    //    {
    //      num_PWM_levels = 100;
    //      pinMode(_pin, OUTPUT);
    //    }
    CSoftPWM(uint8_t PIN)
      : _pin(PIN)
    {
      num_PWM_levels = 100;
      pinMode(_pin, OUTPUT);
    }
    void begin(const unsigned long hertz)
    {
      allOff();  //this prevents inverted channels from momentarily going LOW
      const uint8_t oldSREG = SREG;
      noInterrupts();
      SREG = oldSREG;

      //the setup of timer1 is stolen from ShiftPWM
      TCCR1A = 0b00000000;
      TCCR1B = 0b00001001;
      OCR1A = (F_CPU - hertz * PWMlevels() / 2) / (hertz * PWMlevels());
      bitSet(TIMSK1, OCIE1A);
      _count = 0;
    }
    unsigned int PWMlevels() const {
      return num_PWM_levels ? num_PWM_levels : 256;
    }
    void set(const uint8_t value)
    {
      _channels = value;
    }

    void allOff()
    {
      const uint8_t oldSREG = SREG;
      noInterrupts();
      _channels = 0;
      SREG = oldSREG;
    }

    /* This function cannot be private because the ISR uses it, and I have
       no idea about how to make friends with ISR. :-( */
    void update() __attribute__((always_inline))
    {
      const uint8_t count = _count;
      bitWriteStaticExpander(count, _channels);
      ++_count;
      if (_count == PWMlevels())
        _count = 0;
    }

    void bitWriteStaticExpander(uint8_t const &c, uint8_t const &channels)
    {
      bool const value = (c < channels);
      digitalWrite(_pin, value);
    }
};

#endif
