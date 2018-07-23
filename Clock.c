
#include "Clock.h"
#include "I2C.h"

#define CONTROLREG	(0x07)
#define RTCSEC		(0x00)
#define RTCMIN		(0x01)
#define RTCHOUR		(0x02)

#define RTC_DEVICE	(0xDE)

TCHAR seconds, minutes, hours;

void Clock_ReadTime(void) {
	TCHAR buf[4];
	I2C_GetBuf(RTCSEC, buf, 3);		// Read the hours, minutes, seconds
	seconds = buf[0] & 0x7Fu;		// Ignore oscillator enable bit
	minutes = buf[1];
	hours  = buf[2];
//	if (!(seconds <= 0x59 && minutes <= 0x59 && hours <= 0x23)) {
//		seconds = 0x22; minutes = 0x22; hours = 0x22;
//	}
}

void Clock_SetTime(void) {
	TCHAR buf[4];
	buf[0] = seconds | 0x80u;		// Also set oscillator enable bit
	buf[1] = minutes;
	buf[2] = hours;					// Assumes 24-hour time
	I2C_SendBuf(RTCSEC, buf, 3);	// Write the hours, minutes, seconds
}

void Clock_BEGIN(void) {
	// Initialize the clock I2C bus pins via I2C_BEGIN
	I2C_BEGIN();
	
	// Initialize the clock chip
	I2C_SetDevice(RTC_DEVICE);
	I2C_Send(CONTROLREG, 0b01000000);	// 1Hz output
	seconds = 0; minutes = 0x59; hours = 0x11;
	Clock_SetTime();
}
