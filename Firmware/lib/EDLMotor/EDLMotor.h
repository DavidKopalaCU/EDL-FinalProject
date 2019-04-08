#ifndef EDLMOTOR_H
#define EDLMOTOR_H

#include "Arduino.h"

class EDLMotor
{
private:
    uint8_t ccw_enable;
    uint8_t cc_enable;
    uint8_t pwm_speed;
    uint8_t enc_a;
    uint8_t enc_b;

public:
    EDLMotor(
        uint8_t ccw_enable,
        uint8_t cc_enable,
        uint8_t pwm_speed,
        uint8_t enc_a,
        uint8_t enc_b
    );
    ~EDLMotor();

    uint8_t get_enc_pin() {return enc_a;}
    volatile int enc_count = 0;

    void forward(uint8_t speed);
    void backward(uint8_t speed);
    void stop();
};


#endif //EDLMOTOR_H