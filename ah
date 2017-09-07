#include<STC15F2K60S2.h> //@22.1184MHz
#include <intrins.h>
sbit LED= P5^5;  //
sbit LCD_RS = P3^5;             
sbit LCD_RW = P3^6;
sbit LCD_EN = P3^7;
sbit qidong  = P3^4; 
sbit shoudong  = P3^3; 
sbit guangdian  = P3^2; 
sbit  ks  = P3^1;
sbit  kx  = P3^0; 
sbit  k1  = P5^5; 
sbit  bee  = P5^4; 

unsigned char  cs_flag;
unsigned int xqsj,cdsj,szsj;

unsigned char code lcdxs[]={"0123456789"};

void Open_IAP(void)
{

       EA=0;
       IAP_CONTR = 0x80;           //??ISP/IAP,????<20MHz?,??????WT2,WT1,WT0(010)

}

void Close_IAP(void)
{

       IAP_CONTR = 0x00;           //??ISP/IAP
       IAP_ADDRH = 0xFF;
       IAP_ADDRL = 0xFF;
       EA=1;

}

unsigned int Read_IAP_Byte(unsigned int addr)
{
   
       IAP_CMD = 0x01;
       IAP_ADDRH = (addr & 0xFF00)>>8;
       IAP_ADDRL = addr & 0x00FF;
       IAP_TRIG = 0x5A;
       IAP_TRIG = 0xA5;                     //?IAP_TRIG??0x5A??0xA5,ISP/IAP??????
       return IAP_DATA;

}

void Write_IAP_Byte(unsigned int addr, unsigned int writeVal)
{
       IAP_CMD = 0x02;

       IAP_ADDRH = (addr & 0xFF00)>>8;

       IAP_ADDRL = addr & 0x00FF;

 
       IAP_DATA = writeVal;

 
       IAP_TRIG = 0x5A;

       IAP_TRIG = 0xA5;                     //?IAP_TRIG??0x5A??0xA5,ISP/IAP??????

}

void Erase_IAP_Sector(unsigned int addr)
{

   
       IAP_CMD = 0x03;

       IAP_ADDRH = (addr & 0xFF00)>>8;

       IAP_ADDRL = addr & 0x00FF;

       IAP_TRIG = 0x5A;

       IAP_TRIG = 0xA5;                     //?IAP_TRIG??0x5A??0xA5,ISP/IAP??????

}

void Delayms(unsigned int n)  	//@22.1184MHz
{
        unsigned int x;
        while(n--)
        {
                x=1200;
                while(x--);
        }
}



void Iomode()
{
       P0M0 = 0x00;  P0M1 = 0x00;	P1M0 = 0x00; P1M1 = 0x00;
	     P2M0 = 0x00;  P2M1 = 0x00; P3M0 = 0x00; P3M1 = 0x00;   
       P4M0 = 0x00; P4M1 = 0x00;  P5M0 = 0x00;  P5M1 = 0x00;

}
	



void Delay20us()		//@22.1184MHz
{
	unsigned char i;

	i = 118;
	while (--i);
}

void Timer0Init(void)		//10us@22.1184MHz
{
	AUXR |= 0x80;		//
	TMOD &= 0xF0;		//
	TL0 = 0x23;		//
	TH0 = 0xFF;		//
	TF0 = 0;		//
	TR0 = 0;		//
}


void delayNOP()	//??
{
         _nop_();  _nop_();     
         _nop_();  _nop_();

}

bit lcd_busy() // mang 
{       
         bit result;
         LCD_RS = 0;
         LCD_RW = 1;
         LCD_EN = 1;
          delayNOP();
         result = (bit)(P0&0x80);
         LCD_EN = 0;
         return(result);
}

void lcd_wcmd(unsigned char cmd) // zhi ling  shu ju 
{       
        while(lcd_busy());
         LCD_RS = 0;
         LCD_RW = 0;
         LCD_EN = 0;
          _nop_();
          _nop_(); 
         P0 = cmd;
          delayNOP();
         LCD_EN = 1;
         delayNOP();
         LCD_EN = 0; 
}

void lcd_wdata(unsigned char dat) //  xian shi shu ju 
{                          
        while(lcd_busy());
          LCD_RS = 1;
         LCD_RW = 0;
         LCD_EN = 0;
         P0 = dat;
         delayNOP();
         LCD_EN = 1;
         delayNOP();
         LCD_EN = 0; 
}

void lcd_set_xy(unsigned char x,unsigned char y)
{
  unsigned char address;
	x=x--;
  if(y==1)
  {
    address=0x80+x; // 1
  } else {
    address=0xc0+x; // 2
  }
    Delayms(5);
	lcd_wcmd(address);
   
}

/*
void lcd_dis_pos(unsigned char pos) // wei zhi 
{       
          lcd_wcmd(pos | 0x80); //80+-
}
*/
void lcd_init()
{ 
        Delayms(15);                   
        lcd_wcmd(0x38);      //16*2,5*7,8
        Delayms(5);
        lcd_wcmd(0x38);         
        Delayms(5);
        lcd_wcmd(0x38);         
        Delayms(5);
        lcd_wcmd(0x0c);      //
        Delayms(5);
        lcd_wcmd(0x06);      //
        Delayms(5);
        lcd_wcmd(0x01);      //
        Delayms(5);
}

void exint0() interrupt 0       //INT0
{
  //  LED = !LED;
    xqsj++;
	if(xqsj>=6)
	{
	cdsj++;
		xqsj=0;
	}
	if(cdsj>=9999) cdsj=0;
  //  TR0 = 0;	//
	  cs_flag=1;
	  EX0=0;
	
	
	
}

void timer0() interrupt 1  //   
  {
		
	}

	
void display_set(unsigned int temp1 ) // set 
{
unsigned char q1,b1,s1,g1;
	q1=temp1/1000;
	b1=temp1%1000/100;
	s1=temp1%100/10;
  g1=temp1%10;	
		lcd_set_xy(8,1);
	  lcd_wdata(lcdxs[q1]);//q
	  Delayms(5);	
		lcd_set_xy(9,1);
	  lcd_wdata(lcdxs[b1]);//b
	  Delayms(5);
	  lcd_set_xy(10,1);
	  lcd_wdata(lcdxs[s1]);//s
	  Delayms(5);
		lcd_set_xy(11,1);
	  lcd_wdata(lcdxs[g1]);//g
    Delayms(5);
}

void display_gds(void)
{
		lcd_set_xy(4,1);lcd_wdata(0x53);Delayms(5);   //S
		lcd_set_xy(5,1);	lcd_wdata(0x65);Delayms(5); //e
		lcd_set_xy(6,1);lcd_wdata(0x74);Delayms(5);   //t
	  lcd_set_xy(7,1);	lcd_wdata(0x3a);Delayms(5); //:
		lcd_set_xy(12,1);	lcd_wdata(0x6d);Delayms(5); //m

			lcd_set_xy(4,2);lcd_wdata(0x4e);Delayms(5); //N
		  lcd_set_xy(5,2);	lcd_wdata(0x6f);Delayms(5); //o
			lcd_set_xy(6,2);lcd_wdata(0x77);Delayms(5); //w
    	lcd_set_xy(7,2);lcd_wdata(0x3a);Delayms(5);   //:
	  	lcd_set_xy(12,2);	lcd_wdata(0x6d);Delayms(5); //m
}

void display_now(unsigned int temp2 ) // now
{
unsigned char q2,b2,s2,g2;
	q2=temp2/1000;
	b2=temp2%1000/100;
	s2=temp2%100/10;
  g2=temp2%10;	
			lcd_set_xy(8,2);
	    lcd_wdata(lcdxs[q2]);//b
	    Delayms(5);
	  	lcd_set_xy(9,2);
	    lcd_wdata(lcdxs[b2]);//b
     	Delayms(5);
	    lcd_set_xy(10,2);
	    lcd_wdata(lcdxs[s2]);//s
	    Delayms(5);
		  lcd_set_xy(11,2);
	    lcd_wdata(lcdxs[g2]);//g
      Delayms(5);
}

	

void main(void)
{
  unsigned char rsj1,rsj2,rsj3,rsj4;
	unsigned char wsj1,wsj2,wsj3,wsj4;
	Delayms(500);
	Iomode();
	cdsj=0;
	Open_IAP();
  rsj1=Read_IAP_Byte(0X0001);
	rsj2=Read_IAP_Byte(0X0002);
	rsj3=Read_IAP_Byte(0X0003);
	rsj4=Read_IAP_Byte(0X0004);
  Close_IAP();
	szsj=rsj1*1000+rsj2*100+rsj3*10+rsj4;
	EA=0;
	Delay20us();//
 delayNOP();

	LED=0;
	cs_flag=0;
	IT0=0;//mode di 
	EX0=0; //zhong duan kai guan  

	TR0 = 0; // ding shi qi 0
	
	//EA=1; // zong zhong duan 

  lcd_init();
	display_gds();
display_set(szsj);
display_now(cdsj);

    while(1) 
 {
	
if(qidong==0)
{
k1=0;bee=1;
}	
if(cdsj>=szsj)
{
k1=1; bee=0;cdsj=0;
}

	if(ks==0)
	 {
	 szsj+=10;
	 if(szsj>=8000)szsj=8000;
	wsj1=szsj/1000;
	wsj2=szsj%1000/100;
	wsj3=szsj%100/10;
  wsj4=szsj%10;
	Open_IAP();
Erase_IAP_Sector(0x0001);
Write_IAP_Byte(0X0001, wsj1);
Write_IAP_Byte(0X0002, wsj2);
Write_IAP_Byte(0X0003, wsj3);
Write_IAP_Byte(0X0004, wsj4);
Close_IAP();
	 display_set(szsj);
 }	
	  if(kx==0)
	{
	 szsj-=10;
	 if(szsj<=0)szsj=0;
	wsj1=szsj/1000;
	wsj2=szsj%1000/100;
	wsj3=szsj%100/10;
  wsj4=szsj%10;
	Open_IAP();
Erase_IAP_Sector(0x0001);
Write_IAP_Byte(0X0001, wsj1);
Write_IAP_Byte(0X0002, wsj2);
Write_IAP_Byte(0X0003, wsj3);
Write_IAP_Byte(0X0004, wsj4);
 Close_IAP();
display_set(szsj);
 }	 
		 
display_now(cdsj);
}
}
