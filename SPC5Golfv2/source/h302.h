/*
 * h302.h
 *
 *  Created on: 27 ?ub 2024
 *      Author: bayra
 */

#ifndef INC_H302_H_
#define INC_H302_H_

#include "stdint.h"
#include "math.h"

void Steering_assist(uint8_t *data, float steeringangle,uint8_t steertorque,uint8_t enable);
void rateLimitter(float input,float*output,float rate);
#endif /* INC_H302_H_ */
