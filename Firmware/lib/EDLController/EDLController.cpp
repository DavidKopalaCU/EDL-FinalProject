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

void EDLController::drive_forward_ft(uint8_t feet, uint8_t speed) {
    drive_forward_in(feet * 12, speed);
}

void EDLController::drive_forward_in(uint8_t inches, uint8_t speed) {
    drive_forward_cm(IN_TO_CM(inches), speed);
}

void EDLController::drive_forward_cm(uint8_t cm, uint8_t speed) {
    uint16_t left_pulses = CM_TO_PULSE(cm, 1);
    uint16_t right_pulses = CM_TO_PULSE(cm, 0);

    left_motor->enc_count = 0;
    right_motor->enc_count = 0;

    left_motor->forward(speed * 1.02);
    right_motor->forward(speed);

    bool left_done = false;
    bool right_done = false;
    while (!(left_done && right_done)) {
        if (left_motor->enc_count >= left_pulses) {
            left_motor->stop();
            left_done = true;
        }
        if (right_motor->enc_count >= right_pulses) {
            right_motor->stop();
            right_done = true;
        }
    }
}

void EDLController::pivot_ccw(uint16_t degrees, uint8_t speed) {
    uint16_t left_pulses = DEG_TO_PULSES(degrees, 1);
    uint16_t right_pulses = DEG_TO_PULSES(degrees, 0);

    left_motor->enc_count = 0;
    right_motor->enc_count = 0;

    left_motor->backward(speed * 1.1);
    right_motor->forward(speed);

    bool left_done = false;
    bool right_done = false;

    // while (left_motor->enc_count < left_pulses &&)

    while (!(left_done && right_done)) {
        if (left_motor->enc_count >= left_pulses) {
            left_motor->stop();
            left_done = true;
        }
        if (right_motor->enc_count >= right_pulses) {
            right_motor->stop();
            right_done = true;
        }
    }
}

void EDLController::pivot_cw(uint16_t degrees, uint8_t speed) {
    uint16_t left_pulses = DEG_TO_PULSES(degrees, 1);
    uint16_t right_pulses = DEG_TO_PULSES(degrees, 0);

    left_motor->enc_count = 0;
    right_motor->enc_count = 0;

    left_motor->forward(speed * 1.);
    right_motor->backward(speed);

    bool left_done = false; 
    bool right_done = false;

    while (!(left_done && right_done)) {
        if (left_motor->enc_count >= left_pulses) {
            left_motor->stop();
            left_done = true;
        }
        if (right_motor->enc_count >= right_pulses) {
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