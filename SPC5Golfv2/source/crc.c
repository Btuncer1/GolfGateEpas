/*
 * crc.c
 *
 *  Created on: 21 Ara 2023
 *      Author: bayra
 */

#include "crc.h"
#define CRC8_H2F_START_VALUE    0xFFU
#define CRC8_H2F_XOR            0xFFU

static const uint8_t crc8H2F_tab[256] = { 0x0, 0x2f, 0x5e, 0x71, 0xbc, 0x93,
		0xe2, 0xcd, 0x57, 0x78, 0x9, 0x26, 0xeb, 0xc4, 0xb5, 0x9a, 0xae, 0x81,
		0xf0, 0xdf, 0x12, 0x3d, 0x4c, 0x63, 0xf9, 0xd6, 0xa7, 0x88, 0x45, 0x6a,
		0x1b, 0x34, 0x73, 0x5c, 0x2d, 0x2, 0xcf, 0xe0, 0x91, 0xbe, 0x24, 0xb,
		0x7a, 0x55, 0x98, 0xb7, 0xc6, 0xe9, 0xdd, 0xf2, 0x83, 0xac, 0x61, 0x4e,
		0x3f, 0x10, 0x8a, 0xa5, 0xd4, 0xfb, 0x36, 0x19, 0x68, 0x47, 0xe6, 0xc9,
		0xb8, 0x97, 0x5a, 0x75, 0x4, 0x2b, 0xb1, 0x9e, 0xef, 0xc0, 0xd, 0x22,
		0x53, 0x7c, 0x48, 0x67, 0x16, 0x39, 0xf4, 0xdb, 0xaa, 0x85, 0x1f, 0x30,
		0x41, 0x6e, 0xa3, 0x8c, 0xfd, 0xd2, 0x95, 0xba, 0xcb, 0xe4, 0x29, 0x6,
		0x77, 0x58, 0xc2, 0xed, 0x9c, 0xb3, 0x7e, 0x51, 0x20, 0xf, 0x3b, 0x14,
		0x65, 0x4a, 0x87, 0xa8, 0xd9, 0xf6, 0x6c, 0x43, 0x32, 0x1d, 0xd0, 0xff,
		0x8e, 0xa1, 0xe3, 0xcc, 0xbd, 0x92, 0x5f, 0x70, 0x1, 0x2e, 0xb4, 0x9b,
		0xea, 0xc5, 0x8, 0x27, 0x56, 0x79, 0x4d, 0x62, 0x13, 0x3c, 0xf1, 0xde,
		0xaf, 0x80, 0x1a, 0x35, 0x44, 0x6b, 0xa6, 0x89, 0xf8, 0xd7, 0x90, 0xbf,
		0xce, 0xe1, 0x2c, 0x3, 0x72, 0x5d, 0xc7, 0xe8, 0x99, 0xb6, 0x7b, 0x54,
		0x25, 0xa, 0x3e, 0x11, 0x60, 0x4f, 0x82, 0xad, 0xdc, 0xf3, 0x69, 0x46,
		0x37, 0x18, 0xd5, 0xfa, 0x8b, 0xa4, 0x5, 0x2a, 0x5b, 0x74, 0xb9, 0x96,
		0xe7, 0xc8, 0x52, 0x7d, 0xc, 0x23, 0xee, 0xc1, 0xb0, 0x9f, 0xab, 0x84,
		0xf5, 0xda, 0x17, 0x38, 0x49, 0x66, 0xfc, 0xd3, 0xa2, 0x8d, 0x40, 0x6f,
		0x1e, 0x31, 0x76, 0x59, 0x28, 0x7, 0xca, 0xe5, 0x94, 0xbb, 0x21, 0xe,
		0x7f, 0x50, 0x9d, 0xb2, 0xc3, 0xec, 0xd8, 0xf7, 0x86, 0xa9, 0x64, 0x4b,
		0x3a, 0x15, 0x8f, 0xa0, 0xd1, 0xfe, 0x33, 0x1c, 0x6d, 0x42 };

uint8_t Crc_CalculateCRC8H2F(const uint8_t *Crc_DataPtr, uint32_t Crc_Length,
		uint32_t adress) {
	uint8_t crc = 0;
	uint8_t counter = Crc_DataPtr[1] & 0x0F;
	if (Crc_DataPtr != NULL) {

		crc = CRC8_H2F_START_VALUE;
		Crc_DataPtr++; //CRC the payload first, skipping over the first byte where the CRC
		for (uint32_t byte = 1; byte < Crc_Length; byte++) {
			crc = crc8H2F_tab[crc ^ *Crc_DataPtr];
			Crc_DataPtr++;
		}

		switch (adress) {
		case 0x86:  // LWI_01 Steering Angle
			crc ^=
					(uint8_t[] ) { 0x86, 0x86, 0x86, 0x86, 0x86, 0x86,
									0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86,
									0x86, 0x86, 0x86 } [counter];
			break;
		case 0x9F:  // LH_EPS_03 Electric Power Steering
			crc ^=
					(uint8_t[] ) { 0xF5, 0xF5, 0xF5, 0xF5, 0xF5, 0xF5,
									0xF5, 0xF5, 0xF5, 0xF5, 0xF5, 0xF5, 0xF5,
									0xF5, 0xF5, 0xF5 } [counter];
			break;
		case 0xAD:  // Getriebe_11 Automatic Gearbox
			crc ^=
					(uint8_t[] ) { 0x3F, 0x69, 0x39, 0xDC, 0x94, 0xF9,
									0x14, 0x64, 0xD8, 0x6A, 0x34, 0xCE, 0xA2,
									0x55, 0xB5, 0x2C } [counter];
			break;
		case 0xB5:
			crc ^=
					(uint8_t[] ) { 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
									0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
									0xE4, 0xE4, 0xE4 } [counter];
			break;
		case 0xFD:  // ESP_21 Electronic Stability Program
			crc ^=
					(uint8_t[] ) { 0xB4, 0xEF, 0xF8, 0x49, 0x1E, 0xE5,
									0xC2, 0xC0, 0x97, 0x19, 0x3C, 0xC9, 0xF1,
									0x98, 0xD6, 0x61 } [counter];
			break;
		case 0x106: // ESP_05 Electronic Stability Program
			crc ^=
					(uint8_t[] ) { 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
									0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
									0x07, 0x07, 0x07 } [counter];
			break;
		case 0x117: // ACC_10 Automatic Cruise Control
			crc ^=
					(uint8_t[] ) { 0x16, 0x16, 0x16, 0x16, 0x16, 0x16,
									0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16,
									0x16, 0x16, 0x16 } [counter];
			break;
		case 0x120: // TSK_06 Drivetrain Coordinator
			crc ^=
					(uint8_t[] ) { 0xC4, 0xE2, 0x4F, 0xE4, 0xF8, 0x2F,
									0x56, 0x81, 0x9F, 0xE5, 0x83, 0x44, 0x05,
									0x3F, 0x97, 0xDF } [counter];
			break;
		case 0x121: // Motor_20 Driver Throttle Inputs
			crc ^=
					(uint8_t[] ) { 0xE9, 0x65, 0xAE, 0x6B, 0x7B, 0x35,
									0xE5, 0x5F, 0x4E, 0xC7, 0x86, 0xA2, 0xBB,
									0xDD, 0xEB, 0xB4 } [counter];
			break;
		case 0x122: // ACC_06 Automatic Cruise Control
			crc ^=
					(uint8_t[] ) { 0x37, 0x7D, 0xF3, 0xA9, 0x18, 0x46,
									0x6D, 0x4D, 0x3D, 0x71, 0x92, 0x9C, 0xE5,
									0x32, 0x10, 0xB9 } [counter];
			break;
		case 0x126: // HCA_01 Heading Control Assist
			crc ^=
					(uint8_t[] ) { 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA,
									0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA,
									0xDA, 0xDA, 0xDA } [counter];
			break;
		case 0x12B: // GRA_ACC_01 Steering wheel controls for ACC
			crc ^=
					(uint8_t[] ) { 0x6A, 0x38, 0xB4, 0x27, 0x22, 0xEF,
									0xE1, 0xBB, 0xF8, 0x80, 0x84, 0x49, 0xC7,
									0x9E, 0x1E, 0x2B } [counter];
			break;
		case 0x187: // EV_Gearshift "Gear" selection data for EVs with no gearbox
			crc ^=
					(uint8_t[] ) { 0x7F, 0xED, 0x17, 0xC2, 0x7C, 0xEB,
									0x44, 0x21, 0x01, 0xFA, 0xDB, 0x15, 0x4A,
									0x6B, 0x23, 0x05 } [counter];
			break;
		case 0x30C: // ACC_02 Automatic Cruise Control
			crc ^=
					(uint8_t[] ) { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
									0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
									0x0F, 0x0F, 0x0F } [counter];
			break;
		case 0x30F: // SWA_01 Lane Change Assist (SpurWechselAssistent)
			crc ^=
					(uint8_t[] ) { 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
									0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
									0x0C, 0x0C, 0x0C } [counter];
			break;
		case 0x324: // ACC_04 Automatic Cruise Control
			crc ^=
					(uint8_t[] ) { 0x27, 0x27, 0x27, 0x27, 0x27, 0x27,
									0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27,
									0x27, 0x27, 0x27 } [counter];
			break;
		case 0x3C0: // Klemmen_Status_01 ignition and starting status
			crc ^=
					(uint8_t[] ) { 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3,
									0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3,
									0xC3, 0xC3, 0xC3 } [counter];
			break;
		case 0x65D: // ESP_20 Electronic Stability Program
			crc ^=
					(uint8_t[] ) { 0xAC, 0xB3, 0xAB, 0xEB, 0x7A, 0xE1,
									0x3B, 0xF7, 0x73, 0xBA, 0x7C, 0x9E, 0x06,
									0x5F, 0x02, 0xD9 } [counter];
			break;
		case 0x10B: // ABS
			crc ^=
					(uint8_t[] ) { 0x77, 0x5C, 0xA0, 0x89, 0x4B, 0x7C,
									0xBB, 0xD6, 0x1F, 0x6C, 0x4F, 0xF6, 0x20,
									0x2B, 0x43, 0xDD } [counter];
			break;
		case 0x14D: // ACC
			crc ^=
					(uint8_t[] ) { 0x1A, 0x65, 0x81, 0x96, 0xC0, 0xDF,
									0x11, 0x92, 0xD3, 0x61, 0xC6, 0x95, 0x8C,
									0x29, 0x21, 0xB5 } [counter];
			break;
		case 0x139: //brakefeedback
			crc ^=
					(uint8_t[] ) { 0xED, 0x03, 0x1C, 0x13, 0xC6, 0x23,
									0x78, 0x7A, 0x8B, 0x40, 0x14, 0x51, 0xBF,
									0x68, 0x32, 0xBA } [counter];
			break;
		case 0x13D: // EPAS feedback
			crc ^=
					(uint8_t[] ) { 0x20, 0xCA, 0x68, 0xD5, 0x1B, 0x31,
									0xE2, 0xDA, 0x08, 0x0A, 0xD4, 0xDE, 0x9C,
									0xE4, 0x35, 0x5B } [counter];
			break;
		case 0x407: // PDC
			crc ^=
					(uint8_t[] ) { 0xEF, 0x60, 0x04, 0xA8, 0x0C, 0x1C,
									0xDA, 0x07, 0x36, 0xD7, 0x28, 0x92, 0xA9,
									0x88, 0x2C, 0x4A } [counter];

			break;
		default:    // As-yet undefined CAN message, CRC check expected to fail
			//printf("Attempt to CRC check undefined Volkswagen message 0x%02X\n", address);
			//crc ^= magiccrc[counter];//(uint8_t[]){0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}[counter];
			break;
		}
		crc = crc8H2F_tab[crc];
		crc = crc ^ CRC8_H2F_XOR;

	}

	return crc;

}

void converto1byteorder(uint8_t *bytein4, uint8_t *byteout1) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 4; j++) {
			byteout1[4 * i + j] = bytein4[4 * i + 3 - j];
		}
	}
}

void converto4byteorder(uint8_t *bytein1, uint8_t *byteout4) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 4; j++) {
			byteout4[4 * i + j] = bytein1[4 * i + 3 - j];
		}
	}

}

