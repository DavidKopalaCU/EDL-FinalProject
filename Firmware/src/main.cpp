#include <Arduino.h>

#include "EDLController.h"

#define LEFT_CCW      8
#define LEFT_CW       7
#define LEFT_PWM      9
#define LEFT_ENC_A    2
#define LEFT_ENC_B    0

#define RIGHT_CCW     12
#define RIGHT_CW      11
#define RIGHT_PWM     10
#define RIGHT_ENC_A   3
#define RIGHT_ENC_B   0

EDLController *controller;

void inc_left() {
	controller->left_motor->enc_count++;
}

void inc_right() {
	controller->right_motor->enc_count++;
}

void setup() {
  // put your setup code here, to run once:

	Serial.begin(9600);
	controller = new EDLController(LEFT_CCW, LEFT_CW, LEFT_PWM, LEFT_ENC_A, LEFT_ENC_B,
									RIGHT_CCW, RIGHT_CW, RIGHT_PWM, RIGHT_ENC_A, RIGHT_ENC_B);

	attachInterrupt(digitalPinToInterrupt(controller->left_motor->get_enc_pin()), inc_left, RISING);
	attachInterrupt(digitalPinToInterrupt(controller->right_motor->get_enc_pin()), inc_right, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

  controller->drive_forward(2, 127);
  delay(1500);
}