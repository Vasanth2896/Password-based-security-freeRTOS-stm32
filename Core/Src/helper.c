/*
 * helper.c
 *
 *  Created on: Jul 17, 2025
 *      Author: vasanth
 */
#include "liquidcrystal_i2c.h"
#include "state.h"
#include "global.h"

void handleDisplay(int cursorPosition, const char *message) {

	if (cursorPosition > 1) {
		return;
	}
	HD44780_SetCursor(0, cursorPosition);

	if (message != NULL) {
		HD44780_PrintStr(message);
	}

}

void clearDisplay() {
	HD44780_Clear();
}

void passwordInput(uint8_t *cursorPosition, char key) {
	if(*cursorPosition >= PASS_LENGTH)return;
	char temp[2] = {key,'\0'};
	HD44780_SetCursor(*cursorPosition, 1);
	HD44780_PrintStr(temp);
}

void toggleMode() {
	mode = (mode == NORMAL) ? UPDATE : NORMAL;
}

