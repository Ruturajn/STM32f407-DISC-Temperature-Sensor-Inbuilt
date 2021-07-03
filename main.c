#include "stm32f4xx.h"

void ADC1_Init(void);
int data;
double volt,temp;


void ADC1_Init(){
	RCC->APB2ENR |= 0x00000100; //Enable ADC1 clock
	ADC1->SQR3 |= 16; // Select the ADC Channel
	ADC1->SMPR1 |= 1<<18|1<<19|1<<20; // Select the sampling rate
	ADC->CCR |= 0x800000; //Enable the temp sensor
	ADC->CCR &= ~0x400000; //VBATE must be disabled for temp sensor
	ADC1->CR2 |= 1<<0|1<<1; //ADON and CONT enabled
}


int main(){
	ADC1_Init();
	ADC1->CR2 |= 1<<30; // Start Conversion
	while(1){
		while(!(ADC1->SR & 2)) {}
		data = ADC1->DR;
		volt = (double)data/4095*3300;
		temp = ((volt-760.0)/2.5) + 25;
	}
}



