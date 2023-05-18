/* 
 * File:   app.c
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on May 13, 2023, 8:41 PM
 */

//to use Initialization and boolean types
#include <stdbool.h>
#include <stdint.h>

//Contains registers Bas Addresses
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

//Contains GPIO peripheral prototypes
#include "driverlib/gpio.h"

//Contains Macros for lock
#include "inc/hw_gpio.h"

//Contains Clock Source
#include "driverlib/sysctl.h"

#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/uart.h"


uint32_t flag = 0;


int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
 

	UARTCharPut(UART0_BASE, '!');
	do
	{
	flag = UARTCharGet(UART0_BASE);

		UARTCharPut(UART0_BASE, flag);
	}
	while((flag != '\n') && (flag != '\r'));

	UARTCharPut(UART0_BASE, '@');

}