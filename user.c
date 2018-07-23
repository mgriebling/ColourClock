/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"
#include "Clock.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */
	WPUA = 0x0A;
	TRISAbits.TRISA1 = 1;		// Set switch input
	WPUAbits.WPUA1 = 1;			// Enable internal pull-up
	TRISAbits.TRISA3 = 1;		// Mode switch input
	WPUAbits.WPUA3 = 1;			// Enable internal pull-up
//	IOCAPbits.IOCAP1 = 1;		// Enable interrupt on change
//	IOCANbits.IOCAN1 = 1;
//	IOCAPbits.IOCAP3 = 1;
//	IOCANbits.IOCAN3 = 1;
	OPTION_REGbits.nWPUEN = 0;	// Enable pull-ups
	
	TRISAbits.TRISA2 = 0;		// RGB SO output
	TRISAbits.TRISA4 = 1;		// RTC SCL -- start as input
	TRISAbits.TRISA5 = 1;		// RTC SDA --   "        "
	
	ANSELA = 0;					// All digital I/O

    /* Initialize peripherals */
	Clock_BEGIN();

    /* Enable interrupts */
}

