#include<LPC21xx.h>
typedef unsigned int u8;

typedef struct can
{
  u8 id;
  u8 rtr;
  u8 dlc;
  u8 lbyte;
  u8 hbyte;
}can2_msg_rx;
void can2_init_rx(void)
{
PINSEL1|=1<<14|1<<16;
VPBDIV=1;
C2MOD=0x01;
AFMR=0x02;
C2BTR|=0x1d;
C2MOD=0x00;
}
void can2_rx(can2_msg_rx *m1)
{
   while((C2GSR&0x01)==0);
   m1->id=C2RID;
   m1->dlc=((C2RFS>>16)&0x0f);
   m1->rtr=	 ((C2RFS>>30)&0x1);
   if(m1->rtr==0)
   {
	 m1->lbyte=C2RDA;
	 m1->hbyte=C2RDB;
   }
   C2CMR=1<<2;


}
