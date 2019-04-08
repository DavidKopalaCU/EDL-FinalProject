#include "EDLMotor.h"

EDLMotor::EDLMotor(
        uint8_t ccw_enable,
        uint8_t cc_enable,
        uint8_t pwm_speed,
        uint8_t enc_a,
        uint8_t enc_b)
{
    this->ccw_enable = ccw_enable;
    this->cc_enable = cc_enable;
    this->pwm_speed = pwm_speed;
    this->enc_a = enc_a;
    this->enc_b = enc_b;

    pinMode(ccw_enable, OUTPUT);
    pinMode(cc_enable, OUTPUT);
    pinMode(pwm_speed, OUTPUT);

    pinMode(enc_a, INPUT);
    if (enc_b != 0) {
        pinMode(enc_b, INPUT);
    }
}

EDLMotor::~EDLMotor()
{
}


void EDLMotor::forward(uint8_t speed) {
    digitalWrite(cc_enable, LOW);
    digitalWrite(ccw_enable, HIGH);

    analogWrite(pwm_speed, speed);
}

void EDLMotor::backward(uint8_t speed) {
    digitalWrite(ccw_enable, LOW);
    digitalWrite(cc_enable, HIGH);

    analogWrite(pwm_speed, speed);
}

void EDLMotor::stop() {
    digitalWrite(ccw_enable, LOW);
    digitalWrite(cc_enable, LOW);

    analogWrite(pwm_speed, 0);
}