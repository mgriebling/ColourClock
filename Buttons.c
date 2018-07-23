
#include <pic12f1572.h>
#include "system.h"
#include "Buttons.h"

#define SetButton	(PORTAbits.RA1)
#define ModeButton	(PORTAbits.RA3)

static CARDINAL modeCount = 0;
static TCHAR prevSet = 1, prevMode = 1;
static BOOLEAN setPressed = FALSE, modePressed = FALSE;

void Buttons_UpdateState(void) {
	if (prevSet) {
		if (SetButton == 0) 
	}
}
	
BOOLEAN Buttons_IsModePressed(void) {
	if (SetButton == 0) {
		
	}
}
	
BOOLEAN Buttons_IsModeHeld(void) {
	return TRUE;
}

BOOLEAN Buttons_IsSetPressed(void) {
	
}

