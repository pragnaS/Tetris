// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10

// Last Modified: 11/20/2018 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2018

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2018

 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "PLL.h"
#include "ADC.h"
#include "Images.h"
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"
#include "Pieces.h"

int score[5]={'S', 'C', 'O', 'R', 'E'};

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(uint32_t count); // time delay in 0.1 seconds


void SysTick_Init(void){
        
        NVIC_ST_CTRL_R =0; //Disable SysTick during setup
        NVIC_ST_RELOAD_R = 1333333; //maximum reload value
        NVIC_ST_CURRENT_R = 0; //any write to current clears it
        //NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
        NVIC_ST_CTRL_R =0x07;
}

void Screen_Init(void)
{
	int i=0;
	for(i=10; i<100; i=i+10)
	{
		ST7735_DrawFastVLine(i, 0, 160, 0xFFFF);		//printing vertical lines
	}
	for(i=10; i<160; i=i+10)
	{
		ST7735_DrawFastHLine(0, i, 90, 0xFFFF);		//printing horizontal lines
	}
		
		ST7735_DrawFastVLine(100, 40, 20, 0xFFFF);	//printing the score board
		ST7735_DrawFastHLine(100, 40, 20, 0xFFFF);
		ST7735_DrawFastVLine(120, 40, 20, 0xFFFF);
		ST7735_DrawFastHLine(100, 60, 20, 0xFFFF);
		
		ST7735_SetCursor(100,40);
		ST7735_OutString("SCORE");
//			for(i=60; i<110; i=i+10){
//				ST7735_OutChar(score[i]); 
//				ST7735_SetTextColor(0xFFFF);
					
	//}
}
	

	
int main(void){


  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
	Random_Init(1);
	Output_Init();
	SysTick_Init();
	Screen_Init();
	Sound_Init();
	
	while(1){}
	
}



void SysTick_Handler(void)
{}
