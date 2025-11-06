#include <lpc21xx.h>
#include "keypad_defines.h"
#include "definitions.h"
unsigned int key_lut[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','=','-'}};
void keypad_init(void)
{
	IODIR1|=0x0f<<ROW0;         //set rows pins as output
	//default column pins as input
}
unsigned int colscan(void)
{
	unsigned int status;
	status=((READNIBBLE(IOPIN1,COL0))<15)?0:1;    //checking status of the columns
	return status;
}

/*
checking the status of each row to configure which button is pressed
*/
unsigned int rowcheck(void)
{
	unsigned int r;
	for(r=0;r<4;r++)
	{
		IOPIN1=(IOPIN1&~(15<<ROW0))|((~(1<<r))<<ROW0);     //keeping each row everytime as ground
		if(colscan()==0)
			break;
	}
		WRITENIBBLE(IOPIN1,ROW0,0);                       //keep all rows in ground state
		return r;
}

 /*
checking the status of each column to configure which button is pressed
*/
unsigned int colcheck(void)
{
	unsigned int c;
	for(c=0;c<4;c++)
	{
		if((READBIT(IOPIN1,COL0+c))==0)      
		{
			break;
		}
	}
	return c;
}
/*

when button is pressed it checks the row and 
column of pressed button and return the character 
from look_up table.
*/
unsigned int keyscan(void)
{
	unsigned int key,r,c;
	while(colscan());
	r=rowcheck();
	c=colcheck();
	key=key_lut[r][c];
	return key;
}
