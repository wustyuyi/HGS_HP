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
#include "sbus.h"

#define LEN_DMA_RECV_BUF 256
u8 dma_send_buf[LEN_DMA_RECV_BUF];


void sbus_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO
                         |RCC_APB2Periph_GPIOA , ENABLE);//串口2
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//串口2 低速
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  USART_InitStructure.USART_BaudRate = 100000;//
  USART_InitStructure.USART_WordLength = USART_WordLength_9b;//8bits
  USART_InitStructure.USART_StopBits = USART_StopBits_2;//stop bit is 1
  USART_InitStructure.USART_Parity = USART_Parity_Even;//no parity
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//no Hardware Flow Control
  USART_InitStructure.USART_Mode = USART_Mode_Tx;//enable tx and rx
  USART_Init(USART2, &USART_InitStructure);//
  
//  NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC初始化结构体
//  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口中断2
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure); 

	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel7);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)dma_send_buf;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 0;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel7, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel7, DISABLE);
	DMA_ClearFlag(DMA1_FLAG_GL7);

  USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);//rx interrupt is enable
  USART_Cmd(USART2, ENABLE);
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
}


void USART2_Send(unsigned char *tx_buf, int len)
{
  USART_ClearFlag(USART2, USART_FLAG_TC);
  USART_ClearITPendingBit(USART2, USART_FLAG_TXE);
  while(len--)
  {
    USART_SendData(USART2, *tx_buf);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != 1);
    USART_ClearFlag(USART2, USART_FLAG_TC);
    USART_ClearITPendingBit(USART2, USART_FLAG_TXE);
    tx_buf++;
  }
}


void USART2_Send_DMA(u8 *bytes, u8 bytes_len)
{
	DMA_Cmd(DMA1_Channel7, DISABLE);
	memcpy(dma_send_buf, bytes, bytes_len);
	DMA_SetCurrDataCounter(DMA1_Channel7, bytes_len);
	DMA_Cmd(DMA1_Channel7, ENABLE);
	//while(DMA_GetCurrDataCounter(DMA1_Channel7));
	//while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);
}


void UART2_Send(unsigned char tx_buf)
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);//这里跟分析fputc时是一样的
  USART_SendData(USART2 , tx_buf);//发送字符数组里的单个字符
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);
}



void USART2_IRQHandler(void)//解析GPS输出的UBLOX  PVT协议
{
  //unsigned char ch;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  { 
		//ch=USART_ReceiveData(USART2);
	}
}

systime  sbus_dealt;
uint16_t channels[16]={0};
uint8_t packet[25];
void sbus_output()
{
	  Get_Systime(&sbus_dealt);
		uint8_t stateByte = 0x00;
		if(nrf_sbus_update==0) 
		{
			stateByte |= SBUS_STATE_SIGNALLOSS;
		}
		if(nrf_soft_rssi<30)//信号强度30% 
		{
			stateByte |= SBUS_STATE_FAILSAFE;
		}
		for(uint16_t i=0;i<16;i++)
		{
			channels[i]=(uint16_t)((float)(RC_Data.rcdata[i]-SBUS_SCALE_OFFSET)/SBUS_SCALE_FACTOR+0.5f);
		}
				
    packet[0] = SBUS_FRAME_HEADER; 
		packet[1] = (uint8_t) (channels[0] & 0x07FF);
    packet[2] = (uint8_t) ((channels[0] & 0x07FF)>>8 | (channels[1] & 0x07FF)<<3);
    packet[3] = (uint8_t) ((channels[1] & 0x07FF)>>5 | (channels[2] & 0x07FF)<<6);
    packet[4] = (uint8_t) ((channels[2] & 0x07FF)>>2);
    packet[5] = (uint8_t) ((channels[2] & 0x07FF)>>10 | (channels[3] & 0x07FF)<<1);
    packet[6] = (uint8_t) ((channels[3] & 0x07FF)>>7 | (channels[4] & 0x07FF)<<4);
    packet[7] = (uint8_t) ((channels[4] & 0x07FF)>>4 | (channels[5] & 0x07FF)<<7);
    packet[8] = (uint8_t) ((channels[5] & 0x07FF)>>1);
    packet[9] = (uint8_t) ((channels[5] & 0x07FF)>>9 | (channels[6] & 0x07FF)<<2);
    packet[10] = (uint8_t) ((channels[6] & 0x07FF)>>6 | (channels[7] & 0x07FF)<<5);
    packet[11] = (uint8_t) ((channels[7] & 0x07FF)>>3);
    packet[12] = (uint8_t) ((channels[8] & 0x07FF));
    packet[13] = (uint8_t) ((channels[8] & 0x07FF)>>8 | (channels[9] & 0x07FF)<<3);
    packet[14] = (uint8_t) ((channels[9] & 0x07FF)>>5 | (channels[10] & 0x07FF)<<6);  
    packet[15] = (uint8_t) ((channels[10] & 0x07FF)>>2);
    packet[16] = (uint8_t) ((channels[10] & 0x07FF)>>10 | (channels[11] & 0x07FF)<<1);
    packet[17] = (uint8_t) ((channels[11] & 0x07FF)>>7 | (channels[12] & 0x07FF)<<4);
    packet[18] = (uint8_t) ((channels[12] & 0x07FF)>>4 | (channels[13] & 0x07FF)<<7);
    packet[19] = (uint8_t) ((channels[13] & 0x07FF)>>1);
    packet[20] = (uint8_t) ((channels[13] & 0x07FF)>>9 | (channels[14] & 0x07FF)<<2);
    packet[21] = (uint8_t) ((channels[14] & 0x07FF)>>6 | (channels[15] & 0x07FF)<<5);
    packet[22] = (uint8_t) ((channels[15] & 0x07FF)>>3);
    packet[23] = 0x00;
    packet[24] = SBUS_FRAME_FOOTER;	
    //USART2_Send(packet,25);
		USART2_Send_DMA(packet,25);
		nrf_sbus_update=0;
}


