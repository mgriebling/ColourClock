/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        32000000L
#define _XTAL_FREQ		SYS_FREQ
#define FCY             SYS_FREQ/4

#define ON  (TRUE)
#define OFF (FALSE)
#define TRUE  (1)
#define FALSE (0)
#define TCHAR unsigned char
#define LONGINT long
#define LONGCARD unsigned long
#define CARDINAL LONGCARD
#define BOOLEAN unsigned char

#define Nop()	NOP()

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
