#ifndef ADC_DEFINES_H
#define ADC_DEFINES_H

#define   FCLK    12000000
#define   CCLK    (5*FCLK)
#define   PCLK     (CCLK/4)
#define   ADCLK    (PCLK/5)
#define   CLKDIV  ((PCLK/ADCLK)-1)


#define  CLKDIV_BITS            8
#define   PDN_BIT               21
#define  ADC_CONV_START_BIT     24
#define   DONE_BIT              31
#define   DIGITAL_DATA_BITS     6

void Init_ADC(void);
#endif
