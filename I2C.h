

#ifndef I2C_H_
#define I2C_H_

#include "system.h"


#define I2C_SetDevice(dev) I2C_device = (TCHAR)dev

extern TCHAR I2C_device;
extern TCHAR * I2C_RxBuf;
extern TCHAR * I2C_TxBuf;

extern void I2C_Power(BOOLEAN TurnOn, BOOLEAN Count);
/* Memory power control.  ON turns memory power on; OFF turns memory power off. 
   Count = TRUE, enables automatic counting mode; otherwise, CPU counts bytes. */

extern BOOLEAN I2C_Device_Present(void);
/* Return TRUE iff the active device (I2C_device) is currently connected to the 
   I2C bus and responding with ACKs; otherwise, return FALSE. */

extern void I2C_Send(TCHAR adr, TCHAR byte);
/* Transmit a byte 'b'. */

extern void I2C_SendBuf(TCHAR adr, TCHAR * buf, CARDINAL size);
/* Transmit the contents of buffer 'buf'. */

extern TCHAR I2C_Get(TCHAR adr);
/* Receive a byte 'b'. */

//extern BOOLEAN I2C_GetAck(void);
///* Receive a byte 'b'. */

extern void I2C_GetBuf(TCHAR adr, TCHAR * buf, CARDINAL size);
/* Receive the contents of buffer 'buf'. */


extern void I2C_BEGIN(void);


#endif /* I2C_H_ */
