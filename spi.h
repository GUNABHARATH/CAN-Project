#include<LPC21xx.h>


void spi_init(void);
unsigned char spi_data(unsigned char);
float adc_read(unsigned char);

void spi_init()
{
PINSEL0|= 0x1500;
S0SPCCR = 150;
S0SPCR = 1<<5|3<<3;
IODIR0 = 1<<7;
}
unsigned char spi_data(unsigned char data)
{
S0SPDR = data;
while(!((S0SPSR>>7)&1));
return S0SPDR;
}
float adc_read(unsigned char ch)
{
unsigned char hByte,lByte;
unsigned int adcval = 0;
IOCLR0 = 1<<7;
spi_data(0x06);
hByte = spi_data(ch<<6);
lByte = spi_data(0x00);
IOSET0 = 1<<7;
adcval = ((hByte&0x0F)<<8)|lByte;
return ((adcval * 3.3)/4096);
}
