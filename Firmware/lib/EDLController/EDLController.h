#ifndef EDLCONTROLLER_H
#define EDLCONTROLLER_H

#include "Arduino.h"

#include "EDLMotor.h"

// #define PULSES_PER_ROT      728
#define LEFT_PULSES         743
#define RIGHT_PULSES        733
#define CIRCUMFIRENCE       85 //87.7 //? radius * 2 * pi

#define IN_TO_CM(feet)      (feet * 2.54)
#define CM_TO_PULSE(cm,l)     (l ? ((cm / 40.84) * LEFT_PULSES) : ((cm / 40.84) * RIGHT_PULSES))

// #define DEG_TO_PULSES(deg)  ((deg / 180.0) * 360) // Prolly wrong?
#define DEG_TO_PULSES(deg,l)  ((deg / 360.0) * CM_TO_PULSE(CIRCUMFIRENCE,l))


class EDLController
{
private:

public:
    EDLController(uint8_t left_cc, uint8_t left_cw, uint8_t left_pwm, uint8_t left_enc_a, uint8_t left_enc_b,
                    uint8_t right_cc, uint8_t right_cw, uint8_t right_pwm, uint8_t right_enc_a, uint8_t right_enc_b);
    ~EDLController();

    EDLMotor *left_motor, *right_motor;

    void drive_forward_cm(uint8_t cm, uint8_t speed);
    void drive_forward_in(uint8_t inches, uint8_t speed);
    void drive_forward_ft(uint8_t feet, uint8_t speed);
    void turn_left(uint8_t speed);
    void turn_right(uint8_t speed);
    void pivot_ccw(uint16_t degrees, uint8_t speed);
    void pivot_cw(uint16_t degrees, uint8_t speed);
};

#endif //EDLCONTROLLER_H