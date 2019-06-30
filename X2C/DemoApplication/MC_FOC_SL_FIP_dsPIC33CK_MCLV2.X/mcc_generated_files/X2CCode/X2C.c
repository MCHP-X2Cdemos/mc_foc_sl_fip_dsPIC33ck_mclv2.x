/* This file is part of X2C. http://x2c.lcm.at/                                                                       */

/* Model: MC_FOC_SL_FIP_dsPIC33CK_MCLV2                                                                               */
/* Date:  2019-06-26 09:50                                                                                            */

/* X2C-Version: 6.1.1707                                                                                              */
/* X2C-Edition: Free                                                                                                  */

/* Common includes                                                                                                    */
#include "TableStruct.h"
/* Generated file includes                                                                                            */
#include "FlashTable.h"
#include "RamTable.h"
#include "X2C.h"

/**********************************************************************************************************************/
/**                                                       Model                                                      **/
/**********************************************************************************************************************/
struct x2cModel x2cModel;

/**********************************************************************************************************************/
/**                                                       Scope                                                      **/
/**********************************************************************************************************************/
SCOPE_MAIN x2cScope;



/* Block function table                                                                                               */
#define END_BLOCKFUNCTIONS { (uint16)0, (void (*)(void*))0, (void (*)(void*))0, \
    (tLoadImplementationParameter)0, (tSaveImplementationParameter)0, (void* (*)(const void*, uint16))0 }
const tBlockFunctions blockFunctionTable[] = {
    FUNCTIONS,
    END_BLOCKFUNCTIONS
};

/* Parameter identifier table                                                                                         */
#define END_PARAMETERTABLE { (uint16)0, (void*)0 }
const tParameterTable parameterIdTable[] = {
    PARAMETER_TABLE,
    END_PARAMETERTABLE
};

/* Inport Parameter identifier table                                                                                  */
#define END_PARAMID_IO_TABLE { 0, 0, (void*)0 }
const tIoParamIdEntry inportParamIdTable[] = {
    INPORT_PARAMID_TABLE, 
    END_PARAMID_IO_TABLE
};

/* Outport Parameter identifier table                                                                                 */
const tIoParamIdEntry outportParamIdTable[] = {
    OUTPORT_PARAMID_TABLE, 
    END_PARAMID_IO_TABLE
};
/* Mask Parameter identifier table                                                                                    */
#define END_MASKPARAMID_TABLE { 0, (void*)0, (void*)0, (tSaveMaskParameter)0, (tLoadMaskParameter)0 }
static const tMaskParameterEntry maskParamIdTable[] = {
    END_MASKPARAMID_TABLE
};

/**********************************************************************************************************************/
/** Model Sample Time                                                                                                **/
/**********************************************************************************************************************/
float_CoT getModelSampleTime()
{
    return ((float_CoT)1.0E-4);
}

/**********************************************************************************************************************/
/**                                                  Initialization                                                  **/
/**********************************************************************************************************************/
void X2C_Init()
{
    /******************************************************************************************************************/
    /**                                          Initialize Block Parameters                                         **/
    /******************************************************************************************************************/

    /* Block: Constant3                                                                                               */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.bConstant3.K = 0;

    /* Block: Delay1                                                                                                  */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.bDelay1.In_old = 0;

    /* Block: Delay2                                                                                                  */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.bDelay2.In_old = 0;

    /* Block: Delay3                                                                                                  */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.bDelay3.In_old = 0;

    /* Block: FOC_main/Clark_Park                                                                                     */

    /* Block: FOC_main/Constant                                                                                       */
    /* Value = 0.2                                                                                                    */
    x2cModel.blocks.sFOC_main.bConstant.K = 6554;

    /* Block: FOC_main/Constant1                                                                                      */
    /* Value = 1.0                                                                                                    */
    x2cModel.blocks.sFOC_main.bConstant1.K = 32767;

    /* Block: FOC_main/Gain1                                                                                          */
    /* Gain = 0.98                                                                                                    */
    x2cModel.blocks.sFOC_main.bGain1.V = 32113;
    x2cModel.blocks.sFOC_main.bGain1.sfr = 15;

    /* Block: FOC_main/Gain2                                                                                          */
    /* Gain = 0.98                                                                                                    */
    x2cModel.blocks.sFOC_main.bGain2.V = 32113;
    x2cModel.blocks.sFOC_main.bGain2.sfr = 15;

    /* Block: FOC_main/ManualSwitch                                                                                   */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.sFOC_main.bManualSwitch.Toggle = 1;

    /* Block: FOC_main/ManualSwitch1                                                                                  */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.sFOC_main.bManualSwitch1.Toggle = 1;

    /* Block: FOC_main/ManualSwitch2                                                                                  */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.sFOC_main.bManualSwitch2.Toggle = 1;

    /* Block: FOC_main/ManualSwitch3                                                                                  */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.sFOC_main.bManualSwitch3.Toggle = 1;

    /* Block: FOC_main/ManualSwitch4                                                                                  */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.sFOC_main.bManualSwitch4.Toggle = 1;

    /* Block: FOC_main/Not                                                                                            */

    /* Block: FOC_main/OpenLoop_Vd                                                                                    */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sFOC_main.bOpenLoop_Vd.K = 0;

    /* Block: FOC_main/OpenLoop_Vq                                                                                    */
    /* Value = 0.3                                                                                                    */
    x2cModel.blocks.sFOC_main.bOpenLoop_Vq.K = 9830;

    /* Block: FOC_main/PI_flux                                                                                        */
    /* Kp = 0.8                                                                                                       */
    /* Ki = 0.5                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.bPI_flux.b0 = 2;
    x2cModel.blocks.sFOC_main.bPI_flux.b1 = 26214;
    x2cModel.blocks.sFOC_main.bPI_flux.sfrb0 = 15;
    x2cModel.blocks.sFOC_main.bPI_flux.sfrb1 = 15;
    x2cModel.blocks.sFOC_main.bPI_flux.i_old = 0;
    x2cModel.blocks.sFOC_main.bPI_flux.enable_old = 0;

    /* Block: FOC_main/PI_torque                                                                                      */
    /* Kp = 0.8                                                                                                       */
    /* Ki = 0.5                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.bPI_torque.b0 = 2;
    x2cModel.blocks.sFOC_main.bPI_torque.b1 = 26214;
    x2cModel.blocks.sFOC_main.bPI_torque.sfrb0 = 15;
    x2cModel.blocks.sFOC_main.bPI_torque.sfrb1 = 15;
    x2cModel.blocks.sFOC_main.bPI_torque.i_old = 0;
    x2cModel.blocks.sFOC_main.bPI_torque.enable_old = 0;

    /* Block: FOC_main/PLLEstimator/BEMF_calc                                                                         */
    /* Ls = 0.41                                                                                                      */
    /* Rs = 0.35                                                                                                      */
    /* U0 = 24.0                                                                                                      */
    /* I0 = 3.95                                                                                                      */
    /* ts_fact = 1.0                                                                                                  */
    /* CurrentSampleFactor = 10.0                                                                                     */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.Ls = 2211;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.Rs = 1888;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.sfrLs = 15;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.sfrRs = 15;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.Ib_old = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.Ia_old = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.CurrentSampleFactor = 10;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.V_Ls_alpha = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.V_Ls_beta = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.FactCounter = 0;

    /* Block: FOC_main/PLLEstimator/Constant1                                                                         */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bConstant1.K = 0;

    /* Block: FOC_main/PLLEstimator/Delay1                                                                            */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bDelay1.In_old = 0;

    /* Block: FOC_main/PLLEstimator/Edfilter                                                                          */
    /* V = 1.0                                                                                                        */
    /* fc = 400.0                                                                                                     */
    /* ts_fact = 1.0                                                                                                  */
    /* method = zoh                                                                                                   */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.b0 = 7282;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.b1 = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.a0 = -25486;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.sfrb = 15;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.sfra = 15;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.in_old = 0;

    /* Block: FOC_main/PLLEstimator/Eqfilter                                                                          */
    /* V = 1.0                                                                                                        */
    /* fc = 400.0                                                                                                     */
    /* ts_fact = 1.0                                                                                                  */
    /* method = zoh                                                                                                   */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.b0 = 7282;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.b1 = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.a0 = -25486;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.sfrb = 15;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.sfra = 15;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.in_old = 0;

    /* Block: FOC_main/PLLEstimator/Park                                                                              */

    /* Block: FOC_main/PLLEstimator/Speed_Estim_Superblock/Add                                                        */

    /* Block: FOC_main/PLLEstimator/Speed_Estim_Superblock/AutoSwitch                                                 */
    /* Thresh_up = 0.0                                                                                                */
    /* Thresh_down = 0.0                                                                                              */
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch.Thresh_up = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch.Thresh_down = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch.Status = &RamTable_int16[0];

    /* Block: FOC_main/PLLEstimator/Speed_Estim_Superblock/Gain                                                       */
    /* Gain = 0.65                                                                                                    */
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain.V = 21299;
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain.sfr = 15;

    /* Block: FOC_main/PLLEstimator/Speed_Estim_Superblock/Sub                                                        */

    /* Block: FOC_main/PLLEstimator/uI                                                                                */
    /* Ki = 800.0                                                                                                     */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.sPLLEstimator.buI.b0 = 2621;
    x2cModel.blocks.sFOC_main.sPLLEstimator.buI.sfr = 15;
    x2cModel.blocks.sFOC_main.sPLLEstimator.buI.i_old = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.buI.enable_old = 0;

    /* Block: FOC_main/Park_Clark_inv                                                                                 */

    /* Block: FOC_main/Saturation                                                                                     */
    /* max = 0.98                                                                                                     */
    /* min = -0.98                                                                                                    */
    x2cModel.blocks.sFOC_main.bSaturation.max = 32113;
    x2cModel.blocks.sFOC_main.bSaturation.min = -32113;

    /* Block: FOC_main/Saturation1                                                                                    */
    /* max = 0.98                                                                                                     */
    /* min = -0.98                                                                                                    */
    x2cModel.blocks.sFOC_main.bSaturation1.max = 32113;
    x2cModel.blocks.sFOC_main.bSaturation1.min = -32113;

    /* Block: FOC_main/Sin3Gen                                                                                        */
    /* fmax = 100.0                                                                                                   */
    /* Offset = 0.0                                                                                                   */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sFOC_main.bSin3Gen.delta_phi = 655;
    x2cModel.blocks.sFOC_main.bSin3Gen.offset = 0;
    x2cModel.blocks.sFOC_main.bSin3Gen.phi = 0;

    /* Block: FOC_main/Sub_flux                                                                                       */

    /* Block: FOC_main/Sub_torque                                                                                     */

    /* Block: FOC_main/TypeConv2                                                                                      */

    /* Block: FOC_main/initForcedValue                                                                                */
    /* Value = 0.2                                                                                                    */
    x2cModel.blocks.sFOC_main.binitForcedValue.K = 6554;

    /* Block: Gain                                                                                                    */
    /* Gain = 0.8                                                                                                     */
    x2cModel.blocks.bGain.V = 26214;
    x2cModel.blocks.bGain.sfr = 15;

    /* Block: Gain1                                                                                                   */
    /* Gain = 0.0030                                                                                                  */
    x2cModel.blocks.bGain1.V = 98;
    x2cModel.blocks.bGain1.sfr = 15;

    /* Block: ManualSwitch                                                                                            */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.bManualSwitch.Toggle = 1;

    /* Block: ManualSwitch1                                                                                           */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.bManualSwitch1.Toggle = 1;

    /* Block: Negation                                                                                                */

    /* Block: speedPI/PI_speed                                                                                        */
    /* Kp = 2.0                                                                                                       */
    /* Ki = 1.0                                                                                                       */
    /* ts_fact = 10.0                                                                                                 */
    x2cModel.blocks.sspeedPI.bPI_speed.b0 = 33;
    x2cModel.blocks.sspeedPI.bPI_speed.b1 = 16384;
    x2cModel.blocks.sspeedPI.bPI_speed.sfrb0 = 15;
    x2cModel.blocks.sspeedPI.bPI_speed.sfrb1 = 13;
    x2cModel.blocks.sspeedPI.bPI_speed.i_old = 0;
    x2cModel.blocks.sspeedPI.bPI_speed.enable_old = 0;

    /* Block: speedPI/RateLimiter                                                                                     */
    /* Tr = 0.0010                                                                                                    */
    /* Tf = 0.0010                                                                                                    */
    /* ts_fact = 10.0                                                                                                 */
    x2cModel.blocks.sspeedPI.bRateLimiter.RateUp = 2147483647;
    x2cModel.blocks.sspeedPI.bRateLimiter.RateDown = 2147483647;
    x2cModel.blocks.sspeedPI.bRateLimiter.out_old = 0;
    x2cModel.blocks.sspeedPI.bRateLimiter.enable_old = 0;

    /* Block: speedPI/Speed_Init                                                                                      */
    /* Value = 1.0                                                                                                    */
    x2cModel.blocks.sspeedPI.bSpeed_Init.K = 1;

    /* Block: speedPI/Speed_Init1                                                                                     */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sspeedPI.bSpeed_Init1.K = 0;

    /* Block: speedPI/Speed_error                                                                                     */

    /* Block: startup/AutoSwitch                                                                                      */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sstartup.bAutoSwitch.Thresh_up = 16384;
    x2cModel.blocks.sstartup.bAutoSwitch.Thresh_down = 16384;
    x2cModel.blocks.sstartup.bAutoSwitch.Status = &RamTable_int16[1];

    /* Block: startup/AutoSwitch1                                                                                     */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sstartup.bAutoSwitch1.Thresh_up = 16384;
    x2cModel.blocks.sstartup.bAutoSwitch1.Thresh_down = 16384;
    x2cModel.blocks.sstartup.bAutoSwitch1.Status = &RamTable_int16[2];

    /* Block: startup/AutoSwitch2                                                                                     */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sstartup.bAutoSwitch2.Thresh_up = 16384;
    x2cModel.blocks.sstartup.bAutoSwitch2.Thresh_down = 16384;
    x2cModel.blocks.sstartup.bAutoSwitch2.Status = &RamTable_int16[3];

    /* Block: startup/Constant1                                                                                       */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.bConstant1.K = 0;

    /* Block: startup/Constant5                                                                                       */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.bConstant5.K = 0;

    /* Block: startup/Constant6                                                                                       */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.bConstant6.K = 0;

    /* Block: startup/Delay50/Delay                                                                                   */
    /* ts_fact = 50.0                                                                                                 */
    x2cModel.blocks.sstartup.sDelay50.bDelay.In_old = 0;

    /* Block: startup/Flux_select                                                                                     */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sstartup.bFlux_select.Thresh_up = 16384;
    x2cModel.blocks.sstartup.bFlux_select.Thresh_down = 16384;
    x2cModel.blocks.sstartup.bFlux_select.Status = &RamTable_int16[4];

    /* Block: startup/Flux_select1                                                                                    */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sstartup.bFlux_select1.Thresh_up = 16384;
    x2cModel.blocks.sstartup.bFlux_select1.Thresh_down = 16384;
    x2cModel.blocks.sstartup.bFlux_select1.Status = &RamTable_int16[5];

    /* Block: startup/Ramp_Up_Current                                                                                 */
    /* Value = 0.2                                                                                                    */
    x2cModel.blocks.sstartup.bRamp_Up_Current.K = 6554;

    /* Block: startup/Ramp_Up_SB/Constant4                                                                            */
    /* Value = 0.2                                                                                                    */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bConstant4.K = 6554;

    /* Block: startup/Ramp_Up_SB/I_Init_Zero                                                                          */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero.K = 0;

    /* Block: startup/Ramp_Up_SB/I_Init_Zero1                                                                         */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero1.K = 0;

    /* Block: startup/Ramp_Up_SB/Ramp_Up_PositionGenerator                                                            */
    /* Ki = 100.0                                                                                                     */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.b0 = 328;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.sfr = 15;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.i_old = 0;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.enable_old = 0;

    /* Block: startup/Ramp_Up_SB/RateLimiter                                                                          */
    /* Tr = 1.5                                                                                                       */
    /* Tf = 1.5                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter.RateUp = 143166;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter.RateDown = 143166;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter.out_old = 0;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter.enable_old = 0;

    /* Block: startup/Ramp_Up_SB/Saturation                                                                           */
    /* max = 2.0                                                                                                      */
    /* min = -2.0                                                                                                     */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation.max = 32767;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation.min = -32767;

    /* Block: startup/Ramp_Up_SB/Speed_Ramp_UP_I                                                                      */
    /* Ki = 1.0                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.b0 = 3;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.sfr = 15;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.i_old = 0;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.enable_old = 0;

    /* Block: startup/Ramp_Up_SB/TypeConv                                                                             */

    /* Block: startup/Ramp_Up_SB/TypeConv1                                                                            */

    /* Block: startup/RateLimiter                                                                                     */
    /* Tr = 2.0                                                                                                       */
    /* Tf = 2.0                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.bRateLimiter.RateUp = 107374;
    x2cModel.blocks.sstartup.bRateLimiter.RateDown = 107374;
    x2cModel.blocks.sstartup.bRateLimiter.out_old = 0;
    x2cModel.blocks.sstartup.bRateLimiter.enable_old = 0;

    /* Block: startup/RateLimiter1                                                                                    */
    /* Tr = 0.0040                                                                                                    */
    /* Tf = 0.0040                                                                                                    */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.bRateLimiter1.RateUp = 53687091;
    x2cModel.blocks.sstartup.bRateLimiter1.RateDown = 53687091;
    x2cModel.blocks.sstartup.bRateLimiter1.out_old = 0;
    x2cModel.blocks.sstartup.bRateLimiter1.enable_old = 0;

    /* Block: startup/RateLimiter2                                                                                    */
    /* Tr = 0.6                                                                                                       */
    /* Tf = 0.6                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.bRateLimiter2.RateUp = 357914;
    x2cModel.blocks.sstartup.bRateLimiter2.RateDown = 357914;
    x2cModel.blocks.sstartup.bRateLimiter2.out_old = 0;
    x2cModel.blocks.sstartup.bRateLimiter2.enable_old = 0;

    /* Block: startup/Sequencer                                                                                       */
    /* Delay1 = 0.4                                                                                                   */
    /* Delay2 = 2.7                                                                                                   */
    /* Delay3 = 3.0                                                                                                   */
    /* Delay4 = 2.2                                                                                                   */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.bSequencer.delay1 = 4000;
    x2cModel.blocks.sstartup.bSequencer.delay2 = 27000;
    x2cModel.blocks.sstartup.bSequencer.delay3 = 30000;
    x2cModel.blocks.sstartup.bSequencer.delay4 = 22000;
    x2cModel.blocks.sstartup.bSequencer.cnt = 0;
    x2cModel.blocks.sstartup.bSequencer.start_old = 0;

    /* Block: startup/TypeConv                                                                                        */

    /* Block: startup/TypeConv1                                                                                       */

    /* Block: startup/TypeConv2                                                                                       */


    /* Initialize RAM table content */
    initRamTables();

    /******************************************************************************************************************/
    /**                                              Initialize Inports                                              **/
    /******************************************************************************************************************/
    x2cModel.inports.bCPU_LOAD = (int16)0;
    x2cModel.inports.bI_a = (int16)0;
    x2cModel.inports.bI_b = (int16)0;
    x2cModel.inports.bI_sum = (int16)0;
    x2cModel.inports.bQEI_POS = (int16)0;
    x2cModel.inports.bQEI_VEL = (int16)0;
    x2cModel.inports.bS2 = false;
    x2cModel.inports.bS3 = (int16)0;
    x2cModel.inports.bV_POT = (int16)0;

    /******************************************************************************************************************/
    /**                                               Link Block Inputs                                              **/
    /******************************************************************************************************************/

    /* Block Constant3                                                                                                */

    /* Block Delay1                                                                                                   */
    x2cModel.blocks.bDelay1.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain.Out;

    /* Block Delay2                                                                                                   */
    x2cModel.blocks.bDelay2.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.buI.Out;

    /* Block Delay3                                                                                                   */
    x2cModel.blocks.bDelay3.In =
        &x2cModel.blocks.sFOC_main.bClark_Park.d;

    /* Block Clark_Park                                                                                               */
    x2cModel.blocks.sFOC_main.bClark_Park.a =
        &x2cModel.inports.bI_a;
    x2cModel.blocks.sFOC_main.bClark_Park.b =
        &x2cModel.inports.bI_b;
    x2cModel.blocks.sFOC_main.bClark_Park.theta =
        &x2cModel.blocks.sstartup.bAutoSwitch1.Out;

    /* Block Constant                                                                                                 */

    /* Block Constant1                                                                                                */

    /* Block Gain1                                                                                                    */
    x2cModel.blocks.sFOC_main.bGain1.In =
        &x2cModel.blocks.sFOC_main.bPark_Clark_inv.Valpha;

    /* Block Gain2                                                                                                    */
    x2cModel.blocks.sFOC_main.bGain2.In =
        &x2cModel.blocks.sFOC_main.bPark_Clark_inv.Vbeta;

    /* Block ManualSwitch                                                                                             */
    x2cModel.blocks.sFOC_main.bManualSwitch.In1 =
        &x2cModel.blocks.sFOC_main.bOpenLoop_Vd.Out;
    x2cModel.blocks.sFOC_main.bManualSwitch.In2 =
        &x2cModel.blocks.sFOC_main.bPI_flux.Out;

    /* Block ManualSwitch1                                                                                            */
    x2cModel.blocks.sFOC_main.bManualSwitch1.In1 =
        &x2cModel.blocks.sFOC_main.bOpenLoop_Vq.Out;
    x2cModel.blocks.sFOC_main.bManualSwitch1.In2 =
        &x2cModel.blocks.sFOC_main.bPI_torque.Out;

    /* Block ManualSwitch2                                                                                            */
    x2cModel.blocks.sFOC_main.bManualSwitch2.In1 =
        &x2cModel.blocks.sFOC_main.bSin3Gen.u;
    x2cModel.blocks.sFOC_main.bManualSwitch2.In2 =
        &x2cModel.blocks.sFOC_main.bPark_Clark_inv.A;

    /* Block ManualSwitch3                                                                                            */
    x2cModel.blocks.sFOC_main.bManualSwitch3.In1 =
        &x2cModel.blocks.sFOC_main.bSin3Gen.v;
    x2cModel.blocks.sFOC_main.bManualSwitch3.In2 =
        &x2cModel.blocks.sFOC_main.bPark_Clark_inv.B;

    /* Block ManualSwitch4                                                                                            */
    x2cModel.blocks.sFOC_main.bManualSwitch4.In1 =
        &x2cModel.blocks.sFOC_main.bSin3Gen.w;
    x2cModel.blocks.sFOC_main.bManualSwitch4.In2 =
        &x2cModel.blocks.sFOC_main.bPark_Clark_inv.C;

    /* Block Not                                                                                                      */
    x2cModel.blocks.sFOC_main.bNot.In =
        &x2cModel.blocks.sFOC_main.bTypeConv2.Out;

    /* Block OpenLoop_Vd                                                                                              */

    /* Block OpenLoop_Vq                                                                                              */

    /* Block PI_flux                                                                                                  */
    x2cModel.blocks.sFOC_main.bPI_flux.In =
        &x2cModel.blocks.sFOC_main.bSub_flux.Out;
    x2cModel.blocks.sFOC_main.bPI_flux.Init =
        &x2cModel.blocks.sFOC_main.bSub_flux.Out;
    x2cModel.blocks.sFOC_main.bPI_flux.Enable =
        &x2cModel.blocks.sFOC_main.bTypeConv2.Out;

    /* Block PI_torque                                                                                                */
    x2cModel.blocks.sFOC_main.bPI_torque.In =
        &x2cModel.blocks.sFOC_main.bSub_torque.Out;
    x2cModel.blocks.sFOC_main.bPI_torque.Init =
        &x2cModel.blocks.sFOC_main.bSub_torque.Out;
    x2cModel.blocks.sFOC_main.bPI_torque.Enable =
        &x2cModel.blocks.sFOC_main.bTypeConv2.Out;

    /* Block BEMF_calc                                                                                                */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.Ialpha =
        &x2cModel.blocks.sFOC_main.bClark_Park.alpha;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.Ibeta =
        &x2cModel.blocks.sFOC_main.bClark_Park.beta;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.Valpha =
        &x2cModel.blocks.sFOC_main.bGain1.Out;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.Vbeta =
        &x2cModel.blocks.sFOC_main.bGain2.Out;

    /* Block Constant1                                                                                                */

    /* Block Delay1                                                                                                   */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bDelay1.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.buI.Out;

    /* Block Edfilter                                                                                                 */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bPark.d;

    /* Block Eqfilter                                                                                                 */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bPark.q;

    /* Block Park                                                                                                     */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bPark.alpha =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.BEMFalpha;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bPark.beta =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc.BEMFbeta;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bPark.theta =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bDelay1.Out;

    /* Block Add                                                                                                      */
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAdd.In1 =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.Out;
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAdd.In2 =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.Out;

    /* Block AutoSwitch                                                                                               */
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch.In1 =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bSub.Out;
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch.Switch =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.Out;
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch.In3 =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAdd.Out;

    /* Block Gain                                                                                                     */
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch.Out;

    /* Block Sub                                                                                                      */
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bSub.Plus =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.Out;
    x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bSub.Minus =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.Out;

    /* Block uI                                                                                                       */
    x2cModel.blocks.sFOC_main.sPLLEstimator.buI.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain.Out;
    x2cModel.blocks.sFOC_main.sPLLEstimator.buI.Init =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bConstant1.Out;
    x2cModel.blocks.sFOC_main.sPLLEstimator.buI.Enable =
        &x2cModel.blocks.sFOC_main.bTypeConv2.Out;

    /* Block Park_Clark_inv                                                                                           */
    x2cModel.blocks.sFOC_main.bPark_Clark_inv.d =
        &x2cModel.blocks.sFOC_main.bSaturation1.Out;
    x2cModel.blocks.sFOC_main.bPark_Clark_inv.q =
        &x2cModel.blocks.sFOC_main.bSaturation.Out;
    x2cModel.blocks.sFOC_main.bPark_Clark_inv.theta =
        &x2cModel.blocks.sstartup.bAutoSwitch1.Out;
    x2cModel.blocks.sFOC_main.bPark_Clark_inv.forcedMode =
        &x2cModel.blocks.sFOC_main.bNot.Out;
    x2cModel.blocks.sFOC_main.bPark_Clark_inv.forcedValue =
        &x2cModel.blocks.sFOC_main.binitForcedValue.Out;

    /* Block Saturation                                                                                               */
    x2cModel.blocks.sFOC_main.bSaturation.In =
        &x2cModel.blocks.sFOC_main.bManualSwitch1.Out;

    /* Block Saturation1                                                                                              */
    x2cModel.blocks.sFOC_main.bSaturation1.In =
        &x2cModel.blocks.sFOC_main.bManualSwitch.Out;

    /* Block Sin3Gen                                                                                                  */
    x2cModel.blocks.sFOC_main.bSin3Gen.A =
        &x2cModel.blocks.sFOC_main.bConstant.Out;
    x2cModel.blocks.sFOC_main.bSin3Gen.f =
        &x2cModel.blocks.sFOC_main.bConstant1.Out;

    /* Block Sub_flux                                                                                                 */
    x2cModel.blocks.sFOC_main.bSub_flux.Plus =
        &x2cModel.blocks.sstartup.bFlux_select1.Out;
    x2cModel.blocks.sFOC_main.bSub_flux.Minus =
        &x2cModel.blocks.sFOC_main.bClark_Park.d;

    /* Block Sub_torque                                                                                               */
    x2cModel.blocks.sFOC_main.bSub_torque.Plus =
        &x2cModel.blocks.sstartup.bAutoSwitch2.Out;
    x2cModel.blocks.sFOC_main.bSub_torque.Minus =
        &x2cModel.blocks.sFOC_main.bClark_Park.q;

    /* Block TypeConv2                                                                                                */
    x2cModel.blocks.sFOC_main.bTypeConv2.In =
        &x2cModel.blocks.sstartup.bSequencer.Out1;

    /* Block initForcedValue                                                                                          */

    /* Block Gain                                                                                                     */
    x2cModel.blocks.bGain.In =
        &x2cModel.inports.bV_POT;

    /* Block Gain1                                                                                                    */
    x2cModel.blocks.bGain1.In =
        &x2cModel.blocks.bNegation.Out;

    /* Block ManualSwitch                                                                                             */
    x2cModel.blocks.bManualSwitch.In1 =
        &x2cModel.inports.bQEI_POS;
    x2cModel.blocks.bManualSwitch.In2 =
        &x2cModel.blocks.bDelay2.Out;

    /* Block ManualSwitch1                                                                                            */
    x2cModel.blocks.bManualSwitch1.In1 =
        &x2cModel.inports.bQEI_VEL;
    x2cModel.blocks.bManualSwitch1.In2 =
        &x2cModel.blocks.bDelay1.Out;

    /* Block Negation                                                                                                 */
    x2cModel.blocks.bNegation.In =
        &x2cModel.blocks.sstartup.bSequencer.Out1;

    /* Block PI_speed                                                                                                 */
    x2cModel.blocks.sspeedPI.bPI_speed.In =
        &x2cModel.blocks.sspeedPI.bSpeed_error.Out;
    x2cModel.blocks.sspeedPI.bPI_speed.Init =
        &x2cModel.blocks.bManualSwitch1.Out;
    x2cModel.blocks.sspeedPI.bPI_speed.Enable =
        &x2cModel.blocks.sstartup.bTypeConv1.Out;

    /* Block RateLimiter                                                                                              */
    x2cModel.blocks.sspeedPI.bRateLimiter.In =
        &x2cModel.blocks.sspeedPI.bPI_speed.Out;
    x2cModel.blocks.sspeedPI.bRateLimiter.Init =
        &x2cModel.blocks.sspeedPI.bSpeed_Init1.Out;
    x2cModel.blocks.sspeedPI.bRateLimiter.Enable =
        &x2cModel.blocks.sspeedPI.bSpeed_Init.Out;

    /* Block Speed_Init                                                                                               */

    /* Block Speed_Init1                                                                                              */

    /* Block Speed_error                                                                                              */
    x2cModel.blocks.sspeedPI.bSpeed_error.Plus =
        &x2cModel.blocks.bGain.Out;
    x2cModel.blocks.sspeedPI.bSpeed_error.Minus =
        &x2cModel.blocks.bManualSwitch1.Out;

    /* Block AutoSwitch                                                                                               */
    x2cModel.blocks.sstartup.bAutoSwitch.In1 =
        &x2cModel.blocks.bManualSwitch.Out;
    x2cModel.blocks.sstartup.bAutoSwitch.Switch =
        &x2cModel.blocks.sstartup.bSequencer.Out3;
    x2cModel.blocks.sstartup.bAutoSwitch.In3 =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.Out;

    /* Block AutoSwitch1                                                                                              */
    x2cModel.blocks.sstartup.bAutoSwitch1.In1 =
        &x2cModel.blocks.bManualSwitch.Out;
    x2cModel.blocks.sstartup.bAutoSwitch1.Switch =
        &x2cModel.blocks.sstartup.sDelay50.bDelay.Out;
    x2cModel.blocks.sstartup.bAutoSwitch1.In3 =
        &x2cModel.blocks.sstartup.bRateLimiter1.Out;

    /* Block AutoSwitch2                                                                                              */
    x2cModel.blocks.sstartup.bAutoSwitch2.In1 =
        &x2cModel.blocks.sspeedPI.bRateLimiter.Out;
    x2cModel.blocks.sstartup.bAutoSwitch2.Switch =
        &x2cModel.blocks.sstartup.bSequencer.Out3;
    x2cModel.blocks.sstartup.bAutoSwitch2.In3 =
        &x2cModel.blocks.sstartup.bRateLimiter2.Out;

    /* Block Constant1                                                                                                */

    /* Block Constant5                                                                                                */

    /* Block Constant6                                                                                                */

    /* Block Delay                                                                                                    */
    x2cModel.blocks.sstartup.sDelay50.bDelay.In =
        &x2cModel.blocks.sstartup.bSequencer.Out3;

    /* Block Flux_select                                                                                              */
    x2cModel.blocks.sstartup.bFlux_select.In1 =
        &x2cModel.blocks.sstartup.bRateLimiter.Out;
    x2cModel.blocks.sstartup.bFlux_select.Switch =
        &x2cModel.blocks.sstartup.bSequencer.Out2;
    x2cModel.blocks.sstartup.bFlux_select.In3 =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter.Out;

    /* Block Flux_select1                                                                                             */
    x2cModel.blocks.sstartup.bFlux_select1.In1 =
        &x2cModel.blocks.sstartup.bFlux_select.Out;
    x2cModel.blocks.sstartup.bFlux_select1.Switch =
        &x2cModel.blocks.sstartup.bSequencer.Out1;
    x2cModel.blocks.sstartup.bFlux_select1.In3 =
        &x2cModel.blocks.sstartup.bConstant6.Out;

    /* Block Ramp_Up_Current                                                                                          */

    /* Block Constant4                                                                                                */

    /* Block I_Init_Zero                                                                                              */

    /* Block I_Init_Zero1                                                                                             */

    /* Block Ramp_Up_PositionGenerator                                                                                */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.In =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.Init =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero1.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.Enable =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv.Out;

    /* Block RateLimiter                                                                                              */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter.In =
        &x2cModel.blocks.sstartup.bRamp_Up_Current.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter.Init =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero1.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter.Enable =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv1.Out;

    /* Block Saturation                                                                                               */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation.In =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.Out;

    /* Block Speed_Ramp_UP_I                                                                                          */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.In =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bConstant4.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.Init =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.Enable =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv.Out;

    /* Block TypeConv                                                                                                 */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv.In =
        &x2cModel.blocks.sstartup.bSequencer.Out1;

    /* Block TypeConv1                                                                                                */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv1.In =
        &x2cModel.inports.bS3;

    /* Block RateLimiter                                                                                              */
    x2cModel.blocks.sstartup.bRateLimiter.In =
        &x2cModel.blocks.sstartup.bConstant1.Out;
    x2cModel.blocks.sstartup.bRateLimiter.Init =
        &x2cModel.blocks.bDelay3.Out;
    x2cModel.blocks.sstartup.bRateLimiter.Enable =
        &x2cModel.blocks.sstartup.bTypeConv2.Out;

    /* Block RateLimiter1                                                                                             */
    x2cModel.blocks.sstartup.bRateLimiter1.In =
        &x2cModel.blocks.sstartup.bAutoSwitch.Out;
    x2cModel.blocks.sstartup.bRateLimiter1.Init =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.Out;
    x2cModel.blocks.sstartup.bRateLimiter1.Enable =
        &x2cModel.blocks.sstartup.bTypeConv1.Out;

    /* Block RateLimiter2                                                                                             */
    x2cModel.blocks.sstartup.bRateLimiter2.In =
        &x2cModel.blocks.sspeedPI.bRateLimiter.Out;
    x2cModel.blocks.sstartup.bRateLimiter2.Init =
        &x2cModel.blocks.sstartup.bConstant5.Out;
    x2cModel.blocks.sstartup.bRateLimiter2.Enable =
        &x2cModel.blocks.sstartup.bTypeConv.Out;

    /* Block Sequencer                                                                                                */
    x2cModel.blocks.sstartup.bSequencer.Start =
        &x2cModel.inports.bS3;

    /* Block TypeConv                                                                                                 */
    x2cModel.blocks.sstartup.bTypeConv.In =
        &x2cModel.blocks.sstartup.bSequencer.Out2;

    /* Block TypeConv1                                                                                                */
    x2cModel.blocks.sstartup.bTypeConv1.In =
        &x2cModel.blocks.sstartup.bSequencer.Out3;

    /* Block TypeConv2                                                                                                */
    x2cModel.blocks.sstartup.bTypeConv2.In =
        &x2cModel.blocks.sstartup.bSequencer.Out2;

    /******************************************************************************************************************/
    /**                                                 Link Outports                                                **/
    /******************************************************************************************************************/
    x2cModel.outports.sFOC_main.bEstimated_angle =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.buI.Out;
    x2cModel.outports.sFOC_main.bEstimated_speed =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain.Out;
    x2cModel.outports.bHOME_INIT =
        &x2cModel.blocks.bGain1.Out;
    x2cModel.outports.bLED_D17 =
        &x2cModel.blocks.bConstant3.Out;
    x2cModel.outports.bLED_D2 =
        &x2cModel.inports.bS2;
    x2cModel.outports.bPWM1 =
        &x2cModel.blocks.sFOC_main.bManualSwitch2.Out;
    x2cModel.outports.bPWM2 =
        &x2cModel.blocks.sFOC_main.bManualSwitch3.Out;
    x2cModel.outports.bPWM3 =
        &x2cModel.blocks.sFOC_main.bManualSwitch4.Out;
    x2cModel.outports.sstartup.bId =
        &x2cModel.blocks.sstartup.bFlux_select1.Out;
    x2cModel.outports.sstartup.bIq =
        &x2cModel.blocks.sstartup.bAutoSwitch2.Out;
    x2cModel.outports.sstartup.bON_OFF =
        &x2cModel.inports.bS3;
    x2cModel.outports.sstartup.bpos =
        &x2cModel.blocks.sstartup.bAutoSwitch1.Out;

    /******************************************************************************************************************/
    /**                                           Run Block Init Functions                                           **/
    /******************************************************************************************************************/
    Constant_Bool_Init(&x2cModel.blocks.bConstant3);
    Delay_FiP16_Init(&x2cModel.blocks.bDelay1);
    Delay_FiP16_Init(&x2cModel.blocks.bDelay2);
    Delay_FiP16_Init(&x2cModel.blocks.bDelay3);
    Clark_Park_FiP16_Init(&x2cModel.blocks.sFOC_main.bClark_Park);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.bConstant);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.bConstant1);
    Gain_FiP16_Init(&x2cModel.blocks.sFOC_main.bGain1);
    Gain_FiP16_Init(&x2cModel.blocks.sFOC_main.bGain2);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bManualSwitch);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bManualSwitch1);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bManualSwitch2);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bManualSwitch3);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.bManualSwitch4);
    Not_Bool_Init(&x2cModel.blocks.sFOC_main.bNot);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.bOpenLoop_Vd);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.bOpenLoop_Vq);
    PI_FiP16_Init(&x2cModel.blocks.sFOC_main.bPI_flux);
    PI_FiP16_Init(&x2cModel.blocks.sFOC_main.bPI_torque);
    BEMF_calc_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bConstant1);
    Delay_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bDelay1);
    PT1_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter);
    PT1_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter);
    Park_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bPark);
    Add_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAdd);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch);
    Gain_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain);
    Sub_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bSub);
    uI_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.buI);
    Park_Clark_inv_FiP16_Init(&x2cModel.blocks.sFOC_main.bPark_Clark_inv);
    Saturation_FiP16_Init(&x2cModel.blocks.sFOC_main.bSaturation);
    Saturation_FiP16_Init(&x2cModel.blocks.sFOC_main.bSaturation1);
    Sin3Gen_FiP16_Init(&x2cModel.blocks.sFOC_main.bSin3Gen);
    Sub_FiP16_Init(&x2cModel.blocks.sFOC_main.bSub_flux);
    Sub_FiP16_Init(&x2cModel.blocks.sFOC_main.bSub_torque);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sFOC_main.bTypeConv2);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.binitForcedValue);
    Gain_FiP16_Init(&x2cModel.blocks.bGain);
    Gain_FiP16_Init(&x2cModel.blocks.bGain1);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.bManualSwitch);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.bManualSwitch1);
    Negation_FiP16_Init(&x2cModel.blocks.bNegation);
    PI_FiP16_Init(&x2cModel.blocks.sspeedPI.bPI_speed);
    RateLimiter_FiP16_Init(&x2cModel.blocks.sspeedPI.bRateLimiter);
    Constant_Bool_Init(&x2cModel.blocks.sspeedPI.bSpeed_Init);
    Constant_FiP16_Init(&x2cModel.blocks.sspeedPI.bSpeed_Init1);
    Sub_FiP16_Init(&x2cModel.blocks.sspeedPI.bSpeed_error);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bAutoSwitch);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bAutoSwitch1);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bAutoSwitch2);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.bConstant1);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.bConstant5);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.bConstant6);
    Delay_FiP16_Init(&x2cModel.blocks.sstartup.sDelay50.bDelay);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bFlux_select);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bFlux_select1);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.bRamp_Up_Current);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bConstant4);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero1);
    uI_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator);
    RateLimiter_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter);
    Saturation_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation);
    I_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv1);
    RateLimiter_FiP16_Init(&x2cModel.blocks.sstartup.bRateLimiter);
    RateLimiter_FiP16_Init(&x2cModel.blocks.sstartup.bRateLimiter1);
    RateLimiter_FiP16_Init(&x2cModel.blocks.sstartup.bRateLimiter2);
    Sequencer_FiP16_Init(&x2cModel.blocks.sstartup.bSequencer);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sstartup.bTypeConv);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sstartup.bTypeConv1);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sstartup.bTypeConv2);
    Scope_Main_Init(&x2cScope);

    /* Initialize Mask parameter structures                                                                           */

    /* Initialize Implementation parameters of Conversion-on-Target blocks                                            */

    /* Initialize TableStruct tables                                                                                  */
    TableStruct->TFncTable = blockFunctionTable;
    TableStruct->TParamTable = parameterIdTable;
    TableStruct->inportParamTable = inportParamIdTable;
    TableStruct->outportParamTable = outportParamIdTable;
    TableStruct->maskParameterTable = maskParamIdTable;
}

/**********************************************************************************************************************/
/**                                            Run Block Update Functions                                            **/
/**********************************************************************************************************************/
static uint16 cnt_10 = X2C_UPDATE_10_DIVIDER - 1;
static uint16 cnt_50 = X2C_UPDATE_50_DIVIDER - 1;
void X2C_Update(void)
{
    X2C_Update_1();
    if (cnt_10 == 0)
    {
        cnt_10 = X2C_UPDATE_10_DIVIDER;
        X2C_Update_10();
    }
    if (cnt_50 == 0)
    {
        cnt_50 = X2C_UPDATE_50_DIVIDER;
        X2C_Update_50();
    }

    cnt_10--;
    cnt_50--;
}

/* X2C_Update for blocks with 1*Ts                                                                                    */
void X2C_Update_1(void)
{
    Delay_FiP16_Update(&x2cModel.blocks.bDelay1);
    Delay_FiP16_Update(&x2cModel.blocks.bDelay2);
    Delay_FiP16_Update(&x2cModel.blocks.bDelay3);
    Delay_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.bDelay1);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv1);
    Sequencer_FiP16_Update(&x2cModel.blocks.sstartup.bSequencer);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sFOC_main.bTypeConv2);
    RateLimiter_FiP16_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bRateLimiter);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sstartup.bTypeConv);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sstartup.bTypeConv1);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sstartup.bTypeConv2);
    Not_Bool_Update(&x2cModel.blocks.sFOC_main.bNot);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.bManualSwitch);
    I_FiP16_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I);
    RateLimiter_FiP16_Update(&x2cModel.blocks.sstartup.bRateLimiter);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bFlux_select);
    Saturation_FiP16_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bFlux_select1);
    uI_FiP16_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bAutoSwitch);
    RateLimiter_FiP16_Update(&x2cModel.blocks.sstartup.bRateLimiter1);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bAutoSwitch1);
    Clark_Park_FiP16_Update(&x2cModel.blocks.sFOC_main.bClark_Park);
    Sin3Gen_FiP16_Update(&x2cModel.blocks.sFOC_main.bSin3Gen);
    Sub_FiP16_Update(&x2cModel.blocks.sFOC_main.bSub_flux);
    Negation_FiP16_Update(&x2cModel.blocks.bNegation);
    PI_FiP16_Update(&x2cModel.blocks.sFOC_main.bPI_flux);
    Gain_FiP16_Update(&x2cModel.blocks.bGain1);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch);
    Saturation_FiP16_Update(&x2cModel.blocks.sFOC_main.bSaturation1);
    RateLimiter_FiP16_Update(&x2cModel.blocks.sstartup.bRateLimiter2);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bAutoSwitch2);
    Sub_FiP16_Update(&x2cModel.blocks.sFOC_main.bSub_torque);
    PI_FiP16_Update(&x2cModel.blocks.sFOC_main.bPI_torque);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch1);
    Saturation_FiP16_Update(&x2cModel.blocks.sFOC_main.bSaturation);
    Park_Clark_inv_FiP16_Update(&x2cModel.blocks.sFOC_main.bPark_Clark_inv);
    Gain_FiP16_Update(&x2cModel.blocks.sFOC_main.bGain1);
    Gain_FiP16_Update(&x2cModel.blocks.sFOC_main.bGain2);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch2);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch3);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch4);
    BEMF_calc_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_calc);
    Park_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.bPark);
    PT1_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter);
    PT1_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter);
    Add_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAdd);
    Sub_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bSub);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch);
    Gain_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain);
    uI_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.buI);
    Scope_Main_Update(&x2cScope);
}

/* X2C_Update for blocks with 10*Ts                                                                                   */
void X2C_Update_10(void)
{
    Gain_FiP16_Update(&x2cModel.blocks.bGain);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.bManualSwitch1);
    Sub_FiP16_Update(&x2cModel.blocks.sspeedPI.bSpeed_error);
    PI_FiP16_Update(&x2cModel.blocks.sspeedPI.bPI_speed);
    RateLimiter_FiP16_Update(&x2cModel.blocks.sspeedPI.bRateLimiter);
}

/* X2C_Update for blocks with 50*Ts                                                                                   */
void X2C_Update_50(void)
{
    Delay_FiP16_Update(&x2cModel.blocks.sstartup.sDelay50.bDelay);
}

