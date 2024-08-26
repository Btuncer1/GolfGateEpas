/*
 * CAN_tools.c
 *
 *  Created on: 23 A?u 2024
 *      Author: bayra
 */

#include"CAN_tools.h"
#include "can_lld.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "crc.h"
extern QueueHandle_t xQueue_CAN5;
extern uint8_t Relay, autonom;
void can3_rx(uint32_t msgbuf, CANRxFrame crfp) {
	(void) crfp;
	(void) msgbuf;
	CANTxFrame CANtx;
	CANRxFrame CANrx;

	if (CAND4.mcan->IR.B.RF0N != 0U) {

		uint32_t msgbuff;
		msgbuff = CAND4.mcan->RXF0S.B.F0GI;
		/* read message */
		can_lld_readBuffer(&CAND4, CAN_FIFO0_RXBUFFER, msgbuff, &CANrx);
		/* release rx buffer */
		CAND4.mcan->RXF0A.B.F0AI = CAND4.mcan->RXF0S.B.F0GI;
		if (Relay) {
			if (autonom) {
				if (CANrx.ID == 0xFD) {
					copyCANmsgs(&CANtx, &CANrx);

					uint16_t speed_u16 = 0;
					speed_u16 =((uint16_t) CANrx.data8[5] << 8 | CANrx.data8[4]);
					float speedf = (float) speed_u16 * 0.01f;

					//float speedf = Vehicle.WheelSpeed.ESP;
					speedf = speedf > 9.0 ? 9.0 : speedf;
					uint16_t speed = (uint16_t)(speedf * 100);

					CANtx.data8[4] = speed & 0x00FF;
					CANtx.data8[5] = (speed & 0xFF00) >> 8;
					CANtx.data8[0] = Crc_CalculateCRC8H2F(CANtx.data8,
							CANtx.DLC, 0xFD);

					can_lld_transmit(&CAND7, CAN_QUEUE_TXBUFFER, &CANtx);
				} else {
					copyCANmsgs(&CANtx, &CANrx);
					can_lld_transmit(&CAND7, CAN_QUEUE_TXBUFFER, &CANtx);
				}

			} else {
				copyCANmsgs(&CANtx, &CANrx);
				can_lld_transmit(&CAND7, CAN_QUEUE_TXBUFFER, &CANtx);
			}
			/* clear flag */
			if (CAND4.mcan->RXF0S.B.F0FL == 0) {
				CAND4.mcan->IR.B.RF0N = 1;
			}

		}

	}
	clearCANerrors(&CAND4); //if exist
}
;
void can4_rx(uint32_t msgbuf, CANRxFrame crfp) {
	(void) crfp;
	(void) msgbuf;
	CANTxFrame CANtx;
	CANRxFrame CANrx;

	if (CAND7.mcan->IR.B.RF0N != 0U) {

		uint32_t msgbuff;
		msgbuff = CAND7.mcan->RXF0S.B.F0GI;
		/* read message */
		can_lld_readBuffer(&CAND7, CAN_FIFO0_RXBUFFER, msgbuff, &CANrx);
		/* release rx buffer */
		CAND7.mcan->RXF0A.B.F0AI = CAND7.mcan->RXF0S.B.F0GI;
		if (Relay) {
			if (autonom) {
				copyCANmsgs(&CANtx, &CANrx);
				can_lld_transmit(&CAND4, CAN_QUEUE_TXBUFFER, &CANtx);

			} else {
				copyCANmsgs(&CANtx, &CANrx);
				can_lld_transmit(&CAND4, CAN_QUEUE_TXBUFFER, &CANtx);
			}

		}

		/* clear flag */
		if (CAND7.mcan->RXF0S.B.F0FL == 0) {
			CAND7.mcan->IR.B.RF0N = 1;
		}

	}
	clearCANerrors(&CAND7); //if exist
}
;
void can5_rx(uint32_t msgbuf, CANRxFrame crfp) {
	(void) crfp;
	(void) msgbuf;
	CANTxFrame CANtx;
	CANRxFrame CANrx;

	if (CAND8.mcan->IR.B.RF0N != 0U) {

		uint32_t msgbuff;
		msgbuff = CAND8.mcan->RXF0S.B.F0GI;
		/* read message */
		can_lld_readBuffer(&CAND8, CAN_FIFO0_RXBUFFER, msgbuff, &CANrx);
		/* release rx buffer */
		CAND8.mcan->RXF0A.B.F0AI = CAND8.mcan->RXF0S.B.F0GI;
		/*user functions*/

		BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		xQueueSendFromISR(xQueue_CAN5, &CANrx, xHigherPriorityTaskWoken);

		/* clear flag */
		if (CAND8.mcan->RXF0S.B.F0FL == 0) {
			CAND8.mcan->IR.B.RF0N = 1;
		}

	}
	clearCANerrors(&CAND8); //if exist
}
;

void copyCANmsgs(CANTxFrame *to, CANRxFrame *from) {
	to->DLC = from->DLC;
	to->ID = from->ID;
	to->OPERATION = from->OPERATION;
	to->TYPE = from->TYPE;
	to->RTR = from->RTR;
	for (int i = 0; i < 16; i++) {
		to->data32[i] = from->data32[i];
	}
}

void clearCANerrors(CANDriver *cand) {
	if ((cand->mcan->IR.R & MCAN_ERROR_MASK) != 0U) {

		/* BUSOFF interrupt management */
		if (cand->mcan->IR.B.BO == 1U) {
			/* Start Bus Off status exit sequence */
			cand->mcan->CCCR.B.INIT = 0;
		}
		/* reset all error bits checked */
		cand->mcan->IR.R = MCAN_ERROR_MASK;
	}
}
