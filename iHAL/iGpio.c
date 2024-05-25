/******************************************************************************************************************************/
/* HISTORY ********************************************************************************************************************/
/******************************************************************************************************************************/
/* Berat Erdemkilic [19.05.2024] - "GPIO driver interface, initialization" */

/******************************************************************************************************************************/
/* INCLUDES *******************************************************************************************************************/
/******************************************************************************************************************************/
#include "iGpio.h"

/******************************************************************************************************************************/
/* VARIABLES ******************************************************************************************************************/
/******************************************************************************************************************************/

/******************************************************************************************************************************/
/* DEFINITIONS ****************************************************************************************************************/
/******************************************************************************************************************************/

/******************************************************************************************************************************/
/* STRUCTS ********************************************************************************************************************/
/******************************************************************************************************************************/
typedef enum
{
	I_GPIO_BANK_A = 0,
	I_GPIO_BANK_B,
	I_GPIO_BANK_C,
	I_GPIO_BANK_D,
	I_GPIO_BANK_E,
	I_GPIO_BANK_F,
	I_GPIO_BANK_G,
	I_GPIO_BANK_H,
	I_GPIO_BANK_I
}IGPIO_BANKS_ENUM;

/******************************************************************************************************************************/
/* FUNCTIONS ******************************************************************************************************************/
/******************************************************************************************************************************/
/*	
Initialize the clocks of application specific GPIO ports
Inputs:	
GpioBank - GPIO Bank Type

Return:
IHAL_RETURN_ERROR if the clock is misused
IHAL_RETURN_OK if the clock is initialized
*/
static IHAL_RETURN_TYPES_ENUM iGpio_clockInit (IGPIO_BANKS_ENUM GpioBank)
{
	switch (GpioBank)
	{
		case I_GPIO_BANK_A:
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
			break;
		}
		case I_GPIO_BANK_B:
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
			break;
		}
		case I_GPIO_BANK_C:
		{
			__HAL_RCC_GPIOC_CLK_ENABLE();
			break;
		}
		case I_GPIO_BANK_D:
		{
			__HAL_RCC_GPIOD_CLK_ENABLE();
			break;
		}
		case I_GPIO_BANK_E:
		{
			__HAL_RCC_GPIOE_CLK_ENABLE();
			break;
		}
		case I_GPIO_BANK_F:
		{
			__HAL_RCC_GPIOF_CLK_ENABLE();
			break;
		}
		case I_GPIO_BANK_G:
		{
			__HAL_RCC_GPIOG_CLK_ENABLE();
			break;
		}
		case I_GPIO_BANK_H:
		{
			__HAL_RCC_GPIOH_CLK_ENABLE();
			break;
		}
		case I_GPIO_BANK_I:
		{
			__HAL_RCC_GPIOI_CLK_ENABLE();
			break;
		}
		default:
		{
			return IHAL_RETURN_ERROR;
			break;
		}
	}
	
	return IHAL_RETURN_OK;
}

/*	Initialize application specific GPIO ports

Inputs:	
GpioBank 				- GPIO Bank Type
GpioInitStruct	- GPIO configuration structure for initialization

Return:	
IHAL_RETURN_OK in either case since the main BSP method is defined as void */
IHAL_RETURN_TYPES_ENUM iGPIO_UserGpioInit (void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* Configure GPIO pin : PD12 */
  GPIO_InitStruct.Pin		= GPIO_PIN_12;
  GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull	= GPIO_NOPULL;
  GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	
	/* Initialize the clock for GPIO Bank D */
	iGpio_clockInit(I_GPIO_BANK_D);
	
	/* Configure the GPIO Bank D with the specified configuration */
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	/* Set the initial output level of GPIOs*/
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	
	return IHAL_RETURN_OK;
}

/*	Read the status of the BL button and pass the status into readResult

Inputs:	
readResult			- Status of the BL button (High when the button is pressed, Active low in default)

Return:	
IHAL_RETURN_OK
 */
IHAL_RETURN_TYPES_ENUM iGPIO_ReadBootloaderButton (GPIO_PinState* readResult)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin		= GPIO_PIN_0;
  GPIO_InitStruct.Mode	= GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull	= GPIO_NOPULL;
  GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	
	/* Initialize the clock for GPIO Bank D */
	iGpio_clockInit(I_GPIO_BANK_A);
	
	/* Configure the GPIO Bank D with the specified configuration */
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* Set the initial output level of GPIOs*/
	*readResult = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	
	return IHAL_RETURN_OK;
}