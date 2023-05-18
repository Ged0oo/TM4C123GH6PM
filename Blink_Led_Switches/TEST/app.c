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
#include "inc/hw_types.h"


bool flag = 0;

void INT_HANDLER()
{
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) != GPIO_PIN_4)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        flag = 1;
    }
}

int main(void)
{
    /*Initialization*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    uint8_t state = 0;

    /*SuperLoop*/
    while(1)
    {
        state1 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 |GPIO_PIN_4);
        switch(state)
        {
        case GPIO_PIN_0:

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);

            SysCtlDelay(1000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            SysCtlDelay(1000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
            break;

        case GPIO_PIN_4:

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);

            SysCtlDelay(1000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            SysCtlDelay(1000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
            break;

        default:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

            SysCtlDelay(1000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(1000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
            break;
        }
    }
}