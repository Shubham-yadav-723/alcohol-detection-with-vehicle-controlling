#include<reg51.h>

//for lcd screen
sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;

//for gas sensor
sbit sensor=P1^7;

//for engine
sbit motor=P0^7;

//for buzzer
sbit buzzer=P3^0;

//function declaration for lcd screen
void lcdinit();
void lcdcmd(unsigned char);
void lcddat(unsigned char );
void lcddis(unsigned char *);
void delay();
void main()
{
	sensor=1;
	buzzer=0;
	motor=0x09;
	lcdinit();
	lcddis("WELCOME BACK TO  ");
	lcdcmd(0xc0);
	lcddis("THE CAR SIR");
	delay();
	
	while(1)
	{
	
		if(sensor==1)                          //alcohol detected
		{
		
			back3:lcdcmd(0x01);                  //clearing the screen
			lcddis("ALCOHOL DETECTED");
			lcdcmd(0x01);
	   lcddis("TURNING OFF THE");
			lcdcmd(0xc0);                       //cursor on next line
			lcddis("ENGINE!!!!");
			motor=0x09;                         //engine stopped
			buzzer=1;                           //buzzer turns on
			back:lcdcmd(0x01);
			lcddis("ENGINE TURNED");
				lcdcmd(0xc0);
			lcddis("OFF....");
			if(sensor==0)                       //no alcohol
			{ 
				buzzer=0;                         //buzzer off
				lcdcmd(0x01);
				lcddis("TURNING ON THE ");
				lcdcmd(0xc0);
				lcddis("ENGINE AGAIN..");
			
				goto back1;
			}
			goto back;
			
			
			
			
		  
			
		}
		if(sensor==0)                              
		{
			back1:motor=0x00;
			buzzer=0;
			lcdcmd(0x01);
			lcddis("HAPPY JOURNEY");
			back2:lcdcmd(0x01);
			lcddis("NO ALCOHOL ");
			lcdcmd(0xC0);
	   lcddis("DETECTED...");
			lcdcmd(0x01);
			lcddis("KEEP GOING..");
			if(sensor==1)
			{
			 goto back3;
			}
			goto back2;
		
		}
		
	
		
		
		
	}
}


//initialization of lcd
void lcdinit()
{
	lcdcmd(0x38);
	lcdcmd(0x01);
	lcdcmd(0x10);
	lcdcmd(0x0c);
	lcdcmd(0x80);
	
}

//command function for lcd 
void lcdcmd(unsigned char val)
{
	P2=val;
	rs=0;
	rw=0;
	en=1;
	delay();
	en=0;
	
}

// function for sending the data on lcd screen
void lcddat(unsigned char dat)
{
	P2=dat;
	rs=1;
	rw=0;
	en=1;
	delay();
	en=0;
	
}


// function for displaying the message on lcd screen
void lcddis(unsigned char *s)
{
	unsigned char w;
	for(w=0;s[w]!='\0';w++)
	{
		lcddat(s[w]);
	}
}
	
void delay()
{
	unsigned int i;
	for(i=0;i<8000;i++);
	
}