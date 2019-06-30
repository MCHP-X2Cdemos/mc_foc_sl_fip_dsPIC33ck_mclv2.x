/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
    
    typedef signed int SFRAC16;

    #define Q15(Float_Value)	\
        ((Float_Value < 0.0) ? (SFRAC16)(32768 * (Float_Value) - 0.5) \
        : (SFRAC16)(32767 * (Float_Value) + 0.5))

    #define FOSC 200000000
    #define PWMFREQUENCY 10000
    
        /* encoder */
    #define PULSE_PER_REV   1000                // ENCODER Pulses
    #define N_P             5                   // Electrical Pole-Pairs
    #define QEI_FACT        65535/((PULSE_PER_REV/N_P))
    #define QEI_FACT_MECH   65535/(PULSE_PER_REV)

    //#define QEI_FACT        65535/((PULSE_PER_REV/N_P)-1)
    
    #define DEADTIMESEC     0.000001            // Dead time in seconds - 1us
    #define DFCY            FOSC/2        // Instruction cycle frequency (Hz)

    #define DTCY            (1.0/DFCY)          // Instruction cycle period (sec)
    #define DDEADTIME       (unsigned int)(DEADTIMESEC*DFCY)	// Dead time in dTcys
    #define MIN_DUTY        (unsigned int)(DDEADTIME/2 + 1)        // Should be >= DDEADTIME/2 for PWM Errata workaround
    #define LOOPINTCY       (DFCY/PWMFREQUENCY) // Basic loop period in units of Tcy
    #define PWM_PERIODE     (LOOPINTCY/2)

    #define SPEED_SAMPLE_FREQ   100             /*In 1/seconds*/
    #define MAX_SPEED   3000                    /*rpm*/

  
    #define MAX_CURRENT 3.9                     /* Current BEMF_calc block has to be sync with this */
    #define OPAMP_GAIN  15
    #define SHUNT_R     0.025
    #define AD_RES      1024
    #define REF_VOLT    3.246

    #define PWM_MIN     0.02 * LOOPINTCY
    #define PWM_MAX     0.98 * LOOPINTCY
    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

