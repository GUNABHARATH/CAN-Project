#include<lpc21xx.h>
#include"CAN_Rx.h"//CAN Receiver Header
#define M 1<<0

int main()
{
 can2_msg_rx m1;
 can2_init_rx();
 IODIR0|=M;
 IOSET0 = M;
 while(1)
 {
   can2_rx(&m1);//Receiving data from Master Node
   if(m1.id==0x0c)
   {
    if(m1.lbyte==1)
	{
	  IOCLR0 = M;//Motor ON or Buzzer ON
	}
	else
	IOSET0 = M;
	m1.lbyte=0;
   }
 }
}
