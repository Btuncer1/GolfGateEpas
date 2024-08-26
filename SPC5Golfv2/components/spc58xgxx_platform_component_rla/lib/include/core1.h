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
 * @file    core1.h
 * @brief   core1 boot module header.
 *
 * @addtogroup PPC_BOOT
 * @{
 */

#ifndef _CORE1_H_
#define _CORE1_H_

#include "boot.h"

#if (BOOT_CORE1 == 1)
/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
  void runCore1(void);
#ifdef __cplusplus
}
#endif

#endif /* BOOT_CORE1 == 1 */

#endif /* _CORE1_H_ */

/** @} */
