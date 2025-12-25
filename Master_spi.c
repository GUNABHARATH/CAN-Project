#include<lpc21xx.h>
#include"CAN_Rx.h"//CAN Receiver Header
#include"CAN_Tx.h"//CAN Transmitter Header
#include"lcd_4bit_base.h"//LCD 4bit Header
#include"uart2.h"//LCD 4bit Header

int main()
{
 float f =0;
 int i=0;
 can2_msg_rx m1;
 can2_msg A;
 can2_init();
 LCD_INIT();
 LCD_CMD(0x80);
 LCD_String("     BATTERY");
 LCD_CMD(0xC0);
 LCD_String("   MANAGEMENT ");
 delay_ms(5000);
 LCD_CMD(0x01);
 LCD_CMD(0x80);
 LCD_String("VOLTAGE:");
 can2_init_rx();
 uart_config();
 //LCD_INIT();
 UART_STRING("HELLO\r\n");
 //UART_STRING("i=");   
 //Uart_Integer(i);
 f=i;
 uart_float(f/100);
 //UART_STRING("\n\r");
 f/=100;
 LCD_CMD(0xC0);
 LCD_Celsius(i);
 IOSET0 = LED;
 A.msg_id=0x0c;
 A.rtr=0;
 A.dlc=4;
 A.lbyte=0;
 A.hbyte=0;
 while(1)
{
  LCD_CMD(0xC0);
  LCD_Celsius(i);
  can2_rx(&m1);//CAN waiting to Receive
  //UART_hex(m1.id);
  //uart_tx(' ');
  if(m1.id==0x0b)
  {
  //UART_hex(m1.rtr);
  //uart_tx(' ');
  //UART_hex(m1.dlc);
  //uart_tx(' ');
  i=m1.lbyte;//Reading the value lbyte
  f=0;
  f=i;
  if(i>70)//Calculating the value and sending data to send to other Nodes
  {
  A.lbyte=1;
  can2_tx(A);
  IOCLR0 = LED;
  }
  else
  {
  A.lbyte=0;
  can2_tx(A);
  IOSET0 = LED;
  }//f/=100;
  //uart_float(f);
  //uart_tx(' ');
  //UART_hex(m1.hbyte);
  //uart_tx(' ');
  UART_STRING("\r\n");
  delay_ms(500);
  //LCD_CMD(0xC0);
  //LCD_String("                ");
  } 
 LCD_CMD(0xC0);
 LCD_String("                ");
  
}
}
