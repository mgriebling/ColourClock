/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "Clock.h"

#define SO		LATAbits.LATA2

#define BITOUT(b)\
	asm("bsf	12,2");\
	if (b & 0x80) {\
        Nop();\
        Nop();\
        Nop();\
        Nop();\
        Nop();\
        Nop();\
        b <<= 1;\
		asm("bcf	12,2");\
	} else {\
		asm("bcf	12,2");\
        Nop();\
        Nop();\
        Nop();\
        Nop();\
        Nop();\
        Nop();\
        Nop();\
        Nop();\
        b <<= 1;\
	}


/* output RGB values to one LED */
inline void WriteRGB (unsigned char r, unsigned char g, unsigned char b) {
	asm("BANKSEL _r");  // only need this once
    BITOUT(r);
    BITOUT(r);
    BITOUT(r);
    BITOUT(r);
    BITOUT(r);
    BITOUT(r);
    BITOUT(r);
    BITOUT(r);
    BITOUT(g);
    BITOUT(g);
    BITOUT(g);
    BITOUT(g);
    BITOUT(g);
    BITOUT(g);
    BITOUT(g);
    BITOUT(g);
    BITOUT(b);
    BITOUT(b);
    BITOUT(b);
    BITOUT(b);
    BITOUT(b);
    BITOUT(b);
    BITOUT(b);
    BITOUT(b);
}


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
#define BROWNR	(0x45u)		// Normal Brown colour
#define BROWNG  (0x0Au)
#define BROWNB	(0x0Au)
#define BINHRR	(0x00u)		// Binary mode hour's colour when "1"
#define BINHRG  (0xFFu)
#define BINHRB	(0x00u)
#define BINMINR	(0x00u)		// Binary mode minute's colour when "1"
#define BINMING (0x00u)
#define BINMINB	(0xFFu)
#define BINSET1R (0xFFu)		// Setting mode's colour when "1"
#define BINSET1G (0xFFu)
#define BINSET1B (0x00u)
#define BINSET0R (0x0Fu)		// Setting mode's colour when "0"
#define BINSET0G (0x0Fu)
#define BINSET0B (0x0Fu)

enum {     Black=0, Brown, Red, Orange, Yellow, Green, Blue, Violet, Gray,  White} hours10, hours1, mins10, mins1, secs10, secs1;
TCHAR r[] = {0x00u, BROWNR, 0xFFu, 0xFFu,  0xFFu, 0x00u, 0x00u, 0x94u, 0x80u, 0xFFu};
TCHAR g[] = {0x00u, BROWNG, 0x00u, 0xA5u,  0xFFu, 0xFFu, 0x00u, 0x00u, 0x80u, 0xFFu};
TCHAR b[] = {0x00u, BROWNB, 0x00u, 0x00u,  0x00u, 0x00u, 0xFFu, 0xD3u, 0x80u, 0xFFu};
enum { RGBMode, BinaryMode, SettingMode } mode;
enum { HoursMode, MinutesMode } subMode;

TCHAR BCDToBinary (TCHAR bcd) {
	// convert BCD number in bcd to binary (e.g., 0x59 -> 0x3B)
	return bcd - (((bcd & 0xF0u) >> 3) * 3);
}

void SetBinary (TCHAR time) {
	time = BCDToBinary(time);
	secs1   = time & 0x1;			// LSBit
	secs10  = (time >> 1) & 0x1;
	mins1   = (time >> 2) & 0x1;
	mins10  = (time >> 3) & 0x1;
	hours1  = (time >> 4) & 0x1;
	hours10 = (time >> 5) & 0x1;	// MSBit	
}

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

void DecodeTime(void) {
	switch (mode) {
		case RGBMode:
			// restore Brown colour
			r[Brown] = BROWNR; g[Brown] = BROWNG; b[Brown] = BROWNB;
			secs1 = seconds & 0x0F;
			secs10 = seconds >> 4;
			mins1 = minutes & 0x0F;
			mins10 = minutes >> 4;
			hours1 = hours & 0x0F;
			hours10 = hours >> 4;
			break;
			
		case BinaryMode:
			// set Brown colour for binary mode
			if (subMode == HoursMode) {
				r[Brown] = BINHRR; g[Brown] =  BINHRG; b[Brown] =  BINHRB;
				SetBinary(hours);
				subMode = MinutesMode;
			} else {
				r[Brown] = BINMINR; g[Brown] =  BINMING; b[Brown] =  BINMINB;
				SetBinary(minutes);
				subMode = HoursMode;				
			}
			break;
			
		default:
			// Setting mode uses a light gray for 0 and yellow for 1
			r[Brown] = BINSET1R; g[Brown] = BINSET1G; b[Brown] = BINSET1B;
			r[Black] = BINSET0R; g[Black] = BINSET0G; b[Black] = BINSET0B;			
			break;
	}
}

void main (void) {
	/* Configure the oscillator for the device */
	ConfigureOscillator();

	/* Initialize I/O and Peripherals for application */
	InitApp();
	mode = RGBMode; subMode = MinutesMode;
//	secs1 = Black; secs10 = Black; hours1 = Black; hours10 = Black; mins1 = Black; mins10 = Black;

	while (1) {
		__delay_us(50);									// LCD reset
		WriteRGB(r[secs1],  g[secs1],  b[secs1]);		// seconds
		WriteRGB(r[secs10], g[secs10], b[secs10]);
		WriteRGB(r[mins1],  g[mins1],  b[mins1]);		// minutes
		WriteRGB(r[mins10], g[mins10], b[mins10]);
		WriteRGB(r[hours1], g[hours1], b[hours1]);		// hours
		WriteRGB(r[hours10], g[hours10], b[hours10]);
		
		__delay_ms(250); __delay_ms(250);
		__delay_ms(250); __delay_ms(250);
		if (mode != SettingMode) Clock_ReadTime();
		DecodeTime();
	}

}

