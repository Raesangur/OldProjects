// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define LCD_TEXT_MAX_LINES			20U
#define LCD_TEXT_MAX_COLUMNS		30U
/* I2C */
#define LCD_I2C_ADRESS				0x20U
#define LCD_I2C_COMMAND_CLEAR		0x00U
#define LCD_I2C_COMMAND_TEXT		0x01U
#define LCD_I2C_COMMAND_GRAPH		0x02U
/* UART */
#define LCD_UART_COMMAND_TEXT		0x01U
/* SPI */
#define LCD_SPI_COMMAND_TEXT		0x01U
/* Parallel */
#define LCD_PARALLEL_COMMAND_TEXT	0x01U

#ifdef HAL_I2C_MODULE_ENABLED			/* Check if HAL definition of I2C exists */
#define I2C_HANDLER I2C_HandleTypeDef
#else									/* Otherwise create a pointer that will be pointing NULL */
#define I2C_HANDLER uint32_t
#endif

#ifdef HAL_UART_MODULE_ENABLED			/* Check if HAL definition of UART exists */
#define UART_HANDLER UART_HandleTypeDef
#else									/* Otherwise create a pointer that will be pointing NULL */
#define UART_HANDLER uint32_t
#endif

#ifdef HAL_SPI_MODULE_ENABLED			/* Check if HAL definition of SPI exists */
#define SPI_HANDLER SPI_HandleTypeDef
#else									/* Otherwise create a pointer that will be pointing NULL */
#define SPI_HANDLER uint32_t
#endif
#ifdef HAL_TIM_MODULE_ENABLED			/* Check if HAL definition of Timers exists */
#define TIM_HANDLER TIM_HandleTypeDef
#else									/* Otherwise create a pointer that will be pointing NULL */
#define TIM_HANDLER uint32_t
#endif

typedef enum
{
	NO_ERROR = 0U,						/* Default state */
	E_NONE = 0U,						/* Default state */
	E_TIM_INIT,							/* Error during initialization of the timer */
	E_I2C_INIT,							/* Error during I2C initialization */
	E_UART_INIT,						/* Error during UART initialization */
	E_SPI_INIT,							/* Error during SPI initialization */
	E_PARALLELL_INIT,					/* Error during parallel initialization */
	E_TIM_START,						/* Error while starting the timer */
	E_TIM_STOP,							/* Error while stopping the timer */
	E_MODULE_BUSY,						/* Operations are being performed in another thread */
	E_I2C_HAL_BUSY,						/* I2C peripheral currently busy */
	E_UART_HAL_BUSY,					/* UART peripheral currently busy*/
	E_SPI_HAL_BUSY,						/* SPI peripheral currently busy */
	E_PARALLEL_PORT_BUSY,				/* Parallel port currently busy */
	E_I2C_HAL_TIMEOUT,					/* I2C peripheral timeout error */
	E_UART_HAL_TIMEOUT,					/* UART peripheral timeout error */
	E_SPI_HAL_TIMEOUT,					/* SPI peripheral timeout error */
	E_PARALLEL_PORT_TIMEOUT,			/* Parallel port timeout error */
	E_I2C_HAL_ERROR,					/* HAL I2C generic error */
	E_I2C_HAL_ERROR_AF,					/* HAL I2C error #AF	-- Acknowledge Failure */
	E_I2C_HAL_ERROR_BERR,				/* HAL I2C error #BERR	-- Bus Error */
	E_I2C_HAL_ERROR_ARLO,				/* HAL I2C error #ARLO	-- Arbitration lost */
	E_I2C_HAL_ERROR_OVR,				/* HAL I2C error #OVR	-- Overrun error */
	E_I2C_HAL_ERROR_DMA,				/* HAL I2C error #DMA	-- DMA error */
	E_UNKNOWN_MODE,						/* Attempting to access an unknown module mode */
	E_UNINITIALIZED,					/* Function called is not initialized */
	E_NOT_IMPLEMENTED,					/* Function called is not implemented in the API yet */
	E_WRITE_ARRAY,						/* Generic writing array couldn't be initialized */
	E_I2C_WRITE_S_BUSY,					/* Attempt to write in I2C while module state is busy */
	E_UART_WRITE_S_BUSY,				/* Attempt to write in UART while module state is busy */
	E_SPI_WRITE_S_BUSY,					/* Attempt to write in SPI while module state is busy */
	E_PARALLEL_WRITE_S_BUSY,			/* Attempt to write in Parallel while module state is busy */
	E_I2C_WRITE_S_INIT,					/* Attempt to write in I2C while module state is not yet initialized */
	E_UART_WRITE_S_INIT,				/* Attempt to write in UART while module state is not yet initialized */
	E_SPI_WRITE_S_INIT,					/* Attempt to write in SPI while module state is not yet initialized */
	E_PARALLEL_WRITE_S_INIT,			/* Attempt to write in Parallel while module state is not yet initialized */
	E_I2C_WRITE_S_FAILURE,				/* Attempt to write in I2C while module has state critically failed */
	E_UART_WRITE_S_FAILURE,				/* Attempt to write in UART while module has state critically failed */
	E_SPI_WRITE_S_FAILURE,				/* Attempt to write in SPI while module has state critically failed */
	E_PARALLEL_WRITE_S_FAILURE,			/* Attempt to write in Parallel while module state has critically failed */
	E_WRITE_TEXT_SIZE,					/* Incorrect size of character array */
	E_WRITE_TEXT_LINE,					/* Incorrect line number */
	E_WRITE_TEXT_COLUMN,				/* Incorrect column number */

}LCD_ERROR_T;

typedef enum
{
	NOT_INIT,							/* Default mode */
	I2C_MODE,							/* I2C Mode; code can't access other modes */
	UART_MODE,							/* UART Mode; code can't access other modes */
	SPI_MODE,							/* SPI Mode; code can't access other modes */
	PARALLEL_MODE						/* Parallel Mode; code can't access other modes */
}LCD_MODE_T;

typedef enum
{
	READY,								/* LCD module is ready to perform operations */
	INIT,								/* LCD module is not initialized yet, or is currently being initialized */
	BUSY,								/* LCD module is currently performing operations */
	FAILURE								/* A critical error has disabled the LCD module */
}LCD_STATE_T;

typedef struct
{
	LCD_MODE_T Mode;
	LCD_STATE_T State;
	I2C_HANDLER* hi2c;
	UART_HANDLER* huart;
	SPI_HANDLER* hspi;
	TIM_HANDLER* htim;
}LCD_STRUCT_T;

LCD_STRUCT_T LCD_Struct =
{
	NOT_INIT,		/* LCD_MODE_T Mode */
	INIT,			/* LCD_STATE_T State */
	NULL,			/* I2C_HandleTypeDef hi2c */
	NULL,			/* UART_HandleTypeDef huart */
	NULL,			/* SPI_HandleTypeDef hspi */
	NULL,			/* TIM_HandleTypeDef htim */
};


void HAL_I2C_Master_Transmit(uint8_t Adress, uint8_t* pData, uint8_t size, uint8_t timeout);
LCD_ERROR_T LCD_Write_I2C(const uint8_t Command, const uint8_t* data, const size_t dataSize);
LCD_ERROR_T LCD_WriteLine(char* const pText, size_t textSize, uint8_t line, uint8_t column);

int main()
{
	char data[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	LCD_Struct.State = READY;
	LCD_Struct.Mode = I2C_MODE;
	std::cout << LCD_WriteLine(data, sizeof(data), 10, 3);
}

LCD_ERROR_T LCD_Write_I2C(const uint8_t Command, const uint8_t* pData, const size_t dataSize)
{
	LCD_ERROR_T I2C_Error = NO_ERROR;
	if (LCD_Struct.State == READY)
	{
		LCD_Struct.State = BUSY;

		/* Initialize data structure */
		/* (Variable lenghts array are illegal in C89, make sure the compiler used is based on C99) */
		size_t write_i = 0x00U;
		uint8_t* Data = new uint8_t[(dataSize + 0x02U)];
		uint8_t Checksum = Command;		/* The checksum starts with the value of the command */
		/* Dynamic stack memory allocation, we must check if it's valid */
		if ((&Data[0] == NULL) || (&Data[0] == 0))
		{
			I2C_Error = E_WRITE_ARRAY;
			assert(&Data[0] != NULL);	/* Display error message if pointer is invalid */
			assert(&Data[0] != 0);		/* Display error message if pointer is invalid */
		}
		else							/* Array is available and valid */
		{
			Data[0] = Command;			/* Command is the first byte sent */

			/* Check pointer value */
			/* It is possible for pData to be a NULL pointer, but only if dataSize is equal to 0 */
			if (pData == NULL)
			{
				if (dataSize != 0)
				{
					/* Invalid pointer! */
					I2C_Error = E_WRITE_ARRAY;
					assert(pData != NULL); /* Display error message if pointer is invalid */
				}
				else
				{
					/* Everything is fine here, pData is null, but that's because we only wanted to send a command */
				}
			}
			else
			{
				/* Populating the array with pData */
				for (write_i = 0x01U; write_i <= (dataSize + 1); write_i++)
				{
					Data[write_i] = pData[(write_i - 1)];
					Checksum += Data[write_i];
				}
			}
			/* Calculating checksum's 2's complement value */
			Checksum = (~Checksum) + 0x01U;
			Data[13] = Checksum;
			/* Calculating a timeout value */
			uint16_t timeoutValue = 0x03 * +(dataSize / 0x04U);

			/* Sending data via I2C */
			HAL_I2C_Master_Transmit(LCD_I2C_ADRESS, &Data[0], (dataSize + 0x02U), timeoutValue);
			LCD_Struct.State = READY;	/* Operations with the module have been completed, reset state */
		}
	}

	return (I2C_Error);
}

LCD_ERROR_T LCD_WriteLine(char* const pText, size_t textSize, uint8_t line, uint8_t column)
{
	LCD_ERROR_T WriteLine_Error = NO_ERROR;

	/* Check if character pointer is valid */
	if ((pText == NULL) || (pText == 0))
	{
		WriteLine_Error = E_WRITE_ARRAY;
		assert(pText != NULL);			/* Display error message if pointer is invalid */
		assert(pText != 0);				/* Display error message if pointer is invalid */
	}
	else
	{
		/* Check if line is valid */
		if (line > LCD_TEXT_MAX_LINES)
		{
			WriteLine_Error = E_WRITE_TEXT_LINE;
		}
		else
		{
			if (column > LCD_TEXT_MAX_COLUMNS)
			{
				WriteLine_Error = E_WRITE_TEXT_COLUMN;
			}
			else
			{
				if (textSize > (LCD_TEXT_MAX_COLUMNS - column))
				{
					WriteLine_Error = E_WRITE_TEXT_SIZE;
				}
				else
				{
					/* New Data Buffer, with 2 extra lines, for line & column */
					uint8_t* Data = new uint8_t[(textSize + 0x02U)];
					size_t write_i = 0x00U;
					/* Dynamic stack memory allocation, we must check if it's valid */
					if ((&Data[0] == NULL) || (&Data[0] == 0))
					{
						WriteLine_Error = E_WRITE_ARRAY;
						assert(&Data[0] != NULL);	/* Display error message if pointer is invalid */
						assert(&Data[0] != 0);		/* Display error message if pointer is invalid */
					}
					else							/* Array is available and valid */
					{
						/* Clear array */
						memset(&Data[0], 0x00, sizeof(Data));
						Data[0] = line;				/* Add line data to the array */
						Data[1] = column;			/* Add column data to the array */
						/* Populating the array with pText*/
						for (write_i = 0x02U; write_i <= (textSize + 1); write_i++)
						{
							Data[write_i] = pText[(write_i - 2)];
						}

						/* Write data */
						uint8_t command = 0x00;
						switch (LCD_Struct.Mode)
						{
						case I2C_MODE:
							command = LCD_I2C_COMMAND_TEXT;
							break;
						case UART_MODE:
							command = LCD_UART_COMMAND_TEXT;
							break;
						case SPI_MODE:
							command = LCD_SPI_COMMAND_TEXT;
							break;
						case PARALLEL_MODE:
							command = LCD_PARALLEL_COMMAND_TEXT;
							break;
						default:
							WriteLine_Error = E_UNKNOWN_MODE;
							break;
						}
						uint8_t Checker[12];
						memcpy(Checker, Data, (textSize + 2));
						LCD_Write_I2C(command, Data, (textSize + 1));
						
					}
				}
			}
		}
	}

	return (WriteLine_Error);
}

void HAL_I2C_Master_Transmit(uint8_t Adress, uint8_t* pData, uint8_t size, uint8_t timeout)
{
	uint8_t Checker[14];
	memcpy(Checker, pData, 14);
	std::cout << Adress;
	for (int i = 0; i <= size; i++)
	{
		std::cout << pData[i];
	}
}