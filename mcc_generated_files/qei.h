/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _QEI_H    /* Guard against multiple inclusion */
#define _QEI_H

//#define ENCA   (PORTCbits.RC10) /* RB6  PIN70 -> PIM PIN80 -> MCLV-2 HALL A*/  
//#define ENCB   (PORTEbits.RE14) /* RE14 PIN43 -> PIM PIN47 -> MCLV-2 HALL B*/
//#define ENCC   (PORTAbits.RA14) /* RA14 PIN66 -> PIM PIN48 -> MCLV-2 HALL C*/
//#define PULSE_PER_EREV  200
//#define PULSE_PER_REV   1000

    

    void QEI_Initialize (void);  
    int16_t GetQEIVel (void);

#endif /* _QEI_H */

/* *****************************************************************************
 End of File
 */
