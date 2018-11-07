/*
 * uart_cfg.c
 *
 * Created: 23-10-2018 11:11:57 AM
 *  Author: New User
 */ 
#include "uart_cfg.h"

/**
* This configuration table is used to configure the behavior and function of
* the timers.  The channels are defined in tmr_cfg.h.  The configuration
* consists of
*
*  o Uart Name - Specify the name of the uart. This label must be defined in
*      the Uart_RegisterType enumeration.
*  o Uart Enable - Specify whether the uart channel is enabled.
*  o Uart Mode - Specify the mode of the UCSI channel.
*	  UART - Standard UART mode
*	  IDLE_LINE - Idle-line multiprocessor mode
*	  ADDR_BIT - Address-bit multiprocessor mode
*	  UART_AUTO - UART mode with automatic baud rate detection
*  o Clock Source - Choose the UART clock source.
*  o Baud Rate - Specify the desired baud rate for the uart channel.
*  o Loopback - Enable or disable loopback mode
*  o Bit Direction - Specify the bit ordering for uart receive and transmit shift registers.
*     LEAST_FIRST - Least significant bit first
*     MOST_FIRST - Most significant bit first
*  o Data Length - Specify the character length, 7- or 8-bits.
*  o Data Length - Specify the number of stop bits, 1 or 2.
*  o Parity Type - Specify whether the uart parity is ODD, EVEN, or DISABLED.
*  o AutoBaud Enable - Enable or Disable automatic baud rate detection.
*  o Delimiter - Specify the break/synch delimiter length for auto baud detection.
*  o Interrupt Enable - This sets whether the receive interrupt for this uart is enabled.
*     DISABLED  - Disable the UART interrupts
*     RX_ONLY - Enable receive interrupt, transmit interrupt disabled
*     TX_ONLY - Enable transmit interrupt, receive interrupt disabled
*     RX_TX - Enable both receive and transmit interrupts
*
*  UART_0 and UART_1 channels are shared with the SPIA_0 and SPIA_1 channel.
*  Only one of them can be enabled on a channel at a time.
*******************************************************************************/
static const UartConfig_t UartConfig[] =
{
//	  Uart		UART		Baud		 Data	   Stop 	Parity		Interrupt
//    Name		Enable   	Rate	    Length     Bits		Type		Enable
	{UART_0,	ENABLED, 	115200,		BITS_EIGHT,	  1,	DISABLED,	ENABLED},
	
	//	  Uart		UART		Uart	Clock	   Baud				    	 Bit    	  Data	    Stop 	Parity     		   		Interrupt
	//    Name		Enable   	Mode	Source	   Rate	     Loopback     Direction	     Length     Bits	 Type		Delimiter	Enable

	//{UART_0,	ENABLED, 	UART,  	SUBMCLK,   115200, DISABLED,	 UART_LSB_FIRST,   BITS_EIGHT,	  1,	DISABLED,  		1,	    DISABLED  },
};

UartConfig_t const * const Uart_ConfigGet(void)
{
	return UartConfig;
}
