/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  dsPIC33CK256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
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

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "X2CUtils.h"
#include "X2CMain.h"
#include "pin_manager.h"
#include "userparms.h"
#include "adc1.h"
#include <stdbool.h>

/*
                         Main application
 */

//local functions
bool measureOffset(void);
void errorTrap(void); 

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    // Not working
    //INTERRUPT_GlobalEnable();
    
    if( measureOffset() == false){
        
    }
    
    
    INTCON2bits.GIE = true; // Start model calculation
    //Not possible to configure the following:
    //Signed fractional conversion format
    //ADCON1Hbits.FORM = 0b11;
    
    TMR1_Start();
    QEI_Initialize();
    while (1)
    {
        // Add your application code
        X2C_Communicate(); // X2C scope communication interface task. NON BLOCKING function.
    }
    return 1; 
    
}

/**
 * Measure offset before starting the motor
 * 
 * @return 1 - if measurement successful
 */

#define FCY (_XTAL_FREQ/2)
#include <libpic30.h>

extern int16_t offset_AN0_IA, offset_ANA1_IB;
bool measureOffset(void){
    int32_t adcOffsetIa = 0, adcOffsetIb = 0, adcOffsetIc = 0;
    uint32_t i = 0;

    /* Taking multiple samples to measure voltage
     * offset in all the channels */
    for (i = 0; i < CURRENT_OFFSET_SAMPLE_COUNT; i++)
    {
        while(!IFS5bits.ADCAN0IF); //Wait until next conversion not complete
        
        /* Sum up the converted results */
        adcOffsetIa += ADC1_ConversionResultGet(AN0_IA);
        adcOffsetIb += ADC1_ConversionResultGet(ANA1_IB);
        
        ADC1_IndividualChannelInterruptFlagClear(AN0_IA);
    }
    
    /* Averaging to find current offsets */
    offset_AN0_IA = (int16_t) (adcOffsetIa >> CURRENT_OFFSET_SAMPLE_SCALER);
    offset_ANA1_IB = (int16_t) (adcOffsetIb >> CURRENT_OFFSET_SAMPLE_SCALER);;
    
    //Check, if offset not too high
    if( (offset_AN0_IA & 0x7FFF) > CURRENT_MAX_OFFSET) {
        return false;
    }
    if( (offset_ANA1_IB & 0x7FFF) > CURRENT_MAX_OFFSET) {
        return false;
    }
    return true; //Measurement ok
}

void errorTrap(void){
    while(1){
        __delay_ms(100);
        LED1_Toggle(); //10Hz blinking
    }
}

/**
 End of File
*/

