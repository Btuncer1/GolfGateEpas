/****************************************************************************
*
* Copyright © 2017-2022 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*****************************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

#include "pal.h"

/*
 * Setup for a generic SPC58xGxx board.
 */

/*
 * Board identifiers.
 */
#define BOARD_SPC58xGXX_EVB
#define BOARD_NAME                  "SPC58xGxx_EVB"

/*
 * Support macros.
 */
#define MSCR_IO_INDEX(port, pin)    (((port) * 16U) + (pin))

/*
 * I/O definitions.
 */
#define HSO3                        10U
#define HSO2                        11U
#define HSO5                        8U
#define HSO4                        9U
#define PIN_RX_4_1                  1U
#define PIN_TX_4_1                  2U
#define PIN_TX_5_1                  6U
#define PIN_RX_5_1                  7U
#define HSO1                        10U
#define PIN_GPIO80                  0U
#define PIN_GPIO81                  1U
#define PIN_TX_3_0                  0U
#define PIN_RX_3_0                  1U

/*
 * PORT definitions.
 */
#define PORT_HSO3                   PORT_B
#define PORT_HSO2                   PORT_B
#define PORT_HSO5                   PORT_B
#define PORT_HSO4                   PORT_B
#define PORT_PIN_RX_4_1             PORT_C
#define PORT_PIN_TX_4_1             PORT_C
#define PORT_PIN_TX_5_1             PORT_C
#define PORT_PIN_RX_5_1             PORT_C
#define PORT_HSO1                   PORT_D
#define PORT_PIN_GPIO80             PORT_F
#define PORT_PIN_GPIO81             PORT_F
#define PORT_PIN_TX_3_0             PORT_H
#define PORT_PIN_RX_3_0             PORT_H

/*
 * MSCR_IO definitions.
 */
#define MSCR_IO_HSO3                MSCR_IO_INDEX(PORT_HSO3, HSO3)
#define MSCR_IO_HSO2                MSCR_IO_INDEX(PORT_HSO2, HSO2)
#define MSCR_IO_HSO5                MSCR_IO_INDEX(PORT_HSO5, HSO5)
#define MSCR_IO_HSO4                MSCR_IO_INDEX(PORT_HSO4, HSO4)
#define MSCR_IO_PIN_RX_4_1          MSCR_IO_INDEX(PORT_PIN_RX_4_1, PIN_RX_4_1)
#define MSCR_IO_PIN_TX_4_1          MSCR_IO_INDEX(PORT_PIN_TX_4_1, PIN_TX_4_1)
#define MSCR_IO_PIN_TX_5_1          MSCR_IO_INDEX(PORT_PIN_TX_5_1, PIN_TX_5_1)
#define MSCR_IO_PIN_RX_5_1          MSCR_IO_INDEX(PORT_PIN_RX_5_1, PIN_RX_5_1)
#define MSCR_IO_HSO1                MSCR_IO_INDEX(PORT_HSO1, HSO1)
#define MSCR_IO_PIN_GPIO80          MSCR_IO_INDEX(PORT_PIN_GPIO80, PIN_GPIO80)
#define MSCR_IO_PIN_GPIO81          MSCR_IO_INDEX(PORT_PIN_GPIO81, PIN_GPIO81)
#define MSCR_IO_PIN_TX_3_0          MSCR_IO_INDEX(PORT_PIN_TX_3_0, PIN_TX_3_0)
#define MSCR_IO_PIN_RX_3_0          MSCR_IO_INDEX(PORT_PIN_RX_3_0, PIN_RX_3_0)

/*
 * MSCR_MUX definitions.
 */
#define MSCR_MUX_PIN_RX_4_1         252U
#define MSCR_MUX_PIN_RX_5_1         253U
#define MSCR_MUX_PIN_RX_3_0         248U

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
