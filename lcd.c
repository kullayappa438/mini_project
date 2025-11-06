//lcd.c
#include <LPC21xx.h>
#include "definitions.h"
#include "lcd_defines.h"
#include "types.h"
#include "delay.h"
void WriteLCD(u8 anyByte)
{
	//select write operation
	IOCLR0=1<<LCD_RW;
	//put any byte onto data pins d0-d7
	WRITEBYTE(IOPIN0,LCD_DATA,anyByte);
	//provide high to low pulse
	IOSET0=1<<LCD_EN;
	delay_us(1);
	IOCLR0=1<<LCD_EN;
	delay_ms(2);
}

void LcdCmd(u8 cmd)
{
  //select cmd/inst reg
	IOCLR0=1<<LCD_RS;
	//write cmd to reg
	WriteLCD(cmd);
}

void CharLcd(u8 asciiVal)
{
 	//select data reg
	IOSET0=1<<LCD_RS;
	//write ascii via data reg to ddram/display
	WriteLCD(asciiVal);	
}

void Init_LCD(void)
{
	//cfg p0.0 to p0.18 as gpio output pins
	IODIR0=(0xFF<<LCD_DATA)|1<<LCD_RS|1<<LCD_RW|1<<LCD_EN;
	//power on delay
	delay_ms(15);
	LcdCmd(0x30);
	delay_ms(4);
	delay_us(100);
	LcdCmd(0x30);
	delay_us(100);
	LcdCmd(0x30);
	LcdCmd(MODE_8BIT_2LINE);
	LcdCmd(DSP_ON_CUR_OFF);
	LcdCmd(CLEAR_LCD);
  LcdCmd(SHIFT_CUR_RIGHT);	
}

void strLcd(s8 *p)
{
	while(*p)
	{	
		CharLcd(*p++);		
	}	
}
 
void U32LCD(u32 num)
{
	u8 a[10];
	int i=0;
	if(num==0)
	{
		CharLcd('0');
	}
	else
	{
		while(num>0)
		{
			a[i]=(num%10)+48;
			i++;
			num/=10;
		}
		for(--i;i>=0;i--)
		{
			CharLcd(a[i]);
		}			
	}
}

void S32LCD(s32 snum)
{
	if(snum<0)
	{
		CharLcd('-');
		snum=-snum;
	}
	U32LCD(snum);
}

void F32LCD(float fNum,unsigned char nDP)
{
  unsigned int num,i;
	if(fNum<0.0)
	{
		CharLcd('-');
		fNum=-fNum;
	}
	num=fNum;
	U32LCD(num);
	CharLcd('.');
	for(i=0;i<nDP;i++)
	{
		fNum=(fNum-num)*10;
		num=fNum;
		CharLcd(num+48);
	}
}

void BuildCGRAM(unsigned char *p,unsigned char nBytes)
{
	unsigned int i;
  //goto cgram start
  LcdCmd(GOTO_CGRAM_START);
	//select data reg
	IOSET0=1<<LCD_RS;
	for(i=0;i<nBytes;i++)
	{
	//	write to cgram memory
		WriteLCD(p[i]);
	}
	//return back to ddram
	LcdCmd(GOTO_LINE1_POS0);
}
