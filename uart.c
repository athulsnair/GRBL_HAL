/*
 * uart.c
 *
 * Created: 23-10-2018 11:11:01 AM
 *  Author: New User
 */ 
#include "uart.h"
#include <avr/common.h>

#define BAUD_RATE 115200

/**
 *  Defines a pointer to the controller status register.
 */
static uint8_t volatile * const status = (uint8_t*)&SREG;

/**
 *  Defines a table of pointers to the uart control & status 0 registers on the microcontroller.
 */
static uint8_t volatile * const uartctlstat1[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UCSR0A
};

/**
 *  Defines a table of pointers to the uart control & status 1 registers on the microcontroller.
 */
static uint8_t volatile * const uartctlstat2[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UCSR0B
};

/**
 *  Defines a table of pointers to the uart control & status 2 registers on the microcontroller.
 */
static uint8_t volatile * const uartctlstat3[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UCSR0C
};


/**
 *  Defines a table of pointers to the uart receive buffer on the microcontroller.
 */
static uint8_t volatile * const uartrx[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UDR0
};

/**
 *  Defines a table of pointers to the uart transmit buffer on the microcontroller.
 */
static uint8_t volatile * const uarttx[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UDR0
};

/**
 * This table defines the uart register values for common system clock frequencies 
 * and UART baud rates.
 */
const UartBaud_t UartBaudTable[] =
{
//    Clock     Baud            
//   Freq(Hz)   Rate	  UBRRn	  Double speed	
//
	{1000000,	2400,		25,		DISABLED	},
	{1000000,	4800,		12,		DISABLED	},
	{1000000,	9600,		12,		ENABLED		},
	{1000000,	14400,		8,		ENABLED		},
	
	{16000000,	9600,		103,	DISABLED	},
	{16000000,	19200,		51,		DISABLED	},
	{16000000,	38400,		25,		DISABLED	},
	{16000000,	57600,		34,		ENABLED		},
	{16000000,	115200,		16,		ENABLED		},
};

/******************************************************************************
* Functions
*******************************************************************************/
/******************************************************************************
* Function : Uart_Init()
*//**
* \b Description:
*
* This function is used to initialize the Uart based on the configuration table
*  defined in uart_cfg module.
*
* PRE-CONDITION: Configuration table needs to populated (sizeof > 0) <br>
* PRE-CONDITION: The MCU clocks must be configured and enabled.
*
* POST-CONDITION: The uart peripheral is setup with the configuration settings.
*
* @param[in]  		Config is a pointer to the configuration table that contains
*				the initialization for the peripheral.
*
* @return 		void
*
* \b Example:
* @code
* 	const UartConfig_t *UartConfig = Uart_ConfigGet();
*
* 	Uart_Init(UartConfig);
* @endcode
*
* <br><b> - HISTORY OF CHANGES - </b>
*
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
* <tr><td> 09/01/2015 </td><td> 0.5.0            </td><td> JWB      </td><td> Interface Created </td></tr>
* <tr><td> 11/10/2015 </td><td> 1.0.0            </td><td> JWB      </td><td> Interface Released </td></tr>
* </table><br><br>
* <hr>
*******************************************************************************/

void Uart_Init(UartConfig_t const * const Config)
{
	uint8_t i = 0;
	for(i = 0; i < NUM_UART_CHANNELS; i++) {
		
		/************************************************************************/
		/*  ENABLE / DISABLE uart                                                                    */
		/************************************************************************/

		if(Config[i].UartEnable == ENABLED) {
			
			*uartctlstat2[i] |= (REGBIT3 | REGBIT4);
		}
		else {
			*uartctlstat2[i] &= ~(REGBIT3 | REGBIT4);
		}
		
		/************************************************************************/
		/* Data length 8 bit / 9 bit                                                                     */
		/************************************************************************/
		
		if(Config[i].DataLength == BITS_EIGHT) {
			
			*uartctlstat3[i] &= ~(REGBIT0 | REGBIT1); //UCSR0C |= ((1 << UCSZ00) | (1 << UCSZ01));
			*uartctlstat2[i] &= ~REGBIT2;
			
			*uartctlstat3[i] |= (REGBIT0 | REGBIT1);
		}
		else if(Config[i].DataLength == BITS_NINE) {
			
			*uartctlstat3[i] |= (REGBIT0 | REGBIT1);
			*uartctlstat2[i] |= REGBIT2;
		}
		
		if(Config[i].IntEnable == ENABLED) {
			*status |= REGBIT7;			//Same as sei() or SREG |= (1 << 7); ==> SREG is found in <avr/common.h>
		}
		
		/************************************************************************/
		/* Baud rate set                                                               */
		/************************************************************************/
		
		/*		for Default clock, 1MHz		*/
		//uint16_t UBRR0_value;
		/*
		if(Config[i].BaudRate >= 9600) {
			UBRR0_value = ((F_CPU / (4L * Config[i].BaudRate)) - 1)/2;
			*uartctlstat1[i] |= (REGBIT1);
		}
		else {
			UBRR0_value = ((F_CPU / (8L * Config[i].BaudRate)) - 1)/2 ;
			*uartctlstat1[i] &= ~(REGBIT1);
		}
		*/
		
		/*		for 16MHz clock, Arduino UNO		*/
		// Set baud rate
		/*
		uint16_t UBRR0_value;
		if(Config[i].BaudRate < 57600) {
		UBRR0_value = ((F_CPU / (8L * Config[i].BaudRate)) - 1)/2 ;
		UCSR0A &= ~(REGBIT1); // baud doubler off  - Only needed on Uno XXX
		}else {
		UBRR0_value = ((F_CPU / (4L * Config[i].BaudRate)) - 1)/2;
		UCSR0A |= (REGBIT1);   // baud doubler on for high baud rates, i.e. >= 57600bps
		}
		
		UBRR0H = UBRR0_value >> 8;
		UBRR0L = UBRR0_value;
		*/
		
		/* !!!New method TEST */
		
		uint8_t size = sizeof(UartBaudTable)/sizeof(UartBaud_t);
		uint16_t UBRR0_value;
		
		for(uint8_t j = 0; j < size; j++) {
			
			if((F_CPU == UartBaudTable[j].ClkFreq) && (Config[i].BaudRate == UartBaudTable[j].BaudRate)) {
				
				if(UartBaudTable[j].Oversampling == ENABLED) {
					//printf("HIGH SPEED\n");
					UBRR0_value = ((F_CPU / (4L * Config[i].BaudRate)) - 1)/2;
					UCSR0A |= (REGBIT1);   // baud doubler on for high baud rates, i.e. >= 57600bps
				}
				else {
					//printf("NORMAL SPEED\n");
					UBRR0_value = ((F_CPU / (8L * Config[i].BaudRate)) - 1)/2 ;
					UCSR0A &= ~(REGBIT1); // baud doubler off  - Only needed on Uno XXX
				}
				break;
			}
			
		}
		UBRR0H = UBRR0_value >> 8;
		UBRR0L = UBRR0_value;
		
	}
	
}


void Uart_ParitySet(UartChannel_t const Channel, UartConfig_t const * const Config)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	if(Config[Channel].ParityType == ODD) {
		
		*uartctlstat3[number] |= (REGBIT4 | REGBIT5);
	}
	else if(Config[Channel].ParityType == EVEN) {
		
		*uartctlstat3[number] &= ~(REGBIT4 | REGBIT5);
		*uartctlstat3[number] |= REGBIT5;
	}
	else {
		*uartctlstat3[number] &= ~(REGBIT4 | REGBIT5);
	}
}

/************************************************************************/
/* I defined it                                                                     */
/************************************************************************/

void Uart_ParityChange(UartChannel_t const Channel, UartParity_t Parity)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	if(Parity == ODD) {
		
		*uartctlstat3[number] |= (REGBIT4 | REGBIT5);
	}
	else if(Parity == EVEN) {
		
		*uartctlstat3[number] &= ~(REGBIT4 | REGBIT5);
		*uartctlstat3[number] |= REGBIT5;
	}
	else {
		*uartctlstat3[number] &= ~(REGBIT4 | REGBIT5);
	}
}

void Uart_IsrModeSet(UartChannel_t const Channel, UartConfig_t const * const Config)
{

}

void Uart_BaudRateSet(UartChannel_t const Channel, UartConfig_t const * const Config)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	uint16_t UBRR0_value;
	if(Config[Channel].BaudRate < 57600) {
		UBRR0_value = ((F_CPU / (8L * Config[Channel].BaudRate)) - 1)/2 ;
		*uartctlstat1[number] &= ~(REGBIT1); // baud doubler off  - Only needed on Uno XXX
		}else {
		UBRR0_value = ((F_CPU / (4L * Config[Channel].BaudRate)) - 1)/2;
		*uartctlstat1[number] |= (REGBIT1);   // baud doubler on for high baud rates, i.e. 115200
	}
	
	UBRR0H = UBRR0_value >> 8;
	UBRR0L = UBRR0_value;
	
}

/************************************************************************/
/* I created this                                                                     */
/************************************************************************/
void Uart_BaudRateChange(UartChannel_t const Channel, uint32_t Baudrate)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	UBRR0H = 0X00;
	UBRR0L = 0X00;
	*uartctlstat1[number] &= ~(REGBIT1);
	
	uint16_t UBRR0_value;
	if(Baudrate < 57600) {
		UBRR0_value = ((F_CPU / (8L * Baudrate)) - 1)/2 ;
		*uartctlstat1[number] &= ~(REGBIT1); // baud doubler off  - Only needed on Uno XXX
		}else {
		UBRR0_value = ((F_CPU / (4L * Baudrate)) - 1)/2;
		*uartctlstat1[number] |= (REGBIT1);   // baud doubler on for high baud rates, i.e. 115200
	}
	
	UBRR0H = UBRR0_value >> 8;
	UBRR0L = UBRR0_value;
}

uint8_t Uart_CharGet(UartChannel_t const Channel)
{
	uint8_t Temp;

	Temp = *uartrx[Channel];
	
	return Temp;
}

uint8_t Uart_IsDataPresent(UartChannel_t const Channel)
{
	// Mask for the uart receive interrupt flag
	// If interrupt flag is set, return false
	// Else, return false
	
	if((*uartctlstat1[Channel] & (REGBIT7)) == 0)		//1 << RX
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void Uart_CharPut(UartChannel_t const Channel, char const Ch)
{
	char *ptr = &Ch;
	if (0x0a==Ch)
	{
		//Ch = 0x0d;
		*ptr = 0x0d;
	}

	// Send one byte to the UxTXREG of the specified channel
	*uarttx[Channel] = Ch;
	while(!(*uartctlstat1[UART_0] & (REGBIT5)));		//1 << TX

	// Mask for UCBUSY bit in UCAxSTAT register
	// If UCBUSY == 1, transmit is not completed
	// Wait for transmition to finish
	//    while((*uartstat[Channel] & REGBIT0) == 1);
}

uint8_t Uart_IsTransmitComplete(UartChannel_t const Channel)
{
	// Mask for the uart receive interrupt flag
	// If interrupt flag is set, return flase
	// Else, return false
	
	if((*uartctlstat1[Channel] & (REGBIT5)) == 0)		//1 << TX
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Uart_interruptTrigger(UartChannel_t Channel, Uart_interrupt Trigger)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	if(Trigger == RECEIVE)
	{
		*uartctlstat2[number] |= (REGBIT7);
	}
	else if(Trigger == TRANSMIT)
	{
		*uartctlstat2[number] |= (REGBIT6);
	}
	else if(Trigger == DATA_EMPTY)
	{
		*uartctlstat2[number] |= (REGBIT5);
	}
}

void Uart_interruptClear(UartChannel_t Channel, Uart_interrupt Trigger)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	if(Trigger == RECEIVE)
	{
		*uartctlstat2[number] &= ~(REGBIT7);
	}
	else if(Trigger == TRANSMIT)
	{
		*uartctlstat2[number] &= ~(REGBIT6);
	}
	else if(Trigger == DATA_EMPTY)
	{
		*uartctlstat2[number] &= ~(REGBIT5);
	}
}
