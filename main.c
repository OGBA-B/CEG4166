#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <avr/io.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "thermalSensor.h"
#include "i2cMultiMaster.h"
#include "SerialLCDModule.h"
#include "WheelMotion.h"
#include "CyclicScheduler.h"

/* serial interface include file. */
#include "usartserial.h"


/*-----------------------------------------------------------*/
/* Create a handle for the serial port. */
//extern xComPortHandle xSerialPort;

/*-----------------------------------------------------------*/

/* Main program loop */
//int main(void) __attribute__((OS_main));
int usartfd;

int main(void)
{

    // turn on the serial port for debugging or for other USART reasons.
usartfd = usartOpen( USART1_ID, 9600, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)

usart_print_P(PSTR("\r\n\n\nSwell!\r\n"));


   xTaskCreate(
		   Scheduler
                ,  (const portCHAR *)"CyclicScheduler"
    	   		,  256
			   	,  NULL
			   	,  3
			   	,  NULL );

	vTaskStartScheduler();

	usart_print_P(PSTR("\r\n\n\nGoodbye... no space for idle task!\r\n")); // Doh, so we're dead...

}

/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/


void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    portCHAR *pcTaskName )
{

	DDRB  |= _BV(DDB7);
	PORTB |= _BV(PORTB7);       // main (red PB7) LED on. Mega main LED on and die.
	while(1);
}

/*-----------------------------------------------------------*/

