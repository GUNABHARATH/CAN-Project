#include<lpc21xx.h>
#include"spi.h"//SPI Header 
#include"CAN_Tx.h"//CAN Transmitter Header
#include"uart2.h"//UART Header used UART1
#include"lcd_4bit_base.h"//LCD 4bit Header

int main()
{
 int i;
 float f=0;
 char*s;
 can2_msg A;
 can2_init();
 uart_config();
 spi_init();
 LCD_INIT();
 LCD_CMD(0x80);
 LCD_String("VOLTAGE:");
 UART_STRING("START:\n\r");
 UART_STRING("\n\rVOLTAGE:");
 f*=100;//float value to integer(Ex:3.33->333)
 i=f;
 uart_float(f/100);
 //UART_STRING(s);
 IOPIN0 = 1<<7;
 A.msg_id=0x0b;
 A.rtr=0;//RTR=0 because Data Frame//RTR=1 means Remote Frame
 A.dlc=4;//Sending only 4 Bytes of Data
 A.lbyte=i;//lowest Byte
 A.hbyte=0;//Highest Byte
 while(1)
{
 f=0;
 f=adc_read(0);//Reading ADC data through SPI
 //f=2.05;
 f*=100;
 i=f;
 LCD_CMD(0xC0);
 LCD_Celsius(i);
 UART_STRING(" \r\nVOLTAGE:");
 uart_float(f/100);
 //i*=100;
 A.lbyte=i;//Assigning the data to lbyte as integer(4bytes)
 //f=A.lbyte;
 can2_tx(A);//Transmitting the Data through CAN to the Receiver
 delay_ms(500);
 LCD_CMD(0xC0);
 LCD_String("                ");
 UART_STRING(" \n\r");
}
}

