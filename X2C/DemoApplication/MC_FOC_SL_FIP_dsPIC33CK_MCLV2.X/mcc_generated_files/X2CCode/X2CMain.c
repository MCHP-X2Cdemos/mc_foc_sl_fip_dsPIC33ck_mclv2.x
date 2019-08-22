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

#include "mcc.h"
#include "../qei.h"
#include "../../userparms.h"

    static unsigned char S3_Value;
    static unsigned char S3_Value_old = 1;
    static unsigned char DebounceCnt;
    static unsigned char edge=0;
    static int16_t CpuLoad;
    static uint16_t POS1CNTtemp;

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
    /* Button latch and debounce */
    S3_Value = ButtonS3_GetValue();
    
    if(S3_Value == 0) x2cModel.inports.bS2 = 0;
    else  x2cModel.inports.bS2 = INT16_MAX;
    
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
    x2cModel.inports.bI_a = ADC1_Core0ConversionResultGet();
    x2cModel.inports.bI_b = ADC1_Core1ConversionResultGet();
    x2cModel.inports.bV_POT = ADC1_SharedChannelAN19ConversionResultGet();  

    POS1CNTtemp = POS1CNTL;
    x2cModel.inports.bQEI_POS = (int16_t)(__builtin_mulss(POS1CNTtemp,QEI_FACT));  
//    x2cModel.inports.bQEI_POS_MECH = (int16_t)(__builtin_mulss(POS1CNTtemp,QEI_FACT_MECH));  
    
    
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
    
    PG1DC = (PWM_PERIODE+(int16)(__builtin_mulss(*x2cModel.outports.bPWM1, PWM_PERIODE)>>15));
    PG2DC = (PWM_PERIODE+(int16)(__builtin_mulss(*x2cModel.outports.bPWM2, PWM_PERIODE)>>15));
    PG3DC = (PWM_PERIODE+(int16)(__builtin_mulss(*x2cModel.outports.bPWM3, PWM_PERIODE)>>15));
    
    /* Clear position counter on Home init */
    if (*x2cModel.outports.bHOME_INIT > 0) { 
    	POS1CNTL = 0; //*x2cModel.outports.bHOME_INIT;
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
/*
 * The selected model update mode is manual.
 * The X2C_Task() have to be called manually!
 * Note:
 * The model X2C sample time frequency must be the same 
 * as the X2C_X2C_Task() call frequency. 
*/

 void X2C_Task (void){
    TMR1_Counter16BitSet(0);
    UpdateInports();
    X2C_Update();
    UpdateOutports();
    CpuLoad = TMR1_Counter16BitGet()*((uint16)INT16_MAX/LOOPINTCY);

}


/* *****************************************************************************
 End of File
 */
