#include<LPC21xx.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
void uart_config(void);

void uart_tx(unsigned char);
void Uart_Integer(int );
unsigned char uart_rx(void);
void UART_hex( int);
void UART_STRING( unsigned char *);
void uart_float(float);

void uart_config(void)

{

PINSEL0|=1<<16|1<<18;

U1LCR=0x83;

U1DLL=32;

U1DLM=0;

U1LCR=0x03;

}

void uart_tx(unsigned char d)

{

while(((U1LSR>>5)&1)==0);

U1THR=d;

}

/*unsigned char uart_rx(void)

{

while((U1LSR&1)==0);

return U1RBR;

}*/


void UART_hex( int m1)

{
unsigned char *a;
sprintf(a,"%x",m1);
UART_STRING(a);

}

void uart_float(float f)
{
/*unsigned char*buf;
sprintf(buf, "%f", f);
UART_STRING(buf);
return buf;*/
int n=f;
Uart_Integer(n);
uart_tx('.');
f=f-n;
n=f*100;
Uart_Integer(n);
n=n*10;
Uart_Integer(n);
}
void Uart_Integer(int n)
{
unsigned char arr[5];
signed char i=0;
if(n==0)
{
uart_tx('0');
}
else
{ if(n<0)
{
uart_tx('-');
n = -n;
}
while(n>0)
{
arr[i++] = n%10;
n = n/10;
}
for(i=i-1;i>=0;i--)	{
uart_tx(arr[i]+48);
}
}
}

void UART_STRING( unsigned char *s)

{

while(*s)

{

uart_tx(*s);

s++;

}

}

