/**
  PWM Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm.h

  @Summary
    This is the generated header file for the PWM driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for PWM.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33CK256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef PWM_H
#define PWM_H

/**
 Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Data Type Definitions
*/

/** PWM Generator Definition
 
 @Summary 
   Defines the PWM generators available for PWM
 
 @Description
   This routine defines the PWM generators that are available for the module to use.
 
 Remarks:
   None
 */
typedef enum 
{
    PWM_GENERATOR_1 =  1,       
    PWM_GENERATOR_2 =  2,       
    PWM_GENERATOR_3 =  3,       
} PWM_GENERATOR;
        
/**
 Section: Interface Routines
*/

/**
  @Summary
    Initializes hardware and data for PWM module

  @Description
    This routine initializes hardware for PWM module,
    using the given hardware initialization data.  It also initializes all
    necessary internal data.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t masterPeriod,masterDutyCycle,masterPhase;

    masterPeriod = 0xFFFF;
    masterDutyCycle = 0xFF;
    masterPhase = 0xF;

    PWM_Initialize();
 
    PWM_ModuleDisable();

    PWM_MasterPeriodSet(masterPeriod);
    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_MasterPhaseSet(masterPhase);
 
    PWM_ModuleEnable(PWM_GENERATOR_1);

    </code>
*/
void PWM_Initialize (void);

/**
  @Summary
    Enables the specific PWM generator.

  @Description
    This routine is used to enable the specific PWM generator.

  @Param
    genNum - PWM generator instance number.

  @Returns
    None
 
  @Example 
    Refer to the example of PWM_Initialize();
*/
inline static void PWM_ModuleEnable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1CONLbits.ON = 1;              
                break;       
        case PWM_GENERATOR_2:
                PG2CONLbits.ON = 1;              
                break;       
        case PWM_GENERATOR_3:
                PG3CONLbits.ON = 1;              
                break;       
        default:break;    
    }     
}

/**
  @Summary
    Disables the specific PWM generator.

  @Description
    This routine is used to disable the specific PWM generator.

  @Param
    genNum - PWM generator instance number.

  @Returns
    None
 
  @Example 
    Refer to the example of PWM_Initialize();
*/
inline static void PWM_ModuleDisable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1CONLbits.ON = 0;              
                break;       
        case PWM_GENERATOR_2:
                PG2CONLbits.ON = 0;              
                break;       
        case PWM_GENERATOR_3:
                PG3CONLbits.ON = 0;              
                break;       
        default:break;    
    }    
}

/**
  @Summary
    Used to set the PWM master duty cycle register.

  @Description
    This routine is used to set the PWM master duty cycle register.

  @Param
    masterDutyCycle - Master Duty Cycle value.

  @Returns
    None
 
  @Example 
    Refer to the example of PWM_Initialize();
*/
inline static void PWM_MasterDutyCycleSet(uint16_t masterDutyCycle)
{
    MDC = masterDutyCycle;
}

/**
  @Summary
    Sets the period value for the Master Time Base generator.

  @Description
    This routine is used to set the period value for the Master Time Base generator.

  @Param
    masterPeriod - Period value.

  @Returns
    None
 
  @Example 
    Refer to the example of PWM_Initialize();
*/
inline static void PWM_MasterPeriodSet(uint16_t masterPeriod)
{
    MPER = masterPeriod;
}

/**
  @Summary
    Sets the phase value for the Master Time Base generator.

  @Description
    This routine is used to set the phase value for the Master Time Base generator.

  @Param
    masterPhase - Phase value.

  @Returns
    None
 
  @Example 
    Refer to the example of PWM_Initialize();
*/
inline static void PWM_MasterPhaseSet(uint16_t masterPhase)
{
    MPHASE = masterPhase;
}

/**
  @Summary
    Used to set the PWM generator specific duty cycle register.

  @Description
    This routine is used to set the PWM generator specific duty cycle register.

  @Param
    genNum      - PWM generator instance number.
    dutyCycle   - PWM generator duty cycle.

  @Returns
    None
 
  @Example 
    <code>    
    int16_t dutyCyle;
    
    dutyCycle = 0xFF;
    PWM_DutyCycleSet(PWM_GENERATOR_1, dutyCycle);
    </code>
*/
inline static void PWM_DutyCycleSet(PWM_GENERATOR genNum,uint16_t dutyCycle)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1DC = dutyCycle;              
                break;       
        case PWM_GENERATOR_2:
                PG2DC = dutyCycle;              
                break;       
        case PWM_GENERATOR_3:
                PG3DC = dutyCycle;              
                break;       
        default:break;    
    }  
}

/**
  @Summary
    Sets the period value for the PWM generator specific Time Base.

  @Description
    This routine is used to set the period value for the PWM generator specific Time Base.

  @Param
    genNum - PWM generator instance number.
    period - PWM generator period.

  @Returns
    None
 
  @Example 
    <code>    
    int16_t period;
    
    period = 0xFFFF;
    PWM_PeriodSet(PWM_GENERATOR_1, period);
    </code>
*/
inline static void PWM_PeriodSet(PWM_GENERATOR genNum,uint16_t period)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1PER = period;              
                break;       
        case PWM_GENERATOR_2:
                PG2PER = period;              
                break;       
        case PWM_GENERATOR_3:
                PG3PER = period;              
                break;       
        default:break;    
    }   
}

/**
  @Summary
    Sets the phase value for the PWM generator specific Time Base.

  @Description
    This routine is used to set the phase value for the PWM generator specific Time Base.

  @Param
    genNum - PWM generator instance number.
    phase - PWM generator phase value.

  @Returns
    None
 
  @Example 
    <code>    
    int16_t phase;
    
    phase = 0xFFFF;
    PWM_PhaseSet(PWM_GENERATOR_1, phase);
    </code>
*/
inline static void PWM_PhaseSet(PWM_GENERATOR genNum,uint16_t phase)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1PHASE = phase;              
                break;       
        case PWM_GENERATOR_2:
                PG2PHASE = phase;              
                break;       
        case PWM_GENERATOR_3:
                PG3PHASE = phase;              
                break;       
        default:break;    
    } 
}

/**
  @Summary
    Sets the TRIGA compare value for a specific PWM generator.

  @Description
    This routine is used to set the TRIGA compare value for a specific PWM generator.

  @Param
    genNum - PWM generator instance number.
    trigA  - TRIGA compare value.

  @Returns
    None
 
  @Example 
    <code>    
    int16_t trigA;
    
    trigA = 0xF;
    PWM_TRIGACompareSet(PWM_GENERATOR_1, trigA);
    </code>
*/
inline static void PWM_TRIGACompareSet(PWM_GENERATOR genNum,uint16_t trigA)
{ 
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1TRIGA = trigA;              
                break;       
        case PWM_GENERATOR_2:
                PG2TRIGA = trigA;              
                break;       
        case PWM_GENERATOR_3:
                PG3TRIGA = trigA;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Sets the TRIGB compare value for a specific PWM generator.

  @Description
    This routine is used to set the TRIGB compare value for a specific PWM generator.

  @Param
    genNum - PWM generator instance number.
    trigB  - TRIGB compare value.

  @Returns
    None
 
  @Example 
    <code>    
    int16_t trigB;
    
    trigB = 0xF;
    PWM_TRIGBCompareSet(PWM_GENERATOR_1, trigB);
    </code>
*/
inline static void PWM_TRIGBCompareSet(PWM_GENERATOR genNum,uint16_t trigB)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1TRIGB = trigB;              
                break;       
        case PWM_GENERATOR_2:
                PG2TRIGB = trigB;              
                break;       
        case PWM_GENERATOR_3:
                PG3TRIGB = trigB;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Sets the TRIGC compare value for a specific PWM generator.

  @Description
    This routine is used to set the TRIGC compare value for a specific PWM generator.

  @Param
    genNum - PWM generator instance number.
    trigC  - TRIGC compare value.

  @Returns
    None
 
  @Example 
    <code>    
    int16_t trigC;
    
    trigC = 0xF;
    PWM_TRIGCCompareSet(PWM_GENERATOR_1, trigC);
    </code>
*/
inline static void PWM_TRIGCCompareSet(PWM_GENERATOR genNum,uint16_t trigC)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1TRIGC = trigC;              
                break;       
        case PWM_GENERATOR_2:
                PG2TRIGC = trigC;              
                break;       
        case PWM_GENERATOR_3:
                PG3TRIGC = trigC;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Enables/Disables PWM override on PWML output for specific PWM generator.

  @Description
    This routine is used to enable/disable PWM override on PWML output for specific PWM generator.

  @Param
    genNum - PWM generator instance number.
    enableOverride  - Data to enable or disable override low. 

  @Returns
    None
 
  @Example 
    <code>    
    PWM_OverrideLowEnableSet(PWM_GENERATOR_1, enableOverride);
    </code>
*/  
inline static void PWM_OverrideLowEnableSet(PWM_GENERATOR genNum, bool enableOverride)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1IOCONLbits.OVRENL = enableOverride;              
                break;       
        case PWM_GENERATOR_2:
                PG2IOCONLbits.OVRENL = enableOverride;              
                break;       
        case PWM_GENERATOR_3:
                PG3IOCONLbits.OVRENL = enableOverride;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Enables/Disables PWM override on PWMH output for specific PWM generator.

  @Description
    This routine is used to enable/disable PWM override on PWMH output for specific PWM generator.

  @Param
    genNum - PWM generator instance number.
    enableOverride  - Data to enable or disable override high. 

  @Returns
    None
 
  @Example 
    <code>    
    PWM_OverrideHighEnableSet(PWM_GENERATOR_1, enableOverride);
    </code>
*/  
inline static void PWM_OverrideHighEnableSet(PWM_GENERATOR genNum, bool enableOverride)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1IOCONLbits.OVRENH = enableOverride;              
                break;       
        case PWM_GENERATOR_2:
                PG2IOCONLbits.OVRENH = enableOverride;              
                break;       
        case PWM_GENERATOR_3:
                PG3IOCONLbits.OVRENH = enableOverride;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Disables PWM override on PWMH output for specific PWM generator.

  @Description
    This routine is used to disable PWM override on PWMH output for specific PWM generator.

  @Param
    genNum - PWM generator instance number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_OverrideHighDisable(PWM_GENERATOR_1);
    </code>
*/  
inline static void PWM_OverrideHighDisable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1IOCONLbits.OVRENH = 0;              
                break;       
        case PWM_GENERATOR_2:
                PG2IOCONLbits.OVRENH = 0;              
                break;       
        case PWM_GENERATOR_3:
                PG3IOCONLbits.OVRENH = 0;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Updates PWM override data bits with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM override data bits with the requested value for a specific PWM generator.

  @Param
    genNum          - PWM generator instance number.
    overrideData    - Override data

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t overrideData;

    overrideData = 0x01;
    
    PWM_OverrideDataSet(PWM_GENERATOR_1, overrideData);
    </code>
*/  
inline static void PWM_OverrideDataSet(PWM_GENERATOR genNum,uint16_t overrideData)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1IOCONLbits.OVRDAT = overrideData;              
                break;       
        case PWM_GENERATOR_2:
                PG2IOCONLbits.OVRDAT = overrideData;              
                break;       
        case PWM_GENERATOR_3:
                PG3IOCONLbits.OVRDAT = overrideData;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Updates PWM Deadtime low register with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM Deadtime low register with the requested value for a specific PWM generator.

  @Param
    genNum      - PWM generator instance number.
    deadtimeLow - Deadtime low value.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t deadtimeLow;

    deadtimeLow = 0x01;
    
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, deadtimeLow);
    </code>
*/  
inline static void PWM_DeadTimeLowSet(PWM_GENERATOR genNum,uint16_t deadtimeLow)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1DTL = deadtimeLow;              
                break;       
        case PWM_GENERATOR_2:
                PG2DTL = deadtimeLow;              
                break;       
        case PWM_GENERATOR_3:
                PG3DTL = deadtimeLow;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Updates PWM Deadtime high register with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM Deadtime high register with the requested value for a specific PWM generator.

  @Param
    genNum          - PWM generator instance number.
    deadtimeHigh    - Deadtime high value.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t deadtimeHigh;

    deadtimeHigh = 0x01;
    
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, deadtimeHigh);
    </code>
*/  
inline static void PWM_DeadTimeHighSet(PWM_GENERATOR genNum,uint16_t deadtimeHigh)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1DTH = deadtimeHigh;              
                break;       
        case PWM_GENERATOR_2:
                PG2DTH = deadtimeHigh;              
                break;       
        case PWM_GENERATOR_3:
                PG3DTH = deadtimeHigh;              
                break;       
        default:break;    
    }
}

/**
  @Summary
    Requests to update the data registers for specific PWM generator.

  @Description
    This routine is used to request to update the data registers for specific PWM generator.

  @Param
    genNum - PWM generator instance number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_DataUpdateRequestSet(PWM_GENERATOR_1);
    </code>
*/  
inline static void PWM_DataUpdateRequestSet(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1STATbits.UPDREQ = 1;              
                break;       
        case PWM_GENERATOR_2:
                PG2STATbits.UPDREQ = 1;              
                break;       
        case PWM_GENERATOR_3:
                PG3STATbits.UPDREQ = 1;              
                break;       
        default:break;    
    }

}

/**
  @Summary
    Gets the status of the update request for specific PWM generator.

  @Description
    This routine is used to get the status of the update request for specific PWM generator

  @Param
    genNum - PWM generator instance number.

  @Returns
    None
 
  @Example 
    <code>    
    bool status;
    
    status = PWM_DataUpdateStatusGet(PWM_GENERATOR_1);
    </code>
*/  
inline static bool PWM_DataUpdateStatusGet(PWM_GENERATOR genNum)
{
    bool status = false;
    switch(genNum) { 
        case PWM_GENERATOR_1:
                status = PG1STATbits.UPDATE;              
                break;       
        case PWM_GENERATOR_2:
                status = PG2STATbits.UPDATE;              
                break;       
        case PWM_GENERATOR_3:
                status = PG3STATbits.UPDATE;              
                break;       
        default:break;   
    }
    return status;
}

/**
  @Summary
    Callback for PWM1 interrupt.

  @Description
    This routine is callback for PWM1 interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Generator1CallBack(void);
/**
  @Summary
    Tasks routine for PWM1.

  @Description
    This is a tasks routine for PWM1.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Tasks_Generator1(void);
/**
  @Summary
    Callback for PWM2 interrupt.

  @Description
    This routine is callback for PWM2 interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Generator2CallBack(void);
/**
  @Summary
    Tasks routine for PWM2.

  @Description
    This is a tasks routine for PWM2.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Tasks_Generator2(void);
/**
  @Summary
    Callback for PWM3 interrupt.

  @Description
    This routine is callback for PWM3 interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Generator3CallBack(void);
/**
  @Summary
    Tasks routine for PWM3.

  @Description
    This is a tasks routine for PWM3.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Tasks_Generator3(void);

/**
  @Summary
    Callback for EventA interrupt.

  @Description
    This routine is callback for EventA interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_EventACallBack(void);
/**
  @Summary
    Tasks routine for EventA.

  @Description
    This is a tasks routine for EventA.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Tasks_EventA(void);
/**
  @Summary
    Callback for EventB interrupt.

  @Description
    This routine is callback for EventB interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_EventBCallBack(void);
/**
  @Summary
    Tasks routine for EventB.

  @Description
    This is a tasks routine for EventB.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Tasks_EventB(void);
/**
  @Summary
    Callback for EventC interrupt.

  @Description
    This routine is callback for EventC interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_EventCCallBack(void);
/**
  @Summary
    Tasks routine for EventC.

  @Description
    This is a tasks routine for EventC.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Tasks_EventC(void);
/**
  @Summary
    Callback for EventD interrupt.

  @Description
    This routine is callback for EventD interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_EventDCallBack(void);
/**
  @Summary
    Tasks routine for EventD.

  @Description
    This is a tasks routine for EventD.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Tasks_EventD(void);
/**
  @Summary
    Callback for EventE interrupt.

  @Description
    This routine is callback for EventE interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_EventECallBack(void);
/**
  @Summary
    Tasks routine for EventE.

  @Description
    This is a tasks routine for EventE.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Tasks_EventE(void);
/**
  @Summary
    Callback for EventF interrupt.

  @Description
    This routine is callback for EventF interrupt

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_EventFCallBack(void);
/**
  @Summary
    Tasks routine for EventF.

  @Description
    This is a tasks routine for EventF.

  @Param
    None.

  @Returns
    None.
 
  @Example 
    None.
*/
void PWM_Tasks_EventF(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //PWM_H

