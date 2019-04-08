#ifndef EDLCONTROLLER_H
#define EDLCONTROLLER_H

#include "Arduino.h"

#include "EDLMotor.h"

#define PULSES_PER_ROT      730
#define CIRCUMFIRENCE       2 //? radius * 2 * pi

#define FT_TO_CM(feet)      (feet * 30)
#define FT_TO_PULSE(feet)   ((FT_TO_CM(feet) / 20) * PULSES_PER_ROT)

#define DEG_TO_PULSES(deg)  ((deg / 180) * 360) // Prolly wrong?
// #define DEG_TO_PULSES(deg)  ((deg * FT_TO_PULSE(CIRCUMFIRENCE)) / 360)


class EDLController
{
private:

public:
    EDLController(uint8_t left_cc, uint8_t left_cw, uint8_t left_pwm, uint8_t left_enc_a, uint8_t left_enc_b,
                    uint8_t right_cc, uint8_t right_cw, uint8_t right_pwm, uint8_t right_enc_a, uint8_t right_enc_b);
    ~EDLController();

    EDLMotor *left_motor, *right_motor;

    void drive_forward(uint8_t feet, uint8_t speed);
    void turn_left(uint8_t speed);
    void turn_right(uint8_t speed);
    void pivot_ccw(uint16_t degrees, uint8_t speed);
    void pivot_cw(uint16_t degrees, uint8_t speed);
};

#endif //EDLCONTROLLER_H