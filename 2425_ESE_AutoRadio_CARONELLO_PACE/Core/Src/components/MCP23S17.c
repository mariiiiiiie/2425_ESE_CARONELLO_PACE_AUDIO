/*
 * MCP23S17.c
 *
 *  Created on: Nov 29, 2024
 *      Author: romingo
 */

#include "components/MCP23S17.h"
#include "shell.h"

#define MCP23S17_ADDR 0x40//A0=A1=A2=GND
#define MCP23S17_SPI hspi3

void MCP23S17_init(void){

	/* 0x05 - IOCON
	 *
	 */
	//MCP23S17_WriteRegister(0x05, 0b00001000) == HAL_OK ? debug(START,"MCP23S17 - IOCON") : debug(D_ERROR,"MCP23S17 - IOCON");


	/* 0x12 - GPIOA | 0x13 - GPIOB
	 *
	 */
	MCP23S17_WriteRegister(0x12, 255) == HAL_OK ? debug(START,"MCP23S17 - GPIOA") : debug(D_ERROR,"MCP23S17 - GPIOA");
	MCP23S17_WriteRegister(0x13, 0) == HAL_OK ? debug(START,"MCP23S17 - GPIOB") : debug(D_ERROR,"MCP23S17 - GPIOB");

	/* 0x00 - IODIRA | 0x01 - IODIRB
	 * 0 : All Pins as Output
	 */
	MCP23S17_WriteRegister(0x00, 0) == HAL_OK ? debug(START,"MCP23S17 - IODIRA") : debug(D_ERROR,"MCP23S17 - IODIRA");
	MCP23S17_WriteRegister(0x01, 0) == HAL_OK ? debug(START,"MCP23S17 - IODIRB") : debug(D_ERROR,"MCP23S17 - IODIRB");


}

HAL_StatusTypeDef MCP23S17_WriteRegister(uint8_t reg, uint8_t data){
	uint8_t pData[3];

	pData[0] = MCP23S17_ADDR ;
	pData[1] = reg;
	pData[2] = data;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_StatusTypeDef ret = HAL_SPI_Transmit(&MCP23S17_SPI, pData, 3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	return ret;

}
uint8_t MCP23S17_ReadRegister(uint8_t reg){
	uint8_t pDataTx[2];
	uint8_t pDataRx[1];


	pDataTx[0] = MCP23S17_ADDR;
	pDataTx[1] = reg;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

	// Transmettre l'adresse du registre, puis recevoir les données
	HAL_SPI_Transmit(&MCP23S17_SPI, pDataTx, 2, HAL_MAX_DELAY);  // Transmet l'adresse et le registre
	HAL_SPI_Receive(&MCP23S17_SPI, pDataRx, 1, HAL_MAX_DELAY);   // Reçoit la donnée du registre
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

	return pDataRx[0];  // Retourne la donnée lue
}
