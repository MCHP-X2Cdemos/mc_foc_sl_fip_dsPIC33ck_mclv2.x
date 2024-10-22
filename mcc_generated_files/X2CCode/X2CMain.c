/* ************************************************************************** */
/** X2CMain.c

  @Company
    Microchip Technology

  @Summary
 Implementation of X2C In and Outport connections

 */
/* ************************************************************************** */
#include <xc.h>
#include "X2CMain.h"

#include "X2C.h"
#ifndef X2C_H
#warning "Please generate the code from the model!"
#endif

#include "../pin_manager.h"
#include "../adc1.h"
#include "../qei.h"
#include "../../userparms.h"

    static unsigned char S3_Value;
    static unsigned char S3_Value_old = 1;
    static unsigned char DebounceCnt;
    static unsigned char edge=0;
    static int16_t CpuLoad;
    static uint16_t POS1CNTtemp;

    volatile int16_t offset_AN0_IA=0, offset_ANA1_IB=0;
    
void UpdateInports(void) {

    /*
     * Pass the peripheral values to model Inports
     * if (PORTA & 1) { 
     *    x2cModel.inports.bInport = INT16_MAX;
     * }else {
     *    x2cModel.inports.bInport = 0;
     * }
     * 
     * The following inputs of the model can be used:
      x2cModel.inports.bCPU_LOAD = Scaling*A_PeripheralVariable
      x2cModel.inports.bI_a = Scaling*A_PeripheralVariable
      x2cModel.inports.bI_b = Scaling*A_PeripheralVariable
      x2cModel.inports.bI_sum = Scaling*A_PeripheralVariable
      x2cModel.inports.bQEI_POS = Scaling*A_PeripheralVariable
      x2cModel.inports.bQEI_VEL = Scaling*A_PeripheralVariable
      x2cModel.inports.bS2 = Scaling*A_PeripheralVariable
      x2cModel.inports.bS3 = Scaling*A_PeripheralVariable
      x2cModel.inports.bV_POT = Scaling*A_PeripheralVariable

     */
 
    if(ButtonS2_GetValue() == 0) x2cModel.inports.bS2 = false;
    else  x2cModel.inports.bS2 = true;
    
    /* Button latch and debounce */
    S3_Value = ButtonS3_GetValue();
    
    if(edge==0)
    {
        if (S3_Value != S3_Value_old) 
        {
            S3_Value_old = S3_Value;
            if(S3_Value)
            {
                DebounceCnt = 0;
                edge = 1;
            }
        }
    }
    else
    {
        DebounceCnt++;
        if(DebounceCnt >= 10)
        {           
            if(x2cModel.inports.bS3==0)
            {
                x2cModel.inports.bS3 = INT16_MAX;
            }
            else
            {
                x2cModel.inports.bS3 = 0;
            }
            
            DebounceCnt = 0;
            edge=0;
        }    
    }  

    /* ADC */   
    x2cModel.inports.bI_a = ADC1_ConversionResultGet(AN0_IA) - offset_AN0_IA; 
    x2cModel.inports.bI_b = ADC1_ConversionResultGet(ANA1_IB) - offset_ANA1_IB;
    x2cModel.inports.bV_POT = ADC1_ConversionResultGet(AN19_POT);   

    //Encoder caculation
    POS1CNTtemp = POS1CNTL;
    x2cModel.inports.bQEI_POS = (int16_t) (__builtin_mulss(POS1CNTtemp, QEI_FACT));
    x2cModel.inports.bQEI_VEL = GetQEIVel();
    
    x2cModel.inports.bCPU_LOAD = CpuLoad;
    
    
}

void UpdateOutports(void) {
    
    /*
     * Pass model outports to peripherals e.g.:
     * 
     * if (*x2cModel.outports.bOutport) {  // if model Outport differ than zero 
     *    LATB |= 1; // set LATB0 
     * } else {
     *    LATB &= ~1; // clear LATB0
     * }    
     * 
     * The following outputs of the model can be used:
      A_PeripheralVariable = *x2cModel.outports.bEstimated_angle*Scaling
      A_PeripheralVariable = *x2cModel.outports.bEstimated_speed*Scaling
      A_PeripheralVariable = *x2cModel.outports.bId*Scaling
      A_PeripheralVariable = *x2cModel.outports.bIq*Scaling
      A_PeripheralVariable = *x2cModel.outports.bON_OFF*Scaling
      A_PeripheralVariable = *x2cModel.outports.bpos*Scaling
      A_PeripheralVariable = *x2cModel.outports.bHOME_INIT*Scaling
      A_PeripheralVariable = *x2cModel.outports.bLED_D17*Scaling
      A_PeripheralVariable = *x2cModel.outports.bLED_D2*Scaling
      A_PeripheralVariable = *x2cModel.outports.bPWM1*Scaling
      A_PeripheralVariable = *x2cModel.outports.bPWM2*Scaling
      A_PeripheralVariable = *x2cModel.outports.bPWM3*Scaling
     */   
    
    if (x2cModel.inports.bS3)
    {
        PG1IOCONLbits.OVRENH = 0;
        PG1IOCONLbits.OVRENL = 0;
        PG2IOCONLbits.OVRENH = 0;
        PG2IOCONLbits.OVRENL = 0;
        PG3IOCONLbits.OVRENH = 0;
        PG3IOCONLbits.OVRENL = 0;        
        
        PG1DC = (PWM_PERIODE+(int16)(__builtin_mulss(*x2cModel.outports.bPWM1, PWM_PERIODE)>>15));
        PG2DC = (PWM_PERIODE+(int16)(__builtin_mulss(*x2cModel.outports.bPWM2, PWM_PERIODE)>>15));
        PG3DC = (PWM_PERIODE+(int16)(__builtin_mulss(*x2cModel.outports.bPWM3, PWM_PERIODE)>>15));
    }
    else
    {
        PG1IOCONLbits.OVRDAT = 0;
        PG2IOCONLbits.OVRDAT = 0;
        PG3IOCONLbits.OVRDAT = 0;
        PG1IOCONLbits.OVRENH = 1;
        PG1IOCONLbits.OVRENL = 1;
        PG2IOCONLbits.OVRENH = 1;
        PG2IOCONLbits.OVRENL = 1;
        PG3IOCONLbits.OVRENH = 1;
        PG3IOCONLbits.OVRENL = 1;        
        
    }
    
    /* Clear position counter on Home init */
    if (*x2cModel.outports.bHOME_INIT > 0) { 
    	POS1CNTL = 0; //*x2cModel.outports.bHOME_INIT;
    }
    
    if (*x2cModel.outports.bLED_D17) {
        LED1_SetHigh();
    }
    else {
        LED1_SetLow();
    }    
    
    if (*x2cModel.outports.bLED_D2) {
        LED2_SetHigh();
    }
    else {
        LED2_SetLow();
    }
}
/**
 * Calls the inports update function
 * Then run model calculation
 * Last read model outports and update the peripherals
*/

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADCAN0Interrupt ( void )
{
    volatile uint16_t valchannel_AN0;
    //Read the ADC value from the ADCBUF
    valchannel_AN0 = ADCBUF0;
    //clear the channel_AN1 interrupt flag
    IFS5bits.ADCAN0IF = 0;
    UpdateInports();
    X2C_Update();
    UpdateOutports();
}

/* *****************************************************************************
 End of File
 */
