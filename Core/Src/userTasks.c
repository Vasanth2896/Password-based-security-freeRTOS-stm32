/*
 * userTasks.c
 *
 *  Created on: Jul 17, 2025
 *      Author: vasanth
 */

#include "main.h"
#include "servo.h"
#include "keypad.h"
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "config.h"
#include "global.h"
#include "helper.h"
#include "flash.h"

void inputTask(void *pvParameters) {
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	uint32_t lastDebounceTime = 0;
	const uint32_t debounceDelay = 50;

	for (;;) {
		for (uint8_t row = 0; row < ROWS; row++) {

			for (uint8_t r = 0; r < ROWS; r++) {
				HAL_GPIO_WritePin(KEYPAD_PORT, rowPins[r],
						(r == row) ? GPIO_PIN_RESET : GPIO_PIN_SET);
			}


			for (uint8_t column = 0; column < COLUMNS; column++) {
				if (!HAL_GPIO_ReadPin(KEYPAD_PORT, columnPins[column])) {
					uint32_t currentTime = HAL_GetTick();

					// Wait for release
					while (!HAL_GPIO_ReadPin(KEYPAD_PORT, columnPins[column])) {
						vTaskDelay(pdMS_TO_TICKS(10));
					}

					if ((currentTime - lastDebounceTime) > debounceDelay) {
						char key = keypadMap[row][column];
						keypadInput_t input = { key, mode };

						if (key == '#') {
							toggleMode();
							input.mode = mode;
							memset(passBuffer, 0, sizeof(passBuffer));
							memset(flashPassBuffer, 0, sizeof(flashPassBuffer));
							xQueueReset(sendValidatorQueue);
							xQueueReset(sendUpdationQueue);
							xQueueSendToBack(sendDisplayQueue, &input,
									xTicksToWait);
						} else {
							xQueueSendToBack(sendDisplayQueue, &input,
									xTicksToWait);

							// Send to respective queue based on mode
							switch (mode) {
							case NORMAL:
								xQueueSendToBack(sendValidatorQueue, &key,
										xTicksToWait);
								xQueueReset(sendUpdationQueue);
								break;

							case UPDATE:
								xQueueSendToBack(sendUpdationQueue, &key,
										xTicksToWait);
								xQueueReset(sendValidatorQueue);
								break;

							default:
								break;
							}
						}
						lastDebounceTime = currentTime;
					}
				}
			}
		}
	}
}

void displayTask(void *pvParameters) {
	QueueSetMemberHandle_t xHandle;
	keypadInput_t receivedDisplayHolder;
	passwordValid_t receivedPassValidityHolder;
	passwordUpdation_t receivedUpdationHolder;
	BaseType_t displayQueueStatus, validQueueStatus, updateQueueStatus;
	const TickType_t xDelay = pdMS_TO_TICKS(100);

	for (;;) {
		xHandle = xQueueSelectFromSet(xQueueSet, xDelay);

		if (xHandle != NULL) {

			if (xHandle == (QueueSetMemberHandle_t) validatorQueue) {
				validQueueStatus = xQueueReceive(validatorQueue,
						&receivedPassValidityHolder, 0);

				if (validQueueStatus == pdPASS) {
					clearDisplay();
					switch (receivedPassValidityHolder) {
					case VALID:
						handleDisplay(0, "Access Granted");
						EVENT_LOG(INFO, "Access Granted");
						unlock();
						break;
					case INVALID:
						handleDisplay(0, "Access Denied");
						EVENT_LOG(ERROR, "Access Denied");
						break;
					default:
						break;
					}
					vTaskDelay(pdMS_TO_TICKS(2000));
					lock();
					handleDisplay(0, "Enter Password:");
				}
			}

			if (xHandle == (QueueSetMemberHandle_t) sendDisplayQueue) {
				displayQueueStatus = xQueueReceive(sendDisplayQueue,
						&receivedDisplayHolder, 0);
				if (displayQueueStatus == pdPASS) {
					if (receivedDisplayHolder.key == '#') {
						clearDisplay();
					}
					switch (receivedDisplayHolder.mode) {
					case UPDATE:
						handleDisplay(0, "Change Password:");
						handleDisplay(1, NULL);
						break;
					case NORMAL:
						handleDisplay(0, "Enter Password:");
						handleDisplay(1, NULL);
						break;
					default:
						break;
					}

					if (receivedDisplayHolder.key != '#') {
						passwordInput(&passPointer, receivedDisplayHolder.key);
					}

				}
			}

			if (xHandle == (QueueSetMemberHandle_t) updatorQueue) {
				updateQueueStatus = xQueueReceive(updatorQueue,
						&receivedUpdationHolder, 0);

				if (updateQueueStatus == pdPASS) {

					clearDisplay();
					switch (receivedUpdationHolder) {
					case UPDATION_SUCCESS:
						handleDisplay(0, "Password");
						handleDisplay(1, "updated");
						EVENT_LOG(INFO, "Password Updated successfully");
						break;
					case UPDATION_FAILED:
						handleDisplay(0, "Password");
						handleDisplay(1, "update failed");
						EVENT_LOG(ERROR, "Password Update Failed");
						break;
					default:
						break;
					}
					vTaskDelay(pdMS_TO_TICKS(3000));
					clearDisplay();
					handleDisplay(0, "Enter Password:");

					toggleMode();
				}
			}

		}

	}
}

void validationTask(void *pvParameters) {
	uint8_t receivedPassCharHolder = 0;
	uint8_t passComp = 0;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	BaseType_t passwordStatus;
	passwordValid_t validationStatus;

	for (;;) {
		passwordStatus = xQueueReceive(sendValidatorQueue,
				&receivedPassCharHolder,
				portMAX_DELAY);

		if (passwordStatus == pdPASS) {
			if (passPointer < PASS_LENGTH) {
				passBuffer[passPointer++] = receivedPassCharHolder;
			}

			if (passPointer == PASS_LENGTH) {
				passBuffer[passPointer] = '\0';
				flashReadPassword(flashPassBuffer, PASS_LENGTH + 1);
				passComp = strcmp(passBuffer, flashPassBuffer);
				validationStatus = VALID;
				if (passComp != 0) {
					validationStatus = INVALID;
				}

				vTaskDelay(pdMS_TO_TICKS(1000));
				xQueueSend(validatorQueue, &validationStatus, xTicksToWait);
				RESET_PASS_BUFFER(passBuffer);
			}
		}

	}

}

void updationTask(void *pvParameters) {
	uint8_t receivedPassCharHolder = 0;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
	int8_t flashEraseError = 0;
	HAL_StatusTypeDef flashWriteStatus = HAL_OK;
	BaseType_t updationStatus;
	passwordUpdation_t passwordUpdationState;

	for (;;) {
		updationStatus = xQueueReceive(sendUpdationQueue,
				&receivedPassCharHolder,
				portMAX_DELAY);

		if (updationStatus == pdPASS) {
			if (passPointer < PASS_LENGTH) {
				flashPassBuffer[passPointer++] = receivedPassCharHolder;
			}

			if (passPointer == PASS_LENGTH) {
				flashEraseError = flashErasePasswordSector();
				flashWriteStatus = flashWritePassword(flashPassBuffer);
				if (flashWriteStatus == HAL_OK && flashEraseError == 0) {
					passwordUpdationState = UPDATION_SUCCESS;
				} else {
					passwordUpdationState = UPDATION_FAILED;
				}

				vTaskDelay(pdMS_TO_TICKS(1000));
				xQueueSendToBack(updatorQueue, &passwordUpdationState,
						xTicksToWait);
				RESET_PASSPOINTER();
			}

		}

	}
}
