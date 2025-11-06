#include <lpc214x.h>
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc_defines.h"
#include "rtc.h"
#include "keypad_init.h"
#include "keypad_defines.h"
#include "interrupt_edit.h"
#include "definitions.h"
u32 hour,min,sec,date,month,year,day;
u16 adcval;
f32 eAR;

/*
after every key pressed it allows to print the character in LCD
if character is not matches terminates the while loop
*/

void edit_TD(u32 *td)
{
  u8 key;
  *td=0;
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		key=keyscan();                       
		if(key>='0'&&key<='9')
		{
			CharLCD(key);
			*td=(*td*10)+(key-'0');
			while(colscan()==0);
		}
		else
		{
			while(colscan()==0);
			CmdLCD(CLEAR_LCD);
			break;
		}
	}
}


/*    here the when the interrupt occurs keyapd matrix is ude to edit the date 
     time,day as user wish
*/
void eint0_isr()__irq
{
	u8 choice,key;
	CmdLCD(CLEAR_LCD);
	StrLCD("1.EDIT RTC INFO");          //user can choose the options to edit or  to exit
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("2.EXIT");
	choice=keyscan();	
 if(choice=='1')
 {
	while(colscan()==0);
	CmdLCD(CLEAR_LCD);
	while(1)
	{
	  StrLCD("1.H 2.Mi 3.S 4.D");
		CmdLCD(GOTO_LINE2_POS0);          // based on the numbers displaying on lcd manual editing is easy to understand
		StrLCD("5.M 6.Y 7.Dy 8.E");
		key=keyscan();
			if(key=='8'){
      CmdLCD(CLEAR_LCD);				//when 8 is pressed it terminates from editing mode
				break;
			}
		while(colscan()==0);
		switch(key)
		{
			case '1':
						edit_TD(&hour);                     
						if(hour>23)
							{
								StrLCD("INVALID");
								CmdLCD(GOTO_LINE2_POS0);     //if the hour value is more than 23 
								StrLCD("ENTER AGAIN");       //it throws an invalid message and edit again 
								delay_ms(100);
							}
						 else
			           HOUR=hour;                  // After the editing the updated value is assigned to respected SFR'S
			      CmdLCD(CLEAR_LCD);
			      break;
			case '2':
					 edit_TD(&min);
					 if(min>59)
						{
							StrLCD("INVALID");
							CmdLCD(GOTO_LINE2_POS0);
							StrLCD("ENTER AGAIN");
							delay_ms(100);
						}
					 else
								MIN=min;
					  CmdLCD(CLEAR_LCD);
		    	  break;
			case '3':
						edit_TD(&sec);
						if(sec>59)
							{
								StrLCD("INVALID");
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("ENTER AGAIN");
								delay_ms(100);
							}
						else
								SEC=sec;
						CmdLCD(CLEAR_LCD);
						break;
			case '4':
				edit_TD(&date);
            if(date>31){
					      StrLCD("INVALID");
					      CmdLCD(GOTO_LINE2_POS0);
					      StrLCD("ENTER AGAIN");
					      delay_ms(100);
					      }
					  else
			         DOM=date;
			         CmdLCD(CLEAR_LCD);
		    	break;
			case '5':
				    edit_TD(&month);
			      if(month>12)
							{
								StrLCD("INVALID");
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("ENTER AGAIN");
								delay_ms(100);
							}
					  else
								MONTH=month;
			      CmdLCD(CLEAR_LCD);
						break;
			case '6':
				   edit_TD(&year);
			     YEAR=year;
			     CmdLCD(CLEAR_LCD);
		    	 break;
			case '7':
				edit_TD(&day);
			     if(day>6)
						 {
					      StrLCD("INVALID");
					      CmdLCD(GOTO_LINE2_POS0);
					      StrLCD("ENTER AGAIN");
					      delay_ms(100);
					    }
					  else
			   DOW=day;
			   CmdLCD(CLEAR_LCD);
		    	break;	
		}						
	 }
 }
 else if(choice=='2')
	{
	CmdLCD(CLEAR_LCD);
  }
	EXTINT=1<<0;            // if choice is 2 the interrupt terminates and enters to main loop again
	VICVectAddr=0;
}
void enable_eint0(void)
{
	keypad_init();
	// p0.16 is cfg as eint0
	CfgPortPinFunc(0,16,EINT0_FUN);
	//select the type of the interrupt irq/fiq
	VICIntSelect=0;//irq type
	//enable the eint0
	VICIntEnable=1<<EINT0;
	//set the enable bit and channel binary
	VICVectCntl0=(1<<5)|EINT0;
	//assign the ISR address
	VICVectAddr0=(unsigned int)eint0_isr;
	//edge triggereing
	EXTMODE=1<<0;
	//falling edge
	EXTPOLAR=0<<0;
}

void Street_lights(void)
{
	 WRITEBYTE(IOPIN0,LEDS,0XF0);                 //All LEDS is in ON condition(4 Active high and 4 active low)
	 delay_ms(100);
}
 //Main function
int main()
{
	 //Initialize RTC
	  RTC_Init();
	  Init_ADC();
		
   //Initialize the LCD
	  InitLCD();
  //Set the initial time (hours, minutes, seconds)
    SetRTCTimeInfo(18,40,00);
    SetRTCDateInfo(28,8,2025);
    SetRTCDay(5);                    // Friday
	  IODIR0|=0XFF<<LEDS;
	  WRITEBYTE(IOPIN0,LEDS,0X0f);     //All 8 LEDS is in OFF condition
	  delay_ms(100);
	  enable_eint0();                  //interrupt function 
    while (1) 
		{ 
			GetRTCTimeInfo(&hour,&min,&sec);
			DisplayRTCTime(hour,min,sec);
			GetRTCDateInfo(&date,&month,&year);         //here always updating the hour,sec,min,date,day,year every time
			DisplayRTCDate(date,month,year);
			GetRTCDay(&day);
			DisplayRTCDay(day);
			if((hour>=18&&hour<=23)||(hour>=0&&hour<=6))
			{
				Read_ADC(1,&adcval,&eAR);
			  CmdLCD(GOTO_LINE2_POS0+11);
	      U32LCD(eAR*100);
			  StrLCD(" 'C");                 //when the time is in the range Based on LDR Thersold value the LEDS is ON/OFF
				if(adcval<500)
				Street_lights();
				else
			  {
				WRITEBYTE(IOPIN0,LEDS,0X0f);
				delay_ms(100);
			  }
			}
			else
			{
				WRITEBYTE(IOPIN0,LEDS,0X0f);
				delay_ms(100);
			}
    }
}
