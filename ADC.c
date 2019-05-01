// put implementations for functions, explain how it works
// put your names here, date
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void ADC_Init(void){ 
	volatile int delay;
	SYSCTL_RCGCGPIO_R |=0x08; //activate clocl for Port D
	while((SYSCTL_PRGPIO_R&0x08)==0){};
		GPIO_PORTD_DIR_R &=~0x04;	//make PD2 input
		GPIO_PORTD_AFSEL_R |=0x04; //enable alternate fun on PD2
		GPIO_PORTD_DEN_R &=~0x04;	//disable digital I/O on PD2
		GPIO_PORTD_AMSEL_R |=0x04; //enable analog fun on PD2
		SYSCTL_RCGCADC_R |=0x01;	//activate ADC0
		delay = SYSCTL_RCGCADC_R;	//extra time to stablize
		delay = SYSCTL_RCGCADC_R;	//extra time to stablize
		delay = SYSCTL_RCGCADC_R;	//extra time to stablize
		delay = SYSCTL_RCGCADC_R;	//extra time to stablize
		ADC0_PC_R=0x01;		//configure for 125k
		ADC0_SSPRI_R=0x0123; //seq 3 is highest priority
		ADC0_ACTSS_R&=~0x0008; //disable sample sequencer 3
		ADC0_EMUX_R&=~0xF000;	//seq3 is software trigger
		ADC0_SSMUX3_R=(ADC0_SSMUX3_R&0xFFFFFFF0)+5; 	//Ain5 (PD2)
		ADC0_SSCTL3_R=0x0006;	//no TS0 D0, yes IE0 END0
		ADC0_IM_R &=~0x0008; 	//disable SS3 interrupts
		ADC0_ACTSS_R |=0x0008;	//enable sample sequencer 3

}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC_In(void){  
	uint32_t data;
	ADC0_PSSI_R = 0x0008;	//start ADC
	while((ADC0_RIS_R&0x08)==0){};	//status
	data=ADC0_SSFIFO3_R&0xFFF;	//read data
	ADC0_ISC_R = 0x0008;	//clear flag
	return data;
	
}

