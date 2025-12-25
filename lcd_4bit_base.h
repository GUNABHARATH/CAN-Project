#include<LPC21xx.h>
#define LCD_D 0xF<<14//d4 to d7 --->14 to 17
#define RS 1<<12
#define E 1<<13
#define LED 1<<0
void delay_ms(int);
void LCD_INIT(void);
void LCD_Integer(int n);
void LCD_Celsius(int );
void LCD_SCelsius(float);
void LCD_Float(float );
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_String(unsigned char *);
void delay_ms(int ms)
{
	T0PR=60000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}
void LCD_String(unsigned char *s)
{
while(*s)
{
LCD_DATA(*s++);
}
}
void LCD_Celsius(int f)
{
/*int n,h,l;
h=f;
f=f-h;
l=f*100;
h=h*100;
n=h+l;*/
LCD_Integer(f);
LCD_CMD(0xC3);
LCD_String("*C");
}
void LCD_SCelsius(float f)
{
int n,h,l;
h=f;
f=f-h;
l=f*100;
h=h*100;
n=h+l;
LCD_Integer(n);
LCD_CMD(0xC3);
LCD_String("*C");
}
void LCD_Float(float f)
{
int n=f;
LCD_Integer(n);
LCD_DATA('.');
f=f-n;
n=f*100;
LCD_Integer(n);

}
void LCD_Integer(int n)
{
unsigned char arr[5];
signed char i=0;
if(n==0)
{
LCD_DATA('0');
}
else
{ if(n<0)
{
LCD_DATA('-');
n = -n;
}

while(n>0)
{
arr[i++] = n%10;
n = n/10;
}
for(i=i-1;i>=0;i--)	{
LCD_DATA(arr[i]+48);
}
}
}
void LCD_INIT(void)
   {
   IODIR0 |= LCD_D|RS|E|LED;
   LCD_CMD(0x01);
   LCD_CMD(0x02);
   LCD_CMD(0x0C);
   LCD_CMD(0x28);
   }
   void LCD_CMD(unsigned char cmd)
   {
   IOCLR0 = LCD_D;
   IOSET0 = (cmd&0xf0)<<10;
   IOCLR0 = RS;
   IOSET0 = E;
   delay_ms(2);
   IOCLR0 = E;

   IOCLR0 = LCD_D;
   IOSET0 = (cmd&0x0f)<<14;
   IOCLR0 = RS;
   IOSET0 = E;
   delay_ms(2);
   IOCLR0 = E;
   }
   void LCD_DATA(unsigned char d)
   {
   IOCLR0 = LCD_D;
   IOSET0 = (d&0xf0)<<10;
   IOSET0 = RS;
   IOSET0 = E;
   delay_ms(2);
   IOCLR0 = E;


   IOCLR0 = LCD_D;
   IOSET0 = (d&0x0f)<<14;
   IOSET0 = RS;
   IOSET0 = E;
   delay_ms(2);
   IOCLR0 = E;
   }
