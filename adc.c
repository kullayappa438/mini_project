#include <LPC21xx.h>
#include "adc_defines.h"
#include "types.h"

void Init_ADC(void)
{
	//cfg p0.27 as ain0 input pin
	PINSEL1=((PINSEL1&~(3<<((27-16)*2)))|(1<<((27-16)*2)));
	//cfg ADCR
	ADCR=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
}

void Read_ADC(u8 chNo,u16 *adcval,f32 *eAR)
{
	//Mask any prev channel sel
	ADCR&=0xffffff00;
	//write channel for analog read,
	//& start adc conversion wrt that channel
	ADCR|=(1<<chNo)|(1<<ADC_CONV_START_BIT);
	//delay_us(3);
	//wait until conversion completion status
	while(((ADDR>>DONE_BIT)&1)==0);
	//stop  adc convert wrt that channel
	ADCR&=~(1<<ADC_CONV_START_BIT);
	//read digital data
	*adcval=((ADDR>>DIGITAL_DATA_BITS)&1023);
	//equivalent analog represention bt/w
	//0 to 3.3v
	*eAR=((*adcval )*(3.3/1023));
}
