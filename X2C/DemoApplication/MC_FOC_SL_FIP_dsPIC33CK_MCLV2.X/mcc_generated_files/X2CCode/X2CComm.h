/** X2CComm.c

  @Company
    Microchip Technology

  @Summary
    Implements the X2C Lin protocol connection with MCC Peripheral drivers.

 */

#ifndef _X2CCOMM_H    /* Guard against multiple inclusion */
#define _X2CCOMM_H

#include <xc.h>
#include "SerialGeneric.h"

void initX2CSerial (tSerial* serial);

#endif