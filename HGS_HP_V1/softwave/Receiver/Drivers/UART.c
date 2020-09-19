/* Copyright (c)  2020-2030 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                开源并不等于免费，先驱者的历史已经证明，在国内这个环境下，毫无收益的开源，单靠坊间个人爱好者，自发地参与项
								目完善的方式行不通，好的开源项目需要请专职人员做好售后服务、手把手教学、统计用户反馈需求、在实践中完成对产
								品的一次次完善与迭代升级。经过综合考虑，无名飞控开源代码中，程序仅保留公司正版激活功能代码，版本激活无实际
								功能，属于公司产品常规出厂操作，不影响客户学习，其余代码全部开放给客户学习，客户移植和二次开发代码请保留代
								码版权。
-----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------
*                                                 为什么选择无名创新？
*                                         感动人心价格厚道，最靠谱的开源飞控；
*                                         国内业界良心之作，最精致的售后服务；
*                                         追求极致用户体验，高效进阶学习之路；
*                                         萌新不再孤单求索，合理把握开源尺度；
*                                         响应国家扶贫号召，促进教育体制公平；
*                                         新时代奋斗最出彩，建人类命运共同体。 
-----------------------------------------------------------------------------------------------------------------------
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：2号群465082224、1号群540707961（人员已满）
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               公司官网:www.nameless.tech
*               无名创新国内首款TI开源飞控设计初衷、知乎专栏:https://zhuanlan.zhihu.com/p/54471146
*               修改日期:2020/09/01                  
*               版本：追梦者RC——OPENRC_DT_V1.0.1
*               版权所有，盗版必究。
*               Copyright(C) 2020-2030 武汉无名创新科技有限公司 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               重要提示：
*               正常淘宝咸鱼转手的飞控、赠送朋友、传给学弟的都可以进售后群学习交流，
*               不得直接在网上销售无名创新资料，无名创新代码有声明版权，他人不得将
*               资料代码传网上供他人下载，不得以谋利为目的销售资料代码，发现有此操
*               作者，公司会提前告知，请1天内及时处理，否则你的学校、单位、姓名、电
*               话、地址信息会被贴出在公司官网、官方微信公众平台、官方技术博客、知乎
*               专栏以及淘宝店铺首页予以公示公告，此种所作所为，会成为个人污点，影响
*               升学、找工作、社会声誉、很快就很在无人机界出名，后果很严重。
*               因此行为给公司造成重大损失者，会以法律途径解决，感谢您的合作，谢谢！！！
----------------------------------------------------------------------------------------------------------------------*/
#include "main.h"
#include "UART.h"

#define USART1_RX_BUFFER_SIZE  128
u8 receive_data[USART1_RX_BUFFER_SIZE ];
void DMA_init(void)
{
   DMA_InitTypeDef    DMA_Initstructure;
   /*开启DMA时钟*/
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
   /*DMA配置*/
   DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&USART1->DR);;
   DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)receive_data;
   DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;
   DMA_Initstructure.DMA_BufferSize = USART1_RX_BUFFER_SIZE;
   DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;
   DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;
   DMA_Initstructure.DMA_Priority = DMA_Priority_VeryHigh;//DMA_Priority_High;
   DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(DMA1_Channel5,&DMA_Initstructure);
	 
	 DMA_ClearFlag(DMA1_FLAG_TC5);
	 DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE);
	 DMA_Cmd(DMA1_Channel5,ENABLE);  
}



void USART1_Init(unsigned long bound)
{
  NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC初始化结构体
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  USART_InitStructure.USART_BaudRate = bound;//
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8bits
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//stop bit is 1
  USART_InitStructure.USART_Parity = USART_Parity_No;//no parity
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//no Hardware Flow Control
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//enable tx and rx
  USART_Init(USART1, &USART_InitStructure);//
  
  //USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//rx interrupt is enable	
  //USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1,USART_IT_IDLE, ENABLE);//开启检测串口空闲状态中断
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//-------USART_DMACmd(LUMMOD_UART, USART_DMAReq_Rx, ENABLE); // 开启串口DMA接收
	USART_Cmd(USART1,ENABLE);
	DMA_init();	
  
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级组别2，具体参见misc.h line80
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口中断1、对应山外上位机、主串口
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void UART1_Send(unsigned char tx_buf)
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);//这里跟分析fputc时是一样的
  USART_SendData(USART1 , tx_buf);//发送字符数组里的单个字符
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
}

void USART1_Send(unsigned char *tx_buf, int len)
{
  USART_ClearFlag(USART1, USART_FLAG_TC);
  USART_ClearITPendingBit(USART1,USART_FLAG_TXE);
  while(len--)
  {
    USART_SendData(USART1, *tx_buf);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != 1);
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_ClearITPendingBit(USART1, USART_FLAG_TXE);
    tx_buf++;
  } 
}


//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
//#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
    
void _sys_exit(int x) { x = x; }//定义_sys_exit()以避免使用半主机模式 

int fputc(int ch, FILE *f)//重定义fputc函数 
{      
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
  return (ch);
}
#endif 


//void USART1_IRQHandler(void)
//{ 
//  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//  {
//    //NCLink_Data_Prase_Prepare(USART_ReceiveData(USART1));
//		//NRF_TxPacket_AP(buf,cnt);
//    USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//  }
//}

//u8 rxd1_buf[512];			//接收数组
//u8 rxd1_len;				//接收数据长度
//u8 rxd1_flag;				//接收标志

//void USART1_IRQHandler(void)                	
//{
//	u8 clear = clear;	//这样定义避免弹出clear定义了没使用的警告
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)		//接收中断
//	{
//		//if(rxd1_len<32)
//		{
//			rxd1_buf[rxd1_len++] = USART1->DR;						//把接收到的数据存到rxd1_buf数组
//		}
//		//else
//		{
//			//clear = USART1->DR;
//		}
//  }
//	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)	//串口线空闲了说明一包数据接收完了
//	{
//		clear = USART1->SR;										//读寄存器就等于清寄存器
//		clear = USART1->DR;										//读寄存器就等于清寄存器
//		rxd1_flag = 1;											  //串口接收标志位置1
//		
////		NRF_TxPacket_AP(rxd1_buf, rxd1_len);//NRF24L01发送数据
////		rxd1_len = 0;												//接收数据长度置0
////		rxd1_flag = 0;									  	//串口接收标志位置0
//		
//		if(rxd1_flag==1)
//		{
//			NRF_TxPacket_AP(rxd1_buf, rxd1_len);						//NRF24L01发送数据
//			rxd1_len = 0;											//接收数据长度置0
//			rxd1_flag = 0;									  //串口接收标志位置0
//		}
//		
//	}
//	USART_ClearITPendingBit(USART1,USART_IT_ORE);				//清除USART1_ORE标志位
//}





void USART1_IRQHandler(void)
{
	unsigned char num=0;
	if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)
	{
		 num = USART1->SR;
		 num = USART1->DR; //清USART_IT_IDLE标志
		 DMA_Cmd(DMA1_Channel5,DISABLE);    //关闭DMA
		
//		DMA_ClearITPendingBit(DMA1_IT_TC2);	// Clear Transfer Complete flag
//		DMA_ClearITPendingBit(DMA1_IT_TE2);	// Clear Transfer error flag

		 num = 128 -  DMA_GetCurrDataCounter(DMA1_Channel5);//得到真正接收数据个数  
		 //receive_data[num] = '\0';
		 DMA1_Channel5->CNDTR=USART1_RX_BUFFER_SIZE;//重新设置接收数据个数
		 DMA_Cmd(DMA1_Channel5,ENABLE);  //开启DMA
		 //printf("%s ",receive_data );
     NRF_TxPacket_AP(receive_data, num);//NRF24L01发送数据		
		 //NRF24L01_TxPacket(receive_data, num);
	}
}














DMA_InitTypeDef DMA_InitStructure;
uint16_t DMA1_MEM_LEN;//保存DMA每次数据传送的长度
/*
DMA1的各通道配置这里的传输形式是固定的,这点要根据不同的情况来修改
从存储器->外设模式/8位数据宽度/存储器增量模式
DMA_CHx:DMA通道CHx      cpar:外设地址
cmar:存储器地址         cndtr:数据传输量
*/
void Quad_DMA_Config(DMA_Channel_TypeDef* DMA_CHx,uint32_t cpar,uint32_t cmar,uint16_t cndtr)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
  DMA_DeInit(DMA_CHx);   											        //将DMA的通道1寄存器重设为缺省值
  DMA1_MEM_LEN=cndtr;
  DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设基地址
  DMA_InitStructure.DMA_MemoryBaseAddr =cmar;				//DMA内存基地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//外设作为数据传输的目的地
  DMA_InitStructure.DMA_BufferSize = cndtr;  												//DMA通道的DMA缓存的大小
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  					//内存地址寄存器递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//数据宽度为8位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        //数据宽度为8位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  									       //工作在正常缓存模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                  //DMA通道 x拥有中优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                           //DMA通道x没有设置为内存到内存传输
  DMA_Init(DMA_CHx, &DMA_InitStructure);//根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
}

void Quad_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx)//开启一次DMA传输
{
  DMA_Cmd(DMA_CHx, DISABLE );
  //关闭USART1 TX DMA1所指示的通道
  DMA_InitStructure.DMA_BufferSize =DMA1_MEM_LEN;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  DMA_Cmd(DMA_CHx, ENABLE);  //使能USART1 TX DMA1 所指示的通道
}

void Quad_DMA1_USART1_SEND(u32 SendBuff,u16 len)//DMA---USART1传输
{
  Quad_DMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,len);//DMA1通道4,外设为串口1,存储器为SendBuff,长度len.
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  Quad_DMA_Enable(DMA1_Channel4);
  //while(DMA_GetFlagStatus(DMA1_FLAG_TC4) != SET);
  //DMA_ClearFlag(DMA1_FLAG_TC4);//清除发送完成标志
}

void USART1_Send_Dma(uint8_t *dma_buf,uint16_t dma_cnt)
{
	Quad_DMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)dma_buf,dma_cnt);//DMA1通道4,外设为串口1,存储器为dma_buf,长度dma_cnt
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  Quad_DMA_Enable(DMA1_Channel4);
}



#define USART3_RX_BUFFER_SIZE  128
u8 receive_data3[USART3_RX_BUFFER_SIZE ];


void USART3_DMA_Init()
{
	DMA_InitTypeDef DMA_InitStructure;	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                      //使能DMA1时钟  
	DMA_DeInit(DMA1_Channel3);                                              //初始化DMA1通道3  串口3接收通道
	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40004804;                  //串口3接收数据的地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)receive_data3;      //数据存放的复制
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      //数据传送方向  串口3作为数据源
	DMA_InitStructure.DMA_BufferSize = USART3_RX_BUFFER_SIZE;                    //接收数据个数       
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //外围设备 串口3 地址不递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // DMA存储地址递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外围设备 串口3 数据宽度 8bits
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //DMA存储 数据宽度 8bits
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         //循环获取数据
	//DMA_Mode_Normal（只传送一次）, DMA_Mode_Circular （不停地传送）
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   //串口3通道优先为中等
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            //关闭内存到内存
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);
	 
	 
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);  //使能串口3 DMA功能
	DMA_Cmd(DMA1_Channel3, ENABLE);
} 
 

void USART3_Init(unsigned long bound)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = bound;//
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8bits
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//stop bit is 1
  USART_InitStructure.USART_Parity = USART_Parity_No;//no parity
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//no Hardware Flow Control
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//enable tx and rx
  USART_Init(USART3, &USART_InitStructure);//

	
	USART_ITConfig(USART3,USART_IT_TC,DISABLE);  //关闭发送中断 
	USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);//关闭接收中断  
	USART_ITConfig(USART3,USART_IT_IDLE,DISABLE); //开启总线空闲中断 
	USART_Cmd(USART3, ENABLE);	      // 使能 USART3
	//USART3_DMA_Init();	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}

void USART3_Send(unsigned char tx_buf)
{
  while(USART_GetFlagStatus(USART3, USART_FLAG_TC) != 1);
  USART_SendData(USART3, tx_buf);
  USART_ClearFlag(USART3, USART_FLAG_TC);
  USART_ClearITPendingBit(USART3, USART_FLAG_TXE);
}
void UART3_Send(unsigned char *tx_buf, int len)
{
  USART_ClearFlag(USART3, USART_FLAG_TC);
  USART_ClearITPendingBit(USART3, USART_FLAG_TXE);
  while(len--)
  {
    USART_SendData(USART3, *tx_buf);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TC) != 1);
    USART_ClearFlag(USART3, USART_FLAG_TC);
    USART_ClearITPendingBit(USART3, USART_FLAG_TXE);
    tx_buf++;
  }
}



void USART3_IRQHandler(void)                	
{
	unsigned char num=0;
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)		//串口3	总线空闲	
	{
  	USART_ClearITPendingBit(USART3, USART_IT_IDLE);  //清除标记位
		DMA_Cmd(DMA1_Channel3, DISABLE);//关闭DMA1通道3
    num = USART3_RX_BUFFER_SIZE -  DMA_GetCurrDataCounter(DMA1_Channel3);//得到真正接收数据个数 
		DMA1_Channel3->CNDTR=USART3_RX_BUFFER_SIZE;//重新设置接收数据个数//DMA_SetCurrDataCounter(DMA1_Channel3,GPS_Rev_Buf_Size);  //接收数据个数 
		DMA_Cmd(DMA1_Channel3, ENABLE);                          //开启DMA1通道3
    NRF_TxPacket_AP(receive_data3, num);//NRF24L01发送数据		
	}	
}

