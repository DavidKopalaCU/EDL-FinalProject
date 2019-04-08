#include "EDLController.h"

EDLController::EDLController(uint8_t left_cc, uint8_t left_cw, uint8_t left_pwm, uint8_t left_enc_a, uint8_t left_enc_b,
                                uint8_t right_cc, uint8_t right_cw, uint8_t right_pwm, uint8_t right_enc_a, uint8_t right_enc_b)
{
    left_motor = new EDLMotor(left_cc, left_cw, left_pwm, left_enc_a, left_enc_b);
    right_motor = new EDLMotor(right_cc, right_cw, right_pwm, right_enc_a, right_enc_b);
}

EDLController::~EDLController()
{
}

void EDLController::drive_forward(uint8_t feet, uint8_t speed) {
    uint16_t pulses = FT_TO_PULSE(feet);

    left_motor->enc_count = 0;
    right_motor->enc_count = 0;

    left_motor->forward(speed);
    right_motor->forward(speed);

    bool left_done = false;
    bool right_done = false;
    while (!(left_done && right_done)) {
        if (left_motor->enc_count >= pulses) {
            left_motor->stop();
            left_done = true;
        }
        if (right_motor->enc_count >= pulses) {
            right_motor->stop();
            right_done = true;
        }
    }
}

void EDLController::pivot_ccw(uint16_t degrees, uint8_t speed) {
    uint16_t pulses = DEG_TO_PULSES(degrees);

    left_motor->enc_count = 0;
    right_motor->enc_count = 0;

    left_motor->backward(speed);
    right_motor->forward(speed);

    bool left_done = false;
    bool right_done = false;

    while (!(left_done && right_done)) {
        if (left_motor->enc_count >= pulses) {
            left_motor->stop();
            left_done = true;
        }
        if (right_motor->enc_count >= pulses) {
            right_motor->stop();
            right_done = true;
        }
    }
}

void EDLController::pivot_cw(uint16_t degrees, uint8_t speed) {
    uint16_t pulses = DEG_TO_PULSES(degrees);

    left_motor->enc_count = 0;
    right_motor->enc_count = 0;

    left_motor->forward(speed);
    right_motor->backward(speed);

    bool left_done = false;
    bool right_done = false;

    while (!(left_done && right_done)) {
        if (left_motor->enc_count >= pulses) {
            left_motor->stop();
            left_done = true;
        }
        if (right_motor->enc_count >= pulses) {
            right_motor->stop();
            right_done = true;
        }
    }
}

void EDLController::turn_left(uint8_t speed) {
    pivot_ccw(90, speed);
}

void EDLController::turn_right(uint8_t speed) {
    pivot_cw(90, speed);
}