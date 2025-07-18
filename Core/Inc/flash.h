/*
 * flash.h
 *
 *  Created on: Jul 17, 2025
 *      Author: vasanth
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

HAL_StatusTypeDef flashWritePassword(const char *password);
void flashReadPassword(char *outBuffer, uint32_t maxLen);
uint32_t flashErasePasswordSector(void);

#endif /* INC_FLASH_H_ */
