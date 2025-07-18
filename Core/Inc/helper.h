/*
 * helper.h
 *
 *  Created on: Jul 17, 2025
 *      Author: vasanth
 */

#ifndef INC_HELPER_H_
#define INC_HELPER_H_

void handleDisplay(int cursorPosition, const char *message);
void clearDisplay();
void passwordInput(uint8_t *cursorPosition, char key);
void toggleMode();



#endif /* INC_HELPER_H_ */
