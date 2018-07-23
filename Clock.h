/* 
 * File:   Clock.h
 * Author: michaelgriebling
 *
 * Created on November 4, 2015, 7:53 AM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif
	
#include "system.h"	
	
extern TCHAR seconds, minutes, hours;
	
extern void Clock_ReadTime(void);
extern void Clock_SetTime(void);

extern void Clock_BEGIN(void);

#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

