/****************************************************************************
 *
 * Copyright © 2015-2021 STMicroelectronics - All Rights Reserved
 *
 * This software is licensed under SLA0098 terms that can be found in the
 * DM00779817_1_0.pdf file in the licenses directory of this software product.
 *
 * THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
 * INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *****************************************************************************/

/* Inclusion of the main header files of all the imported components in the
 order specified in the application wizard. The file is generated
 automatically.*/
#include "components.h"
#include "can_lld_cfg.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "h302.h"
/*
 * Application entry point.
 */

QueueHandle_t xQueue_CAN5;
uint8_t Relay = 0, autonom = 0;
float Setsteer =0;
uint8_t setTorque;
void parseinterface(float* setSteeringDegree, uint8_t* setTorque,uint8_t* autonomEnable, uint8_t* data);
portTASK_FUNCTION( vTaskCAN5, pvParameters ) {
	(void) pvParameters;

	for (;;) {
		CANRxFrame CANRX;
		BaseType_t queuert;
		queuert = xQueueReceive(xQueue_CAN5, &CANRX, portMAX_DELAY);

		if (queuert == pdTRUE) {
			if (CANRX.ID == 0x00B4227U) {
				CANTxFrame txCl;
				static unsigned char life_signal;
				const unsigned RB_DEVICE_ID = 0X06U;
				txCl.DLC = 2;
				txCl.ID = 0x00B4226U;
				txCl.OPERATION = CAN_OP_NORMAL;
				txCl.TYPE = CAN_ID_XTD;
				txCl.data8[0] = life_signal++;
				txCl.data8[1] = RB_DEVICE_ID;
				can_lld_transmit(&CAND8, CAN_QUEUE_TXBUFFER, &txCl);
			}
			if(CANRX.ID == 0x350)
			{
				parseinterface(&Setsteer, &setTorque,&autonom, CANRX.data8);
			}
		}

	}

}
portTASK_FUNCTION( vTaskParkAssist, pvParameters ) {
	(void) pvParameters;
	static uint8_t preautonom = 0;
	CANTxFrame CAN1tx;
	CAN1tx.DLC = 24;
	CAN1tx.ID = 0x302;
	CAN1tx.RTR = 0;
	CAN1tx.OPERATION = CAN_OP_CANFD;
	CAN1tx.TYPE = CAN_ID_STD;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		if (Relay) {
			if(autonom)
			{
				Steering_assist(CAN1tx.data8, Setsteer, setTorque/2, 1);
				can_lld_transmit(&CAND7, CAN_QUEUE_TXBUFFER, &CAN1tx);
			}
			else
			{
				Steering_assist(CAN1tx.data8, Setsteer, setTorque, 0);
				can_lld_transmit(&CAND7, CAN_QUEUE_TXBUFFER, &CAN1tx);
			}

			if(autonom == 0 && preautonom ==1)
			{
				Steering_assist(CAN1tx.data8, Setsteer, setTorque, 0);
				can_lld_transmit(&CAND7, CAN_QUEUE_TXBUFFER, &CAN1tx);
			}
			preautonom = autonom;
		}

		vTaskDelayUntil(&xLastWakeTime, 20);
	}
}
portTASK_FUNCTION( vTaskmain, pvParameters ) {
	(void) pvParameters;

	pal_lld_setpad(PORT_PIN_GPIO80, PIN_GPIO80);
	pal_lld_setpad(PORT_PIN_GPIO81, PIN_GPIO81);

	can_lld_start(&CAND4, &can_config_can3);
	can_lld_start(&CAND7, &can_config_can4);
	can_lld_start(&CAND8, &can_config_can5);
	xTaskCreate(vTaskCAN5, (const char* const ) "task #1",
	configMINIMAL_STACK_SIZE, NULL,
	tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(vTaskParkAssist, (const char* const ) "task #1",
	configMINIMAL_STACK_SIZE, NULL,
	tskIDLE_PRIORITY + 2, NULL);
	xQueue_CAN5 = xQueueCreate(10, sizeof(CANRxFrame));
	if (xQueue_CAN5 == 0) {
		// Queue was not created and must not be used.
	}
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		Relay = 1;
		pal_lld_setpad(PORT_HSO4, HSO4);
		vTaskDelayUntil(&xLastWakeTime, 10);
	}
}
int main(void) {

	/* Initialization of all the imported components in the order specified in
	 the application wizard. The function is generated automatically.*/
	componentsInit();

	//can_lld_start(&CAND4,&can_config_can3);
	xTaskCreate(vTaskmain, (const char* const ) "task #1",
	configMINIMAL_STACK_SIZE, NULL,
	tskIDLE_PRIORITY + 2, NULL);
	/* Uncomment the below routine to Enable Interrupts. */
	irqIsrEnable();
	vTaskStartScheduler();
	/* Application main loop.*/
	for (;;) {

	}
}
void parseinterface(float* setSteeringDegree, uint8_t* setTorque,uint8_t* autonomEnable, uint8_t* data)
{
	int16_t i16setsteer = 0;
	i16setsteer = data[1] << 8 | data[0];
	*setSteeringDegree = (float)i16setsteer * 0.02f;
	*setTorque = data[2];
	*autonomEnable = data[3];

}
