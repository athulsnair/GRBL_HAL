/*
 * uart.h
 *
 * Created: 23-10-2018 11:11:14 AM
 *  Author: New User
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL


#include <avr/io.h>
#include "uart_cfg.h"
#include "constants.h"

/**
 * Defines the uart configuration table elements that are used
 * by Uart_Init to configure the uart registers.
 */
typedef struct 
{
	uint32_t ClkFreq;			/**< System Clock Frequency */
	uint32_t BaudRate;			/**< Desired Baud Rate */
	uint8_t UCBRx;				/**< Value of UBRRn register bits */
	uint8_t Oversampling;		/**< High speed mode ENABLED or DISABLED */
}UartBaud_t;

void Uart_Init(UartConfig_t const * const Config);
void Uart_ParitySet(UartChannel_t const Channel, UartConfig_t const * const Config);
void Uart_ParityChange(UartChannel_t const Channel, UartParity_t Parity);
void Uart_IsrModeSet(UartChannel_t const Channel, UartConfig_t const * const Config);
void Uart_BaudRateSet(UartChannel_t const Channel, UartConfig_t const * const Config);
void Uart_BaudRateChange(UartChannel_t const Channel, uint32_t Baudrate);
uint8_t Uart_CharGet(UartChannel_t const Channel);
uint8_t Uart_IsDataPresent(UartChannel_t const Channel);
void Uart_CharPut(UartChannel_t const Channel, char const Ch);
uint8_t Uart_IsTransmitComplete(UartChannel_t const Channel);
void Uart_interruptTrigger(UartChannel_t Channel, Uart_interrupt Trigger);
void Uart_interruptClear(UartChannel_t Channel, Uart_interrupt Trigger);

#endif /* UART_H_ */
