/* ************************************************************************** */
/** X2CMAIN.h

  @Company
    Microchip Technology

  @Summary
    X2C Model Interface functions

 */
/* ************************************************************************** */

#ifndef _X2CMAIN_H    /* Guard against multiple inclusion */
#define _X2CMAIN_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * 
 * Calls the inports update function
 * Then run model calculation
 * Last read model outports and update the peripherals
 * 
 * The selected model update mode is manual.
 * The X2C_Task() have to be called manually!
 * Note:
 * The model X2C sample time frequency must be the same 
 * as the X2C_Task() call frequency. 
 */
 void X2C_Task (void);

#endif/* X2CMAIN */

/* *****************************************************************************
 End of File
 */
