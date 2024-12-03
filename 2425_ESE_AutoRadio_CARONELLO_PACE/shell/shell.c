/*
 * shellv2.c
 *
 *  Created on: Nov 14, 2024
 *      Author: romingo
 */

#include "shell.h"
#include "components/MCP23S17.h" 

extern SemaphoreHandle_t sem_uart_read;

MAPPER mapping[] = {
		{ "help", "Print every function available", "None",subfunct_help },
		{"led","Allume les leds","None",subfunct_leds},
		{ "clear","Clear screen", "None", subfunct_clear },
};
uint8_t started[] =
		"\r\n*-----------------------------*"
		"\r\n|     Welcome on AutoRadio    |"
		"\r\n*-----------------------------*"
		"\r\n";
uint8_t newline[] = "\r\n";
uint8_t backspace[] = "\b \b";
uint8_t cmdNotFound[] = "Command not found\r\n";
uint8_t prompt[] = "shell@AutoRadio>>";
uint8_t clear[] = "\x1b[2J\x1b[H";
uint8_t uartRxBuffer[UART_RX_BUFFER_SIZE];
uint8_t uartTxBuffer[UART_TX_BUFFER_SIZE];

uint16_t adc2_asserv_VAL[2]={0,0};

char cmdBuffer[CMD_BUFFER_SIZE];
int idx_cmd;
char *argv[MAX_ARGS];
int argc = 0;
char *token;
int newCmdReady = 0;
int isSeeIMU = 0;
int isSeeIMUFORCE = 0;
int isFind = 0;
int isStarted = 0;
int isADC_cplt =0;
uint8_t PWMLed = 255;


void shell_init(void) {
	memset(argv, 0, MAX_ARGS * sizeof(char*));
	memset(cmdBuffer, 0, CMD_BUFFER_SIZE * sizeof(char));
	memset(uartRxBuffer, 0, UART_RX_BUFFER_SIZE * sizeof(char));
	memset(uartTxBuffer, 0, UART_TX_BUFFER_SIZE * sizeof(char));
	sem_uart_read = xSemaphoreCreateBinary();
	sem_uart_read == NULL ? Error_Handler() : (void) 0;

	HAL_UART_Transmit(&UART_DEVICE, started, strlen((char*) started),
			HAL_MAX_DELAY);
	HAL_UART_Transmit(&UART_DEVICE, prompt, strlen((char*) prompt),
			HAL_MAX_DELAY);
}

void shell_run(void*) {
	int reading = 0;
	for (;;) {
		reading = 1;
		idx_cmd = 0;
		while (reading) {
			HAL_UART_Receive_IT(&UART_DEVICE, uartRxBuffer, UART_RX_BUFFER_SIZE);
			xSemaphoreTake(sem_uart_read, portMAX_DELAY)!=pdPASS ? Error_Handler():(void)0;

			switch (uartRxBuffer[0]) {
			case ASCII_CR: // Nouvelle ligne, instruction à traiter
				HAL_UART_Transmit(&UART_DEVICE, newline, sizeof(newline),
						HAL_MAX_DELAY);
				argc = 0;
				token = strtok(cmdBuffer, " ");
				while (token != NULL) {
					argv[argc++] = token;
					token = strtok(NULL, " ");
				}
				idx_cmd = 0;
				reading = 0;        //exit read loop
				newCmdReady = 1;
				break;
			case ASCII_BACK:
			case ASCII_BACK_BIS: // Suppression du dernier caractère
				if (idx_cmd == 0) {
					break;
				}
				cmdBuffer[idx_cmd--] = '\0';
				HAL_UART_Transmit(&UART_DEVICE, backspace, sizeof(backspace),
						HAL_MAX_DELAY);
				break;
			default:
				cmdBuffer[idx_cmd++] = uartRxBuffer[0];
				HAL_UART_Transmit(&UART_DEVICE, uartRxBuffer,
						UART_RX_BUFFER_SIZE, HAL_MAX_DELAY);
			}
		}
		if (newCmdReady) {
			for (int i = 0; i < sizeof(mapping) / sizeof(mapping[0]); i++) {
				if (strcmp(argv[0], mapping[i].name) == 0) {
					isFind = 1;
					mapping[i].funct(argv);
				}
			}
			if (!isFind) {
				HAL_UART_Transmit(&UART_DEVICE, cmdNotFound,
						sizeof(cmdNotFound), HAL_MAX_DELAY);
			}

			HAL_UART_Transmit(&UART_DEVICE, prompt, sizeof(prompt),
					HAL_MAX_DELAY);
			newCmdReady = 0;
			isFind = 0;
			memset(cmdBuffer, 0, MAX_ARGS * sizeof(char*));

		}
	}
}

/*
 * ***********************************************************************************************
 * 										SUBFUNCTIONS
 *************************************************************************************************/
void subfunct_help(char **argv) {
	printf("%s%-15s | %-30s | %-50s\r\n%s%s", GRAS, "Fonctions", "Params",
			"Description", D_RESET, separator);
	for (int i = 0; i < sizeof(mapping) / sizeof(mapping[0]); i++) {
		printf("%s%-15s%s | %-30s | %-50s\r\n", FUNCTION, mapping[i].name,
				D_RESET, mapping[i].params, mapping[i].resume);
	}
	printf(separator);
}
void subfunct_leds(char **argv){
	MCP23S17_init();
}
void subfunct_clear(char **argv) {
	HAL_UART_Transmit(&UART_DEVICE, clear, sizeof(clear), HAL_MAX_DELAY);
}

/************************************************************************************************
 * 										DEBUG
 *************************************************************************************************/

void debug(char *debugType, char *message) {

	printf("%-15s%s| %s\r\n", debugType, D_RESET, message);

}
