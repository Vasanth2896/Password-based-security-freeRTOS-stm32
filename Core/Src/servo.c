#include "servo.h"

extern TIM_HandleTypeDef htim2;

void rotateServoMotor(uint16_t angle) {
	uint16_t minPulse = 25;
	uint16_t maxPulse = 125;
	uint16_t pulse = minPulse + ((maxPulse - minPulse) * angle) / 180;

	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse);

}

void lock() {
	rotateServoMotor(0);
}

void unlock() {
	rotateServoMotor(90);
}
