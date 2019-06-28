/* ************************************************************************** */
/** X2CMAIN.h

  @Company
    Microchip Technology

  @Summary
    X2C util functions

 */
/* ************************************************************************** */

#ifndef _X2CUTILS_H    /* Guard against multiple inclusion */
#define _X2CUTILS_H


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

/**
 * Initialise X2C
 * 
 */
void X2C_Initialise(void);

/**
 * X2C Scope communication interface function
 */
void X2C_Communicate(void);

#endif /* X2CUTILS */

/* *****************************************************************************
 End of File
 */
