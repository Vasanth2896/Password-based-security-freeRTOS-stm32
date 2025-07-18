/*
 * flash.c
 *
 *  Created on: Jul 17, 2025
 *      Author: vasanth
 */
#include "main.h"
#include "config.h"
#include<stdio.h>


uint32_t flashErasePasswordSector(void) {
//	taskENTER_CRITICAL();
	HAL_FLASH_Unlock();
	FLASH_Erase_Sector(FLASH_SECTOR_11, FLASH_VOLTAGE_RANGE_3);

	uint32_t sectorError = HAL_FLASH_GetError();
	printf("%lu sector error code \n", sectorError);
	fflush(stdout);

	if (sectorError == 0) {
		printf("successfully flash erased \n");
	} else {
		printf("error in flash erasure \n");
	}

	HAL_FLASH_Lock();
//	taskEXIT_CRITICAL();
	return sectorError;
}

HAL_StatusTypeDef flashWritePassword(const char *password) {
	HAL_StatusTypeDef status = HAL_OK;

//	taskENTER_CRITICAL();
	HAL_FLASH_Unlock();
	for (int i = 0; i <= PASS_LENGTH; i++) {
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,
		FLASH_STORAGE_ADDR + i, password[i]);
	}

	if (status != HAL_OK) {
		status = HAL_ERROR;
	}
//	taskEXIT_CRITICAL();

	uint8_t i = 0;
	while (password[i] != '\0') {
		// Read one byte from Flash at the address and compare with the corresponding character in password
		if (*(volatile uint8_t*) (FLASH_STORAGE_ADDR + i) != password[i]) {
			return HAL_ERROR;  // Mismatch found
		}
		i++;
	}

	HAL_FLASH_Lock();
	return status;  // Validation passed
}

void flashReadPassword(char *outBuffer, uint32_t maxLen) {
	const char *flashPtr = (const char*) FLASH_STORAGE_ADDR;

	for (uint32_t i = 0; i < maxLen; i++) {
		outBuffer[i] = flashPtr[i];
		if (flashPtr[i] == '\0')
			break;
	}
}

