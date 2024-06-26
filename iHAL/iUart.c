/******************************************************************************************************************************/
/* HISTORY ********************************************************************************************************************/
/******************************************************************************************************************************/
/* Berat Erdemkilic [19.05.2024] - "GPIO driver interface, initialization" */

/******************************************************************************************************************************/
/* INCLUDES *******************************************************************************************************************/
/******************************************************************************************************************************/
#include "iUart.h"
#include <string.h>

/******************************************************************************************************************************/
/* DEFINITIONS ****************************************************************************************************************/
/******************************************************************************************************************************/
#define UART_MSG_TIMEOUT			 										(uint32_t)0xFFFF
#define UART_MAX_MESSAGE_SIZE 										(uint8_t)250
#define UART_CMD1_MESSAGE			 										"Command_1\r\n"
#define UART_CMD2_MESSAGE 												"Command_2\r\n"

/******************************************************************************************************************************/
/* VARIABLES ******************************************************************************************************************/
/******************************************************************************************************************************/
static uint8_t uartMsg[UART_MAX_MESSAGE_SIZE];

/******************************************************************************************************************************/
/* STRUCTS ********************************************************************************************************************/
/******************************************************************************************************************************/

/******************************************************************************************************************************/
/* FUNCTIONS ******************************************************************************************************************/
/******************************************************************************************************************************/
/*	
Transmits the static data in blocking mode

Inputs:	
huart - UART Handler

Return:
IHAL_RETURN_ERROR if the message cannot get send successfully
IHAL_RETURN_OK if the message is sent successfully
*/
IHAL_RETURN_TYPES_ENUM iUART_SendMessage(UART_HandleTypeDef *huart, IHAL_UART_COMMANDS_ENUM command)
{
	uint16_t msgSize = 0;
	
	/* Flush the message array */
	memset(&uartMsg[0], 0, UART_MAX_MESSAGE_SIZE);
	
	/* According to the requested command, set the message content */
	switch (command)
	{
		case IHAL_UART_TEST_MSG1:
		{
			msgSize = strlen(UART_CMD1_MESSAGE);
			memcpy(&uartMsg[0], UART_CMD1_MESSAGE, msgSize);
			break;
		}
		case IHAL_UART_TEST_MSG2:
		{
			msgSize = strlen(UART_CMD2_MESSAGE);
			memcpy(&uartMsg[0], UART_CMD2_MESSAGE, msgSize);
			break;
		}
		default:
		{
			break;
		}
	}
	
	if(HAL_OK != HAL_UART_Transmit(huart, &uartMsg[0], msgSize, UART_MSG_TIMEOUT))
	{
		return IHAL_RETURN_ERROR;
	}		
	
	return IHAL_RETURN_OK;
}





