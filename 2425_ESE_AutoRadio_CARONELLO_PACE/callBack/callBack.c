/*
 * callBack.c
 *
 *  Created on: Nov 19, 2024
 *      Author: romingo
 */

#include "callBack.h"

SemaphoreHandle_t sem_uart_read = NULL;


//extern uint8_t fifo_status = 0;

/*
 * We must declared here a function CUSTOM_ because main.c already use this callback
 */

/*********** PREEMPTION PRIORITY  ***********/
void CUSTOM_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

}
/*********** PREEMPTION PRIORITY 5 ***********/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	/** SHELL INTERRUPTIONS **/
	if (huart->Instance == USART2) {
		BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(sem_uart_read, &pxHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
	}
}
