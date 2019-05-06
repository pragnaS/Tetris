// put implementations for functions, explain how it works
// put your names here, date
#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "sound.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	int delay;
	SYSCTL_RCGCGPIO_R |= 0x02;  //turning on clock B
	delay ++;
	delay ++;
	delay ++;
	delay ++;
	GPIO_PORTB_AMSEL_R &=~0x0F; //no analog
	GPIO_PORTB_PCTL_R &=~0x00000FFF; //regular GPIO function
	GPIO_PORTB_DIR_R |= 0x0F; //setting PB0-3 as outputs
	GPIO_PORTB_AFSEL_R &= ~0x0F;  //disabling the alt function on PB2-5
	GPIO_PORTB_DEN_R |= 0x0F; //enabing PB0-3
}
// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(uint32_t data){
	//GPIO_PORTB_DATA_R = 0x8;
		GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x0F) | (data & 0x0F);	
}
