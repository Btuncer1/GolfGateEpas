/*
 * CAN_tools.h
 *
 *  Created on: 23 A?u 2024
 *      Author: bayra
 */

#ifndef CAN_TOOLS_H_
#define CAN_TOOLS_H_



#endif /* CAN_TOOLS_H_ */

#include "can_lld_cfg.h"

void copyCANmsgs(CANTxFrame *to, CANRxFrame *from);
void clearCANerrors(CANDriver *cand);
