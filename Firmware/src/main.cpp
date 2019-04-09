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

#define SWITCH_PIN		6

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

	pinMode(SWITCH_PIN, INPUT);
}

void ec() {
	uint8_t st_speed = 70;
	uint8_t tr_speed = 70;
	controller->drive_forward_cm(100, st_speed);
	delay(100);
	controller->turn_left(tr_speed);
	delay(100);
	controller->drive_forward_cm(200, st_speed);
	delay(100);
	controller->turn_right(tr_speed);
	delay(100);
	controller->drive_forward_cm(100, st_speed);
	delay(100);
	controller->turn_right(tr_speed);
	delay(100);
	controller->drive_forward_cm(100, st_speed);
	delay(100);
	controller->turn_right(tr_speed);
	delay(100);
	controller->drive_forward_cm(200, st_speed);
	delay(100);
	controller->turn_left(tr_speed);
	delay(100);
	controller->drive_forward_cm(100, st_speed);
	delay(100);
	controller->turn_left(tr_speed);
	delay(100);
}

void demo() {
	delay(1000);

	uint8_t st_speed = 100;
	uint8_t tr_speed = 50;
	controller->drive_forward_ft(2, st_speed);
	delay(200);
	controller->pivot_cw(180, tr_speed);
	delay(200);
	controller->drive_forward_ft(2, st_speed);
	delay(200);
	controller->pivot_ccw(180, tr_speed);

}

void enc_exp() {
	delay(1000);

	char buff[50];
	sprintf(buff, "LEFT: %d\tRIGHT: %d\n", controller->left_motor->enc_count, controller->right_motor->enc_count);
	Serial.print(buff);
}

void loop() {
	// put your main code here, to run repeatedly:

	// controller->drive_forward_ft(2, 127);
	// delay(1500);
	// controller->pivot_ccw(360, 70);

	do {} while (!digitalRead(SWITCH_PIN));
	// ec();
	demo();
	// enc_exp();
	
	
}