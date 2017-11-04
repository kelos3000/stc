#include<STC15F2K60S2.h>//STC15w408as 
#include "intrins.h" // 11.0592MHz   
unsigned char PWM_X,PWM_Y,Rxd_flag,Rxd_Count;
unsigned char xdata Rxd_Data[7];

void Delay(unsigned int ms)		//@11.0592MHz
{
	unsigned int  i, j;
	for(j=0;j<ms;j++)
	{
		i =600;
		while (--i);
	}
}

void Uart() interrupt 4 using 1
{
    if (RI)
    {
        RI = 0;   			
			Rxd_Data[Rxd_Count]=SBUF;
			 Rxd_Count++;
			if(Rxd_Count>=4)
				{
				Rxd_flag=1;
					Rxd_Count=0;
				}	
    }
    if (TI)
    {
        TI = 0;                
    }
}

void Rxd_Dispose(void)
{

if(Rxd_flag)
{
Rxd_flag=0;
if(Rxd_Data[0]==0xaa)
{
if(Rxd_Data[3]==0x55)
{
PWM_X=Rxd_Data[1];
PWM_Y=Rxd_Data[2];
}
}

}

}

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8
	AUXR |= 0x01;		//
	AUXR |= 0x04;		//
	T2L = 0xE0;		//22.1184MHz  T2L = 0xC0;  11.0592  T2L = 0xE0;
	T2H = 0xFE;		//22.1184MHz  T2H = 0xFD;  11.0592  T2H = 0xFE;
	AUXR |= 0x10;		//
}

void UARTSendByte(unsigned char Byte)//
{
SBUF=Byte; //
while(TI==0); //
TI=0; //
}


void InitIO()
{
  P1M0 = 0x00; P1M1 = 0x00; P3M0 = 0x00;  P3M1 = 0x00;P5M0 = 0x00;P5M1 = 0x00;
}

void PWM_Init(void)
{

	CMOD=0X08; //??????????,???=35M/256=22.8K*6
	CL=0;			// PCA?????
	CH=0;
	
	PCA_PWM0 = 0X00;
	CCAP0H=0;    // ???????0% H?????L?
	CCAP0L=0;
	CCAPM0=0x42;	// ???8?PWM??
	
	PCA_PWM1 = 0X00;
	CCAP1H=0;    // ???????0%
	CCAP1L=0;
	CCAPM1=0x42;	// ???8?PWM??
	
	//AUXR1=0X10;         //****************
	CR = 1;     //??PCA???
}

void main(void)
{
InitIO();
PWM_Init();
UartInit();
CCAP0H = CCAP0L = 128;   //y  
CCAP1H = CCAP1L = 128;   //x	
	PWM_Y=128;
	PWM_X=128; 
	Rxd_flag=0;
	Rxd_Count=0;
	EA=1;
	ES=1;

while(1)

{
	CCAP0H = CCAP0L = PWM_Y; 
	CCAP1H = CCAP1L = PWM_X; 
	 Rxd_Dispose();
}
}
