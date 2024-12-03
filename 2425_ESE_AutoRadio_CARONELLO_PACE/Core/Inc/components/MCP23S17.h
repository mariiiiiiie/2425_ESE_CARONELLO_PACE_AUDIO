/*
 * MCP23S17.h
 *
 *  Created on: Nov 29, 2024
 *      Author: romingo
 */

#ifndef INC_COMPONENTS_MCP23S17_H_
#define INC_COMPONENTS_MCP23S17_H_
#include "shell.h"
#include "spi.h"

void MCP23S17_init(void);
HAL_StatusTypeDef MCP23S17_WriteRegister(uint8_t reg, uint8_t data);
uint8_t MCP23S17_ReadRegister(uint8_t reg);

// BANK =1
#define IODIRA_Addr 0x00
#define IODIRB_Addr 0x10
#define GPINTENA_Addr 0x01

#endif /* INC_COMPONENTS_MCP23S17_H_ */
