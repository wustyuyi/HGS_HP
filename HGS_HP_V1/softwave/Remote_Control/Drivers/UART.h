#ifndef _UART_H
#define _UART_H



#define  RINGBUFF_LEN   200     //定义最大接收字节数 50
typedef struct
{
  uint16_t Head;           
  uint16_t Tail;
  uint16_t Lenght;
  uint8_t  Ring_Buff[RINGBUFF_LEN];
}RingBuff_t;

#define USER_RINGBUFF  1  //使用环形缓冲区形式接收数据
#if  USER_RINGBUFF
/**如果使用环形缓冲形式接收串口数据***/
void RingBuff_Init(RingBuff_t *ringBuff);
u8 Write_RingBuff(uint8_t data,RingBuff_t *ringBuff);
u8 Read_RingBuff(uint8_t *rData,RingBuff_t *ringBuff);
#endif


void RingBuf_Write(unsigned char data,RingBuff_t *ringBuff,uint16_t Length);
u8 RingBuf_Read(unsigned char* pData,RingBuff_t *ringBuff);





void USART1_Init(unsigned long bound);
void UART1_Send(unsigned char tx_buf);
void USART1_Send(unsigned char *tx_buf, int len);
void USART1_Send_Dma(uint8_t *dma_buf,uint16_t dma_cnt);



void USART3_Init(unsigned long bound);
void UART3_Send(unsigned char tx_buf);
void USART3_Send(unsigned char *tx_buf, int len);	
void USART3_Isr_Init(void);


extern unsigned char Transparent_Data[128];
extern unsigned char Transparent_Update,Transparent_Cnt;


extern RingBuff_t COM3_Rx_Buf;


#endif




