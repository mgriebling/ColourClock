/* 
 * File:   Buttons.h
 * Author: mikeg
 *
 * Created on July 21, 2018, 3:48 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system.h"	
	
extern BOOLEAN Buttons_IsModePressed(void);
extern BOOLEAN Buttons_IsModeHeld(void);
extern BOOLEAN Buttons_IsSetPressed(void);

extern void Buttons_BEGIN(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

