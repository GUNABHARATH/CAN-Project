#include<LPC21xx.h>
typedef unsigned int u8;

typedef struct can_2
{
   u8 msg_id;
   u8 rtr;
   u8 dlc;
   u8 lbyte;
   u8 hbyte;
}can2_msg;
void can2_init(void)
{
PINSEL1|=1<<14|1<<16;
VPBDIV=1;
C2MOD=0x01;
AFMR=0x02;
C2BTR|=0x1d;
C2MOD=0x00;
}
void can2_tx(can2_msg A)
{
C2TID1=A.msg_id;
C2TFI1=(A.dlc<<16);
if(A.rtr==0)
{ 
C2TFI1&=~(1<<30);	//RTR=0;
C2TDA1=A.lbyte;
C2TDB1=A.hbyte; 
}
else
C2TFI1=1<<30;		  //RTR=1;

C2CMR=1<<0|1<<5;
while(((C2GSR>>3)&1)==0);

}
								

															