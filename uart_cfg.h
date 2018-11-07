/*
 * uart_cfg.h
 *
 * Created: 23-10-2018 11:11:44 AM
 *  Author: New User
 */ 


#ifndef UART_CFG_H_
#define UART_CFG_H_

#include <stdint.h>

/**
 * This enumeration is a list of the uart channels
 */
typedef enum 
{
	UART_0,			/**< UART0 */
	//UART_1,			/**< UART1 */
	//UART_2,			/**< UART2 */
    
    NUM_UART_CHANNELS		/**< Number of UART channels */
}UartChannel_t;

/**
 * Constants: Logic Values
 */
typedef enum
{
    DISABLED = 0U,	/**< Reserved word for representing the logical value 0 (OFF, 0 volts) */
    ENABLED = 1U,	/**< Reserved word for representing the logical value 1 (ON, 5 volts) */
    FALSE = 0U,		/**< Reserved word for representing the logical value 0 (OFF, 0 volts) */
    TRUE = 1U		/**<  Reserved word for representing the logical value 1 (ON, 5 volts) */
}LogicEnum_t;

/**
 * Defines the size of data sent to and from peripheral
 */
typedef enum 
{
	BITS_EIGHT,			/**< 8 bits sent at a time */
	BITS_NINE			/**< 9 bits sent at a time */
}UartComm_t;

/**
 * Defines the uart parity selections.  
 */
typedef enum 
{
	ODD = 0x01,		/**< Odd Parity  */
	EVEN = 0x02		/**< Even Parity */
}UartParity_t;

/************************************************************************/
/* I defined this
UART interrupt trigger                                                                     */
/************************************************************************/

typedef enum {
	TRANSMIT,
	RECEIVE,
	DATA_EMPTY
}Uart_interrupt;

/**
 * Defines the uart configuration table elements that are used
 * by Uart_Init to configure the uart registers.
 */
typedef struct 
{
	uint8_t UartChannel;		/**< Name of UART */
	uint8_t UartEnable;			/**< Uart Enable - ENABLED or DISABLED */	
	uint32_t BaudRate;			/**< Uart channel baud rate */
	uint8_t DataLength;			/**< Character length, 8 or 9 bits */
	uint8_t StopBits;			/**< Specify the number of stop bits, one or two */
	uint8_t ParityType;			/**< Parity Selection.  EVEN, ODD, or DISABLED */
	uint8_t IntEnable;			/**< Uart Receive Interrupt Enable - ENABLED or DISABLED */
}UartConfig_t;

UartConfig_t const * const Uart_ConfigGet(void);

#endif /* UART_CFG_H_ */
