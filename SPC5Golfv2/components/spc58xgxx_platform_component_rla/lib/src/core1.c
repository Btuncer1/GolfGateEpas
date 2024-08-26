/****************************************************************************
*
* Copyright © 2017-2019 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*****************************************************************************/

/**
 * @file    core1.c
 * @brief   core1 boot module code.
 *
 * @addtogroup PPC_BOOT
 * @{
 */

#include "components.h"

#if (BOOT_CORE1 == 1)
/*===========================================================================*/
/* Module extern definitions.                                                 */
/*===========================================================================*/
extern void *_reset_address1(void);
/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief  Run Core 0 using ME.CADDR1 and ME.CCTL1 registers  
 *
 * @api
 */

void runCore1(void){
  uint32_t mode;

  /* Start core1.*/
  /* Conversion between a pointer to function and another type needed to update
     the CADDR1 register with the address of the core1 reset routine.*/
  /*lint -e9074 -e546 */
  MC_ME.CADDR3.R = ((uint32_t)&_reset_address1 | 0x01UL); /* Set reset vector for core1, core1 will be reset on the next mode transition */
  /*lint +e9074 +e546 */
  MC_ME.CCTL3.R = 0x00FEU;                                /* Set modes in which core_1 will run.                                         */
  
  /* Force mode transition to the current mode.*/
  mode = MC_ME.GS.B.S_CURRENT_MODE;
  MC_ME.MCTL.R = (mode << 28 ) | 0x00005AF0UL;            /* Mode & Key                               */
  MC_ME.MCTL.R = (mode << 28 ) | 0x0000A50FUL;            /* Mode & Key                               */
  while(MC_ME.GS.B.S_MTRANS == 1U) {                      /* Waiting for end of transaction           */
  }                               
  while(MC_ME.GS.B.S_CURRENT_MODE != mode) {              /* Check mode has successfully been entered */
  }          
}
#endif /* BOOT_CORE1 */
/** @} */
