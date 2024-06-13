/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/*
 * Address of the clock control register (AHB1ENR)
 * 		0x40023800 (base address of memory address documentation) + 0x30 (offset) = 0x40023830
 *
 * 	Address of the GPIOD mode register (used to control mode). has 16 pints, each pin has two bits...
 * 	need to set this address to output mode which is value 01. so set bit 24 to value of 1
 * 		0x40020C00 (base address) + 0x00 (offset) = 0x40020C00
 *
 * 	Address of the GPIOD output data register (used to write)
 * 		0x40020C00 (GPIO port output data register ) + 0x14 (set the pin 12 that controls led 12 on) = 0x40020C13
 */

int main(void)
{
	uint32_t *pClockAddress = (uint32_t*) 0x40023830;
	uint32_t *pModeRegister = (uint32_t*) 0x40020C00;
	uint32_t *pOutputRegister = (uint32_t*) 0x40020C14;

	// 1. Enable the clock for GPOID peripheral in the AHB1EN
//	uint8_t bitwiseSet4 = 0x08; // to set the bit number 3 to on -> 1000
	uint8_t bitwiseSet4 = (1 << 3);  // NEW METHOD: Creates bit number where the number 1 is in third position
	*pClockAddress |= bitwiseSet4; // modify the bit address of the clock of the third bit...
	// This is the same as *pClockAddress = *pClockAddress | bitwiseSet;

	// 2. Configure the mode of the IO pint as output
	uint32_t bitwiseClear32 = ~(3 << 24); // This is to clear the bit 25 and 24 to zero to make sure the 25 is zero...
	// Or you can do ~(3 << 24) which is the same as (0110)
//	uint32_t bitwiseSet24 = 0x01000000; // to set the bit on position 24 on
	uint32_t bitwiseSet24 = (1 << 24); // NEW METHOD: Sets bit 24th with only one
	// a. clear the 24th and 25th bit positions
	*pModeRegister &= bitwiseClear32; // Clear position 24 and 25
	// b. make 24th bit position as 1 (SET)
	*pModeRegister |= bitwiseSet24; // Set the bit 24 to number 1

	// 3. Set the 12th bit of the output data register to make IO pin12 as high
	uint32_t bitwiseClear15 = 0x0000; // This mask value will clear all the first 15 bits to zero to make sure they are zero
//	uint32_t bitwiseSet12 = 0x1000; // This will set all the bits that are not the bit 12 to state of zero
	uint32_t bitwiseSet12 = (1 << 12); // NEW METHOD: Set the bit 12 to one
	*pOutputRegister &= bitwiseClear15;
	*pOutputRegister |= bitwiseSet12;

    /* Loop forever */
	for(;;);
}