#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "state.h"
#define KEYPAD_ROW1_PIN GPIO_PIN_0
#define KEYPAD_ROW2_PIN GPIO_PIN_1
#define KEYPAD_ROW3_PIN GPIO_PIN_2
#define KEYPAD_ROW4_PIN GPIO_PIN_3

#define KEYPAD_COLUMN1_PIN GPIO_PIN_8
#define KEYPAD_COLUMN2_PIN GPIO_PIN_9
#define KEYPAD_COLUMN3_PIN GPIO_PIN_10
#define KEYPAD_COLUMN4_PIN GPIO_PIN_11

#define KEYPAD_PORT GPIOD

#define ROWS 4
#define COLUMNS 4

static const char keypadMap[ROWS][COLUMNS] = { { '1', '2', '3', 'A' }, { '4', '5', '6',
		'B' }, { '7', '8', '9', 'C' }, { '*', '0', '#', 'D' },

};

static const uint16_t rowPins[ROWS] = {
		KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN,KEYPAD_ROW4_PIN
};

static const uint16_t columnPins[ROWS] = {
		KEYPAD_COLUMN1_PIN,KEYPAD_COLUMN2_PIN,KEYPAD_COLUMN3_PIN,KEYPAD_COLUMN4_PIN
};


typedef struct {
	char key;
	operation_t mode;
} keypadInput_t;

#endif /* INC_KEYPAD_H_ */
