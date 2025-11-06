#ifndef INTERRUPT_EDIT_H
#define INTERRUPT_EDIT_H
#include "types.h"
#define EINT0_FUN FUN2
#define FUN2 1
#define EINT0 14
#define EINT0_LED 8
void eint0_isr(void)__irq;
void enable_eint0(void);
void edit_TD(u32 *hour);
void keypad_init(void);
void CfgPortPinFunc(unsigned int portNo,unsigned int pinNo,unsigned int pinFunc);

#endif
