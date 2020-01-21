/***************************************************************************/
/*                          U N I - L I N Z                                */
/*                                                                         */
/* (c) Institut für Leistungselektornik und elektrische Antriebe           */
/***************************************************************************/
/*                                                                         */
/*      Projekt:        M2C BLOCKs                                         */
/*      Filename:       MathUtilities.h                                    */
/*      Author:         Herbert Grabner                                    */
/*                                                                         */
/*=========================================================================*/
/*      History                                                            */
/*-------------------------------------------------------------------------*/
/*      09.02.04    Release 1                                              */
/***************************************************************************/

#ifndef __MATHUTILITIES__
#define __MATHUTILITIES__

#include "target.h"

// Anmerkung: Makros für Multiplikation !!!!!
// temp.LNG = (int32)x * (int32)y;
// NUR temp.INT_H auf Überlauf prüfen !!!!!!!!!!!!!!1

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
// zum Vergleich t=1370 us @24xx
//       temp = (int32)A + (int32)B;	//
//       LIMIT(temp,INT16_MAX);       // 

// ------- iC = iA + iB -------- ,  t=920us @24xx
#define ADD_INT16(iC,iA,iB)												\
	iC = iA + iB;				            							\
	if ((iA >= 0) && (iB >= 0) && (iC < 0))								\
    	iC = INT16_MAX;                           						\
 	else if ((iA < 0) && (iB < 0) && ((iC >= 0) || (iC == 0x8000)))    	\
    	iC = -INT16_MAX
    	
// ------- iC = iA + iB --------
#define ADD_INT32(iC,iA,iB)												\
	iC = iA + iB;				            							\
	if ((iA >= 0) && (iB >= 0) && (iC < 0))								\
    	iC = (int32)INT32_MAX;                           				\
 	else if ((iA < 0) && (iB < 0) && ((iC >= 0) || (iC == 0x80000000l)))\
    	iC = -(int32)INT32_MAX

// ------- uiC = uiA + uiB -------- , 
#define ADD_UINT32(uiC,uiA,uiB)											\
	uiC = uiA + uiB;				            						\
	if (uiC < uiA)														\
    	uiC = (uint32)UINT32_MAX	                           						

// ------- uiC = uiA + uiB -------- , 
#define ADD_UINT16(uiC,uiA,uiB)											\
	uiC = uiA + uiB;				            						\
	if (uiC < uiA)														\
    	uiC = UINT16_MAX	                           						

// ------- uiC = (uint16)iA -------- 
#define INT16_2_UINT16(uiC,iA)											\
  if ( iA <= 0 )                                                        \
    uiC = 0;															\
  else                                                                  \
    C = (uint16)iA

// ------- i32_C = (int16)i16_A -------- 
#define INT32_2_INT16(i16_C,i32_A)										\
  if ( i32_A > (0x7FFF) )												\
    i16_C = (int16)INT16_MAX;	                                        \
  else if ( i32_A <= ((int32)(0xFFFF8000l)) )                           \
    i16_C = -(int16)INT16_MAX;                                          \
  else                                                                  \
    i16_C = ((int16)i32_A);                                             
    
#endif

