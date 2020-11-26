/* This file is part of X2C. http://x2c.lcm.at/                                                                       */

/* Model: mc_foc_sl_fip_dspic33ck_mclv2                                                                               */
/* Date:  2020-11-26 13:55                                                                                            */

/* X2C-Version: 6.3.2018                                                                                              */
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
#define END_MASKPARAMID_TABLE { 0, (void*)0, (void*)0, (tSaveMaskParameter)0, (tLoadMaskParameter)0, (tConvertMaskParameter)0, (tBackupMaskParameter)0, (tRestoreMaskParameter)0 }
const tMaskParameterEntry maskParamIdTable[] = {
    END_MASKPARAMID_TABLE
};

/* Mask Parameter data table                                                                                          */
const tMaskParamDataRecord maskParamDataTable[] = {
    { 0, 0, (void*)0, 0, 0 }
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

    /* Block: Delay1                                                                                                  */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.bDelay1.In_old = 0;

    /* Block: Delay2                                                                                                  */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.bDelay2.In_old = 0;

    /* Block: FOC_main/Clarke_Park_MCHP                                                                               */

    /* Block: FOC_main/Constant                                                                                       */
    /* Value = 0.2                                                                                                    */
    x2cModel.blocks.sFOC_main.bConstant.K = 6554;

    /* Block: FOC_main/Constant1                                                                                      */
    /* Value = 1.0                                                                                                    */
    x2cModel.blocks.sFOC_main.bConstant1.K = 32767;

    /* Block: FOC_main/Gain                                                                                           */
    /* Gain = 0.5                                                                                                     */
    x2cModel.blocks.sFOC_main.bGain.V = 16384;
    x2cModel.blocks.sFOC_main.bGain.sfr = 15;

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

    /* Block: FOC_main/PLLEstimator/BEMF_MCHP                                                                         */
    /* Ls = 0.34                                                                                                      */
    /* Rs = 0.3                                                                                                       */
    /* U0 = 24.0                                                                                                      */
    /* I0 = 3.95                                                                                                      */
    /* ts_fact = 1.0                                                                                                  */
    /* CurrentSampleFactor = 1.0                                                                                      */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.Ls = 18336;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.Rs = 1618;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.sfrLs = 15;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.sfrRs = 15;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.Ib_old = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.Ia_old = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.CurrentSampleFactor = 1;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.V_Ls_alpha = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.V_Ls_beta = 0;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.FactCounter = 0;

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

    /* Block: FOC_main/PLLEstimator/Park_MCHP                                                                         */

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

    /* Block: FOC_main/Park_Clarke_inv_SVM_MCHP                                                                       */

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

    /* Block: Gain                                                                                                    */
    /* Gain = 0.8                                                                                                     */
    x2cModel.blocks.bGain.V = 26214;
    x2cModel.blocks.bGain.sfr = 15;

    /* Block: ManualSwitch                                                                                            */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.bManualSwitch.Toggle = 1;

    /* Block: ManualSwitch1                                                                                           */
    /* Toggle = 1.0                                                                                                   */
    x2cModel.blocks.bManualSwitch1.Toggle = 1;

    /* Block: Not                                                                                                     */

    /* Block: speedPI/Constant                                                                                        */
    /* Value = 0.05                                                                                                   */
    x2cModel.blocks.sspeedPI.bConstant.K = 1638;

    /* Block: speedPI/Constant1                                                                                       */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sspeedPI.bConstant1.K = 0;

    /* Block: speedPI/Delay                                                                                           */
    /* ts_fact = 10.0                                                                                                 */
    x2cModel.blocks.sspeedPI.bDelay.In_old = 0;

    /* Block: speedPI/ManualSwitch                                                                                    */
    /* Toggle = 0.0                                                                                                   */
    x2cModel.blocks.sspeedPI.bManualSwitch.Toggle = 0;

    /* Block: speedPI/PI_speed                                                                                        */
    /* Kp = 1.0                                                                                                       */
    /* Ki = 0.5                                                                                                       */
    /* ts_fact = 10.0                                                                                                 */
    x2cModel.blocks.sspeedPI.bPI_speed.b0 = 16;
    x2cModel.blocks.sspeedPI.bPI_speed.b1 = 16384;
    x2cModel.blocks.sspeedPI.bPI_speed.sfrb0 = 15;
    x2cModel.blocks.sspeedPI.bPI_speed.sfrb1 = 14;
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

    /* Block: speedPI/Speed_error                                                                                     */

    /* Block: speedPI/perturbation/Add                                                                                */

    /* Block: speedPI/perturbation/AutoSwitch                                                                         */
    /* Thresh_up = 0.0                                                                                                */
    /* Thresh_down = 0.0                                                                                              */
    x2cModel.blocks.sspeedPI.sperturbation.bAutoSwitch.Thresh_up = 0;
    x2cModel.blocks.sspeedPI.sperturbation.bAutoSwitch.Thresh_down = 0;
    x2cModel.blocks.sspeedPI.sperturbation.bAutoSwitch.Status = &RamTable_int16[1];

    /* Block: speedPI/perturbation/Constant                                                                           */
    /* Value = 1.0                                                                                                    */
    x2cModel.blocks.sspeedPI.sperturbation.bConstant.K = 32767;

    /* Block: speedPI/perturbation/Constant1                                                                          */
    /* Value = 0.01                                                                                                   */
    x2cModel.blocks.sspeedPI.sperturbation.bConstant1.K = 328;

    /* Block: speedPI/perturbation/Constant2                                                                          */
    /* Value = 1.0                                                                                                    */
    x2cModel.blocks.sspeedPI.sperturbation.bConstant2.K = 1;

    /* Block: speedPI/perturbation/Constant3                                                                          */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sspeedPI.sperturbation.bConstant3.K = 0;

    /* Block: speedPI/perturbation/Gain                                                                               */
    /* Gain = -1.0                                                                                                    */
    x2cModel.blocks.sspeedPI.sperturbation.bGain.V = -16384;
    x2cModel.blocks.sspeedPI.sperturbation.bGain.sfr = 14;

    /* Block: speedPI/perturbation/RateLimiter                                                                        */
    /* Tr = 0.0                                                                                                       */
    /* Tf = 0.0                                                                                                       */
    /* ts_fact = 10.0                                                                                                 */
    x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter.RateUp = 2147483647;
    x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter.RateDown = 2147483647;
    x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter.out_old = 0;
    x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter.enable_old = 0;

    /* Block: speedPI/perturbation/SinGen                                                                             */
    /* fmax = 100.0                                                                                                   */
    /* Offset = 0.0                                                                                                   */
    /* Phase = 0.0                                                                                                    */
    /* ts_fact = 10.0                                                                                                 */
    x2cModel.blocks.sspeedPI.sperturbation.bSinGen.delta_phi = 6554;
    x2cModel.blocks.sspeedPI.sperturbation.bSinGen.phase = 0;
    x2cModel.blocks.sspeedPI.sperturbation.bSinGen.offset = 0;
    x2cModel.blocks.sspeedPI.sperturbation.bSinGen.phi = 0;

    /* Block: startup/Constant                                                                                        */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.bConstant.K = 0;

    /* Block: startup/Constant1                                                                                       */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.bConstant1.K = 0;

    /* Block: startup/Constant2                                                                                       */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.bConstant2.K = 0;

    /* Block: startup/Constant3                                                                                       */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.bConstant3.K = 0;

    /* Block: startup/Constant5                                                                                       */
    /* Value = 1.0                                                                                                    */
    x2cModel.blocks.sstartup.bConstant5.K = 1;

    /* Block: startup/Delay                                                                                           */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.bDelay.In_old = 0;

    /* Block: startup/Flux_select                                                                                     */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sstartup.bFlux_select.Thresh_up = 16384;
    x2cModel.blocks.sstartup.bFlux_select.Thresh_down = 16384;
    x2cModel.blocks.sstartup.bFlux_select.Status = &RamTable_int16[2];

    /* Block: startup/Flux_select1                                                                                    */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sstartup.bFlux_select1.Thresh_up = 16384;
    x2cModel.blocks.sstartup.bFlux_select1.Thresh_down = 16384;
    x2cModel.blocks.sstartup.bFlux_select1.Status = &RamTable_int16[3];

    /* Block: startup/IdRateLimiter                                                                                   */
    /* Tr = 0.5                                                                                                       */
    /* Tf = 3.0                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.bIdRateLimiter.RateUp = 429497;
    x2cModel.blocks.sstartup.bIdRateLimiter.RateDown = 71583;
    x2cModel.blocks.sstartup.bIdRateLimiter.out_old = 0;
    x2cModel.blocks.sstartup.bIdRateLimiter.enable_old = 0;

    /* Block: startup/Iq_select                                                                                       */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sstartup.bIq_select.Thresh_up = 16384;
    x2cModel.blocks.sstartup.bIq_select.Thresh_down = 16384;
    x2cModel.blocks.sstartup.bIq_select.Status = &RamTable_int16[4];

    /* Block: startup/ManualSwitch                                                                                    */
    /* Toggle = 0.0                                                                                                   */
    x2cModel.blocks.sstartup.bManualSwitch.Toggle = 0;

    /* Block: startup/ManualSwitch1                                                                                   */
    /* Toggle = 0.0                                                                                                   */
    x2cModel.blocks.sstartup.bManualSwitch1.Toggle = 0;

    /* Block: startup/PI                                                                                              */
    /* Kp = 0.0                                                                                                       */
    /* Ki = 0.5                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.bPI.b0 = 2;
    x2cModel.blocks.sstartup.bPI.b1 = 0;
    x2cModel.blocks.sstartup.bPI.sfrb0 = 15;
    x2cModel.blocks.sstartup.bPI.sfrb1 = 15;
    x2cModel.blocks.sstartup.bPI.i_old = 0;
    x2cModel.blocks.sstartup.bPI.enable_old = 0;

    /* Block: startup/PosError                                                                                        */

    /* Block: startup/PosSwitch                                                                                       */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    x2cModel.blocks.sstartup.bPosSwitch.Thresh_up = 16384;
    x2cModel.blocks.sstartup.bPosSwitch.Thresh_down = 16384;
    x2cModel.blocks.sstartup.bPosSwitch.Status = &RamTable_int16[5];

    /* Block: startup/Ramp_Up_Current                                                                                 */
    /* Value = 0.3                                                                                                    */
    x2cModel.blocks.sstartup.bRamp_Up_Current.K = 9830;

    /* Block: startup/Ramp_Up_SB/Constant4                                                                            */
    /* Value = 1.0                                                                                                    */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bConstant4.K = 32767;

    /* Block: startup/Ramp_Up_SB/I_Init_Zero                                                                          */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero.K = 0;

    /* Block: startup/Ramp_Up_SB/I_Init_Zero1                                                                         */
    /* Value = 0.0                                                                                                    */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero1.K = 0;

    /* Block: startup/Ramp_Up_SB/Mult                                                                                 */

    /* Block: startup/Ramp_Up_SB/Ramp_Up_PositionGenerator                                                            */
    /* Ki = 400.0                                                                                                     */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.b0 = 1311;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.sfr = 15;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.i_old = 0;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.enable_old = 0;

    /* Block: startup/Ramp_Up_SB/Saturation                                                                           */
    /* max = 0.5                                                                                                      */
    /* min = -0.5                                                                                                     */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation.max = 16384;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation.min = -16384;

    /* Block: startup/Ramp_Up_SB/Sign                                                                                 */

    /* Block: startup/Ramp_Up_SB/Speed_Ramp_UP_I                                                                      */
    /* Ki = 1.0                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.b0 = 3;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.sfr = 15;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.i_old = 0;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.enable_old = 0;

    /* Block: startup/Ramp_Up_SB/TypeConv                                                                             */

    /* Block: startup/Sequencer                                                                                       */
    /* Delay1 = 0.1                                                                                                   */
    /* Delay2 = 0.5                                                                                                   */
    /* Delay3 = 1.3                                                                                                   */
    /* Delay4 = 1.6                                                                                                   */
    /* ts_fact = 1.0                                                                                                  */
    x2cModel.blocks.sstartup.bSequencer.delay1 = 1000;
    x2cModel.blocks.sstartup.bSequencer.delay2 = 5000;
    x2cModel.blocks.sstartup.bSequencer.delay3 = 13000;
    x2cModel.blocks.sstartup.bSequencer.delay4 = 16000;
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

    /* Block Delay1                                                                                                   */
    x2cModel.blocks.bDelay1.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain.Out;

    /* Block Delay2                                                                                                   */
    x2cModel.blocks.bDelay2.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.buI.Out;

    /* Block Clarke_Park_MCHP                                                                                         */
    x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.a =
        &x2cModel.inports.bI_a;
    x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.b =
        &x2cModel.inports.bI_b;
    x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.theta =
        &x2cModel.blocks.sstartup.bPosSwitch.Out;

    /* Block Constant                                                                                                 */

    /* Block Constant1                                                                                                */

    /* Block Gain                                                                                                     */
    x2cModel.blocks.sFOC_main.bGain.In =
        &x2cModel.blocks.sstartup.bIdRateLimiter.Out;

    /* Block Gain1                                                                                                    */
    x2cModel.blocks.sFOC_main.bGain1.In =
        &x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.Valpha;

    /* Block Gain2                                                                                                    */
    x2cModel.blocks.sFOC_main.bGain2.In =
        &x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.Vbeta;

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
        &x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.A;

    /* Block ManualSwitch3                                                                                            */
    x2cModel.blocks.sFOC_main.bManualSwitch3.In1 =
        &x2cModel.blocks.sFOC_main.bSin3Gen.v;
    x2cModel.blocks.sFOC_main.bManualSwitch3.In2 =
        &x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.B;

    /* Block ManualSwitch4                                                                                            */
    x2cModel.blocks.sFOC_main.bManualSwitch4.In1 =
        &x2cModel.blocks.sFOC_main.bSin3Gen.w;
    x2cModel.blocks.sFOC_main.bManualSwitch4.In2 =
        &x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.C;

    /* Block Not                                                                                                      */
    x2cModel.blocks.sFOC_main.bNot.In =
        &x2cModel.blocks.sstartup.bTypeConv.Out;

    /* Block OpenLoop_Vd                                                                                              */

    /* Block OpenLoop_Vq                                                                                              */

    /* Block PI_flux                                                                                                  */
    x2cModel.blocks.sFOC_main.bPI_flux.In =
        &x2cModel.blocks.sFOC_main.bSub_flux.Out;
    x2cModel.blocks.sFOC_main.bPI_flux.Init =
        &x2cModel.blocks.sstartup.bIdRateLimiter.Out;
    x2cModel.blocks.sFOC_main.bPI_flux.Enable =
        &x2cModel.blocks.sstartup.bTypeConv.Out;

    /* Block PI_torque                                                                                                */
    x2cModel.blocks.sFOC_main.bPI_torque.In =
        &x2cModel.blocks.sFOC_main.bSub_torque.Out;
    x2cModel.blocks.sFOC_main.bPI_torque.Init =
        &x2cModel.blocks.sstartup.bIq_select.Out;
    x2cModel.blocks.sFOC_main.bPI_torque.Enable =
        &x2cModel.blocks.sstartup.bTypeConv.Out;

    /* Block BEMF_MCHP                                                                                                */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.Ialpha =
        &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.alpha;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.Ibeta =
        &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.beta;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.Valpha =
        &x2cModel.blocks.sFOC_main.bGain1.Out;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.Vbeta =
        &x2cModel.blocks.sFOC_main.bGain2.Out;

    /* Block Delay1                                                                                                   */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bDelay1.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.buI.Out;

    /* Block Edfilter                                                                                                 */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bPark_MCHP.d;

    /* Block Eqfilter                                                                                                 */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter.In =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bPark_MCHP.q;

    /* Block Park_MCHP                                                                                                */
    x2cModel.blocks.sFOC_main.sPLLEstimator.bPark_MCHP.alpha =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.BEMFalpha;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bPark_MCHP.beta =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP.BEMFbeta;
    x2cModel.blocks.sFOC_main.sPLLEstimator.bPark_MCHP.theta =
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
        &x2cModel.blocks.sstartup.bPosSwitch.Out;
    x2cModel.blocks.sFOC_main.sPLLEstimator.buI.Enable =
        &x2cModel.blocks.sstartup.bTypeConv2.Out;

    /* Block Park_Clarke_inv_SVM_MCHP                                                                                 */
    x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.d =
        &x2cModel.blocks.sFOC_main.bSaturation1.Out;
    x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.q =
        &x2cModel.blocks.sFOC_main.bSaturation.Out;
    x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.theta =
        &x2cModel.blocks.sstartup.bPosSwitch.Out;
    x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.forcedMode =
        &x2cModel.blocks.sFOC_main.bNot.Out;
    x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP.forcedValue =
        &x2cModel.blocks.sFOC_main.bGain.Out;

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
        &x2cModel.blocks.sstartup.bIdRateLimiter.Out;
    x2cModel.blocks.sFOC_main.bSub_flux.Minus =
        &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.d;

    /* Block Sub_torque                                                                                               */
    x2cModel.blocks.sFOC_main.bSub_torque.Plus =
        &x2cModel.blocks.sstartup.bIq_select.Out;
    x2cModel.blocks.sFOC_main.bSub_torque.Minus =
        &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP.q;

    /* Block Gain                                                                                                     */
    x2cModel.blocks.bGain.In =
        &x2cModel.inports.bV_POT;

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

    /* Block Not                                                                                                      */
    x2cModel.blocks.bNot.In =
        &x2cModel.blocks.sstartup.bTypeConv.Out;

    /* Block Constant                                                                                                 */

    /* Block Constant1                                                                                                */

    /* Block Delay                                                                                                    */
    x2cModel.blocks.sspeedPI.bDelay.In =
        &x2cModel.blocks.sstartup.bIq_select.Out;

    /* Block ManualSwitch                                                                                             */
    x2cModel.blocks.sspeedPI.bManualSwitch.In1 =
        &x2cModel.blocks.sspeedPI.bPI_speed.Out;
    x2cModel.blocks.sspeedPI.bManualSwitch.In2 =
        &x2cModel.blocks.sspeedPI.bConstant.Out;

    /* Block PI_speed                                                                                                 */
    x2cModel.blocks.sspeedPI.bPI_speed.In =
        &x2cModel.blocks.sspeedPI.bSpeed_error.Out;
    x2cModel.blocks.sspeedPI.bPI_speed.Init =
        &x2cModel.blocks.sspeedPI.bDelay.Out;
    x2cModel.blocks.sspeedPI.bPI_speed.Enable =
        &x2cModel.blocks.sstartup.bTypeConv1.Out;

    /* Block RateLimiter                                                                                              */
    x2cModel.blocks.sspeedPI.bRateLimiter.In =
        &x2cModel.blocks.bGain.Out;
    x2cModel.blocks.sspeedPI.bRateLimiter.Init =
        &x2cModel.blocks.bManualSwitch1.Out;
    x2cModel.blocks.sspeedPI.bRateLimiter.Enable =
        &x2cModel.blocks.sstartup.bTypeConv1.Out;

    /* Block Speed_error                                                                                              */
    x2cModel.blocks.sspeedPI.bSpeed_error.Plus =
        &x2cModel.blocks.sspeedPI.bRateLimiter.Out;
    x2cModel.blocks.sspeedPI.bSpeed_error.Minus =
        &x2cModel.blocks.bManualSwitch1.Out;

    /* Block Add                                                                                                      */
    x2cModel.blocks.sspeedPI.sperturbation.bAdd.In1 =
        &x2cModel.blocks.sspeedPI.bManualSwitch.Out;
    x2cModel.blocks.sspeedPI.sperturbation.bAdd.In2 =
        &x2cModel.blocks.sspeedPI.sperturbation.bAutoSwitch.Out;

    /* Block AutoSwitch                                                                                               */
    x2cModel.blocks.sspeedPI.sperturbation.bAutoSwitch.In1 =
        &x2cModel.blocks.sspeedPI.bConstant1.Out;
    x2cModel.blocks.sspeedPI.sperturbation.bAutoSwitch.Switch =
        &x2cModel.blocks.sspeedPI.sperturbation.bSinGen.u;
    x2cModel.blocks.sspeedPI.sperturbation.bAutoSwitch.In3 =
        &x2cModel.blocks.sspeedPI.sperturbation.bGain.Out;

    /* Block Constant                                                                                                 */

    /* Block Constant1                                                                                                */

    /* Block Constant2                                                                                                */

    /* Block Constant3                                                                                                */

    /* Block Gain                                                                                                     */
    x2cModel.blocks.sspeedPI.sperturbation.bGain.In =
        &x2cModel.blocks.sspeedPI.bConstant1.Out;

    /* Block RateLimiter                                                                                              */
    x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter.In =
        &x2cModel.blocks.sspeedPI.sperturbation.bAdd.Out;
    x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter.Init =
        &x2cModel.blocks.sspeedPI.sperturbation.bConstant3.Out;
    x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter.Enable =
        &x2cModel.blocks.sspeedPI.sperturbation.bConstant2.Out;

    /* Block SinGen                                                                                                   */
    x2cModel.blocks.sspeedPI.sperturbation.bSinGen.A =
        &x2cModel.blocks.sspeedPI.sperturbation.bConstant.Out;
    x2cModel.blocks.sspeedPI.sperturbation.bSinGen.f =
        &x2cModel.blocks.sspeedPI.sperturbation.bConstant1.Out;

    /* Block Constant                                                                                                 */

    /* Block Constant1                                                                                                */

    /* Block Constant2                                                                                                */

    /* Block Constant3                                                                                                */

    /* Block Constant5                                                                                                */

    /* Block Delay                                                                                                    */
    x2cModel.blocks.sstartup.bDelay.In =
        &x2cModel.blocks.sstartup.bManualSwitch.Out;

    /* Block Flux_select                                                                                              */
    x2cModel.blocks.sstartup.bFlux_select.In1 =
        &x2cModel.blocks.sstartup.bRamp_Up_Current.Out;
    x2cModel.blocks.sstartup.bFlux_select.Switch =
        &x2cModel.blocks.sstartup.bSequencer.Out1;
    x2cModel.blocks.sstartup.bFlux_select.In3 =
        &x2cModel.blocks.sstartup.bConstant3.Out;

    /* Block Flux_select1                                                                                             */
    x2cModel.blocks.sstartup.bFlux_select1.In1 =
        &x2cModel.blocks.sstartup.bConstant3.Out;
    x2cModel.blocks.sstartup.bFlux_select1.Switch =
        &x2cModel.blocks.sstartup.bManualSwitch.Out;
    x2cModel.blocks.sstartup.bFlux_select1.In3 =
        &x2cModel.blocks.sstartup.bFlux_select.Out;

    /* Block IdRateLimiter                                                                                            */
    x2cModel.blocks.sstartup.bIdRateLimiter.In =
        &x2cModel.blocks.sstartup.bFlux_select1.Out;
    x2cModel.blocks.sstartup.bIdRateLimiter.Init =
        &x2cModel.blocks.sstartup.bConstant3.Out;
    x2cModel.blocks.sstartup.bIdRateLimiter.Enable =
        &x2cModel.blocks.sstartup.bConstant5.Out;

    /* Block Iq_select                                                                                                */
    x2cModel.blocks.sstartup.bIq_select.In1 =
        &x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter.Out;
    x2cModel.blocks.sstartup.bIq_select.Switch =
        &x2cModel.blocks.sstartup.bDelay.Out;
    x2cModel.blocks.sstartup.bIq_select.In3 =
        &x2cModel.blocks.sstartup.bPI.Out;

    /* Block ManualSwitch                                                                                             */
    x2cModel.blocks.sstartup.bManualSwitch.In1 =
        &x2cModel.blocks.sstartup.bSequencer.Out4;
    x2cModel.blocks.sstartup.bManualSwitch.In2 =
        &x2cModel.blocks.sstartup.bConstant.Out;

    /* Block ManualSwitch1                                                                                            */
    x2cModel.blocks.sstartup.bManualSwitch1.In1 =
        &x2cModel.blocks.sstartup.bSequencer.Out3;
    x2cModel.blocks.sstartup.bManualSwitch1.In2 =
        &x2cModel.blocks.sstartup.bConstant2.Out;

    /* Block PI                                                                                                       */
    x2cModel.blocks.sstartup.bPI.In =
        &x2cModel.blocks.sstartup.bPosError.Out;
    x2cModel.blocks.sstartup.bPI.Init =
        &x2cModel.blocks.sstartup.bConstant1.Out;
    x2cModel.blocks.sstartup.bPI.Enable =
        &x2cModel.blocks.sstartup.bTypeConv2.Out;

    /* Block PosError                                                                                                 */
    x2cModel.blocks.sstartup.bPosError.Plus =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.Out;
    x2cModel.blocks.sstartup.bPosError.Minus =
        &x2cModel.blocks.bManualSwitch.Out;

    /* Block PosSwitch                                                                                                */
    x2cModel.blocks.sstartup.bPosSwitch.In1 =
        &x2cModel.blocks.bManualSwitch.Out;
    x2cModel.blocks.sstartup.bPosSwitch.Switch =
        &x2cModel.blocks.sstartup.bDelay.Out;
    x2cModel.blocks.sstartup.bPosSwitch.In3 =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.Out;

    /* Block Ramp_Up_Current                                                                                          */

    /* Block Constant4                                                                                                */

    /* Block I_Init_Zero                                                                                              */

    /* Block I_Init_Zero1                                                                                             */

    /* Block Mult                                                                                                     */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bMult.In1 =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bConstant4.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bMult.In2 =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bSign.Out;

    /* Block Ramp_Up_PositionGenerator                                                                                */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.In =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.Init =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero1.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator.Enable =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv.Out;

    /* Block Saturation                                                                                               */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation.In =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.Out;

    /* Block Sign                                                                                                     */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSign.In =
        &x2cModel.blocks.bGain.Out;

    /* Block Speed_Ramp_UP_I                                                                                          */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.In =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bMult.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.Init =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero.Out;
    x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I.Enable =
        &x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv.Out;

    /* Block TypeConv                                                                                                 */
    x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv.In =
        &x2cModel.blocks.sstartup.bSequencer.Out2;

    /* Block Sequencer                                                                                                */
    x2cModel.blocks.sstartup.bSequencer.Start =
        &x2cModel.inports.bS3;

    /* Block TypeConv                                                                                                 */
    x2cModel.blocks.sstartup.bTypeConv.In =
        &x2cModel.blocks.sstartup.bSequencer.Out2;

    /* Block TypeConv1                                                                                                */
    x2cModel.blocks.sstartup.bTypeConv1.In =
        &x2cModel.blocks.sstartup.bManualSwitch.Out;

    /* Block TypeConv2                                                                                                */
    x2cModel.blocks.sstartup.bTypeConv2.In =
        &x2cModel.blocks.sstartup.bManualSwitch1.Out;

    /******************************************************************************************************************/
    /**                                                 Link Outports                                                **/
    /******************************************************************************************************************/
    x2cModel.outports.sFOC_main.bEstimated_angle =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.buI.Out;
    x2cModel.outports.sFOC_main.bEstimated_speed =
        &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain.Out;
    x2cModel.outports.bHOME_INIT =
        &x2cModel.blocks.bNot.Out;
    x2cModel.outports.bLED_D17 =
        &x2cModel.inports.bS2;
    x2cModel.outports.bLED_D2 =
        &x2cModel.inports.bS3;
    x2cModel.outports.bPWM1 =
        &x2cModel.blocks.sFOC_main.bManualSwitch2.Out;
    x2cModel.outports.bPWM2 =
        &x2cModel.blocks.sFOC_main.bManualSwitch3.Out;
    x2cModel.outports.bPWM3 =
        &x2cModel.blocks.sFOC_main.bManualSwitch4.Out;

    /******************************************************************************************************************/
    /**                                           Run Block Init Functions                                           **/
    /******************************************************************************************************************/
    Delay_FiP16_Init(&x2cModel.blocks.bDelay1);
    Delay_FiP16_Init(&x2cModel.blocks.bDelay2);
    Clarke_Park_MCHP_FiP16_Init(&x2cModel.blocks.sFOC_main.bClarke_Park_MCHP);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.bConstant);
    Constant_FiP16_Init(&x2cModel.blocks.sFOC_main.bConstant1);
    Gain_FiP16_Init(&x2cModel.blocks.sFOC_main.bGain);
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
    BEMF_MCHP_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP);
    Delay_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bDelay1);
    PT1_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter);
    PT1_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter);
    Park_MCHP_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.bPark_MCHP);
    Add_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAdd);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch);
    Gain_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain);
    Sub_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bSub);
    uI_FiP16_Init(&x2cModel.blocks.sFOC_main.sPLLEstimator.buI);
    Park_Clarke_inv_SVM_MCHP_FiP16_Init(&x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP);
    Saturation_FiP16_Init(&x2cModel.blocks.sFOC_main.bSaturation);
    Saturation_FiP16_Init(&x2cModel.blocks.sFOC_main.bSaturation1);
    Sin3Gen_FiP16_Init(&x2cModel.blocks.sFOC_main.bSin3Gen);
    Sub_FiP16_Init(&x2cModel.blocks.sFOC_main.bSub_flux);
    Sub_FiP16_Init(&x2cModel.blocks.sFOC_main.bSub_torque);
    Gain_FiP16_Init(&x2cModel.blocks.bGain);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.bManualSwitch);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.bManualSwitch1);
    Not_Bool_Init(&x2cModel.blocks.bNot);
    Constant_FiP16_Init(&x2cModel.blocks.sspeedPI.bConstant);
    Constant_FiP16_Init(&x2cModel.blocks.sspeedPI.bConstant1);
    Delay_FiP16_Init(&x2cModel.blocks.sspeedPI.bDelay);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sspeedPI.bManualSwitch);
    PI_FiP16_Init(&x2cModel.blocks.sspeedPI.bPI_speed);
    RateLimiter_FiP16_Init(&x2cModel.blocks.sspeedPI.bRateLimiter);
    Sub_FiP16_Init(&x2cModel.blocks.sspeedPI.bSpeed_error);
    Add_FiP16_Init(&x2cModel.blocks.sspeedPI.sperturbation.bAdd);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sspeedPI.sperturbation.bAutoSwitch);
    Constant_FiP16_Init(&x2cModel.blocks.sspeedPI.sperturbation.bConstant);
    Constant_FiP16_Init(&x2cModel.blocks.sspeedPI.sperturbation.bConstant1);
    Constant_Bool_Init(&x2cModel.blocks.sspeedPI.sperturbation.bConstant2);
    Constant_FiP16_Init(&x2cModel.blocks.sspeedPI.sperturbation.bConstant3);
    Gain_FiP16_Init(&x2cModel.blocks.sspeedPI.sperturbation.bGain);
    RateLimiter_FiP16_Init(&x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter);
    SinGen_FiP16_Init(&x2cModel.blocks.sspeedPI.sperturbation.bSinGen);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.bConstant);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.bConstant1);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.bConstant2);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.bConstant3);
    Constant_Bool_Init(&x2cModel.blocks.sstartup.bConstant5);
    Delay_FiP16_Init(&x2cModel.blocks.sstartup.bDelay);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bFlux_select);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bFlux_select1);
    RateLimiter_FiP16_Init(&x2cModel.blocks.sstartup.bIdRateLimiter);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bIq_select);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bManualSwitch);
    ManualSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bManualSwitch1);
    PI_FiP16_Init(&x2cModel.blocks.sstartup.bPI);
    uSub_FiP16_Init(&x2cModel.blocks.sstartup.bPosError);
    AutoSwitch_FiP16_Init(&x2cModel.blocks.sstartup.bPosSwitch);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.bRamp_Up_Current);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bConstant4);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero);
    Constant_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero1);
    Mult_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bMult);
    uI_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator);
    Saturation_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation);
    Sign_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSign);
    I_FiP16_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv);
    Sequencer_FiP16_Init(&x2cModel.blocks.sstartup.bSequencer);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sstartup.bTypeConv);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sstartup.bTypeConv1);
    TypeConv_FiP16_Bool_Init(&x2cModel.blocks.sstartup.bTypeConv2);
    Scope_Main_Init(&x2cScope);

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
void X2C_Update(void)
{
    X2C_Update_1();
    if (cnt_10 == 0)
    {
        cnt_10 = X2C_UPDATE_10_DIVIDER;
        X2C_Update_10();
    }

    cnt_10--;
}

/* X2C_Update for blocks with 1*Ts                                                                                    */
void X2C_Update_1(void)
{
    Delay_FiP16_Update(&x2cModel.blocks.bDelay1);
    Delay_FiP16_Update(&x2cModel.blocks.bDelay2);
    Delay_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.bDelay1);
    Delay_FiP16_Update(&x2cModel.blocks.sstartup.bDelay);
    Gain_FiP16_Update(&x2cModel.blocks.bGain);
    Sign_FiP16_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSign);
    Sequencer_FiP16_Update(&x2cModel.blocks.sstartup.bSequencer);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bFlux_select);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bManualSwitch);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bManualSwitch1);
    Mult_FiP16_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bMult);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sstartup.bTypeConv);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bFlux_select1);
    I_FiP16_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSpeed_Ramp_UP_I);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sstartup.bTypeConv2);
    RateLimiter_FiP16_Update(&x2cModel.blocks.sstartup.bIdRateLimiter);
    Saturation_FiP16_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation);
    Gain_FiP16_Update(&x2cModel.blocks.sFOC_main.bGain);
    Not_Bool_Update(&x2cModel.blocks.sFOC_main.bNot);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.bManualSwitch);
    uI_FiP16_Update(&x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator);
    uSub_FiP16_Update(&x2cModel.blocks.sstartup.bPosError);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bPosSwitch);
    Clarke_Park_MCHP_FiP16_Update(&x2cModel.blocks.sFOC_main.bClarke_Park_MCHP);
    PI_FiP16_Update(&x2cModel.blocks.sstartup.bPI);
    Sub_FiP16_Update(&x2cModel.blocks.sFOC_main.bSub_flux);
    PI_FiP16_Update(&x2cModel.blocks.sFOC_main.bPI_flux);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch);
    Saturation_FiP16_Update(&x2cModel.blocks.sFOC_main.bSaturation1);
    Sin3Gen_FiP16_Update(&x2cModel.blocks.sFOC_main.bSin3Gen);
    Not_Bool_Update(&x2cModel.blocks.bNot);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sstartup.bIq_select);
    Sub_FiP16_Update(&x2cModel.blocks.sFOC_main.bSub_torque);
    PI_FiP16_Update(&x2cModel.blocks.sFOC_main.bPI_torque);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch1);
    Saturation_FiP16_Update(&x2cModel.blocks.sFOC_main.bSaturation);
    Park_Clarke_inv_SVM_MCHP_FiP16_Update(&x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP);
    Gain_FiP16_Update(&x2cModel.blocks.sFOC_main.bGain1);
    Gain_FiP16_Update(&x2cModel.blocks.sFOC_main.bGain2);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch2);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch3);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sFOC_main.bManualSwitch4);
    BEMF_MCHP_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP);
    Park_MCHP_FiP16_Update(&x2cModel.blocks.sFOC_main.sPLLEstimator.bPark_MCHP);
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
    Delay_FiP16_Update(&x2cModel.blocks.sspeedPI.bDelay);
    SinGen_FiP16_Update(&x2cModel.blocks.sspeedPI.sperturbation.bSinGen);
    Gain_FiP16_Update(&x2cModel.blocks.sspeedPI.sperturbation.bGain);
    AutoSwitch_FiP16_Update(&x2cModel.blocks.sspeedPI.sperturbation.bAutoSwitch);
    TypeConv_FiP16_Bool_Update(&x2cModel.blocks.sstartup.bTypeConv1);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.bManualSwitch1);
    RateLimiter_FiP16_Update(&x2cModel.blocks.sspeedPI.bRateLimiter);
    Sub_FiP16_Update(&x2cModel.blocks.sspeedPI.bSpeed_error);
    PI_FiP16_Update(&x2cModel.blocks.sspeedPI.bPI_speed);
    ManualSwitch_FiP16_Update(&x2cModel.blocks.sspeedPI.bManualSwitch);
    Add_FiP16_Update(&x2cModel.blocks.sspeedPI.sperturbation.bAdd);
    RateLimiter_FiP16_Update(&x2cModel.blocks.sspeedPI.sperturbation.bRateLimiter);
}

