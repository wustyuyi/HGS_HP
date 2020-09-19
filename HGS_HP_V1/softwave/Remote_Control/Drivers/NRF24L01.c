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
*               版本：追梦者RC——OPENRC_HP_V1.0.1
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
#include "NRF24L01.h"

//-----NRF24L01发送接收地址-----//
const u8 TX_ADDRESS[TX_ADR_WIDTH] = {'M','A','T','C','H'}; //发送地址
const u8 RX_ADDRESS[RX_ADR_WIDTH] = {'M','A','T','C','H'}; //接收地址
u8 g_NRFRevData[RX_PLOAD_WIDTH]={0,0};//-----NRF24L01接收数据
u8 g_NRFSendData[TX_PLOAD_WIDTH]={0};//-----NRF24L01发送数据
pair_data rc_pair;
uint32_t cpu_id[3];

/********************************
函数名：void NRF24L01_Init(void)
说明：初始化24L01
入口：无
出口：无
备注：无
*********************************/
void NRF24L01_Init(void)
{
	NRF24L01_CE_L; 			//使能24L01
	NRF24L01_CSN_H;			//SPI片选取消  
}

/******************************
函数名：u8 NRF24L01_Check(void)
说明：检测24L01是否存在
入口：无
出口：u8
0，成功;
1，失败	
备注：无
*******************************/
u8 NRF24L01_Check(void)
{
	u8 buf[5] = {0XA5,0XA5,0XA5,0XA5,0XA5}, i;
	NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,buf,5);//写入5个字节的地址，TX_ADDR为地址，WRITE_REG_NRF为命令
	NRF24L01_Read_Buf(TX_ADDR,buf,5);//读出写入的地址  
	for (i = 0; i < 5; i++)
	if (buf[i] != 0XA5)
	break;
	if (i != 5)
	return 1;//检测24L01错误	
	return 0;//检测到24L01
}

/************************************************
函数名：void NRF24L01_Write_Reg(u8 reg, u8 value)
说明：SPI写寄存器
入口：u8 reg		寄存器地址
u8 value	需要写入的值
出口：无
备注：无
************************************************/
void NRF24L01_Write_Reg(u8 reg, u8 value)
{
	NRF24L01_CSN_L;                 	//使能SPI传输
	SPI2_ReadWriteByte(reg);			    //发送寄存器号，这里可以读取到寄存器的状态
	SPI2_ReadWriteByte(value);      		//写入寄存器的值
	NRF24L01_CSN_H;                 	//禁止SPI传输	   
}

/************************************
函数名：u8 NRF24L01_Read_Reg(u8 reg)
说明：读取SPI寄存器值
入口：u8 reg		寄存器地址
出口：u8	状态
备注：无
*************************************/
//
//reg:要读的寄存器
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;
	NRF24L01_CSN_L;          				//使能SPI传输		
	SPI2_ReadWriteByte(reg);   				//发送寄存器号
	reg_val = SPI2_ReadWriteByte(0XFF);	    //读取寄存器内容，只需要读取，主机可以随意传送数据过去
	NRF24L01_CSN_H;          			    //禁止SPI传输		    
	return(reg_val);           				//返回状态值
}

/*******************************************************
函数名：void NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len)
说明：在指定位置读出指定长度的数据
入口：u8 reg		寄存器(位置)
u8 *pBuf	数据指针
u8 len		数据长度
出口：无
备注：无
*******************************************************/
void NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 i;

	NRF24L01_CSN_L;           							//使能SPI传输
	SPI2_ReadWriteByte(reg);									//发送寄存器值(位置)  	   
	for (i = 0; i < len; i++)
	pBuf[i] = SPI2_ReadWriteByte(0XFF);		//读出数据
	NRF24L01_CSN_H;       									//关闭SPI传输
}


systime  spi_dealt[2];
float spi_dealt_t=0;

/********************************************************
函数名：void NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
说明：在指定位置写指定长度的数据
入口：u8 reg		寄存器(位置)
u8 *pBuf	数据指针
u8 len		数据长度
出口：无
备注：无
********************************************************/
void NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 i;
	NRF24L01_CSN_L;          						//使能SPI传输
	SPI2_ReadWriteByte(reg);							//发送寄存器值(位置)
	for	(i = 0; i < len; i++)
	SPI2_ReadWriteByte(*pBuf++); 			//写入数据	 
	NRF24L01_CSN_H;       							//关闭SPI传输
}


systime  nrf_tx_dealt;
/***************************************
函数名：u8 NRF24L01_TxPacket(u8 *txbuf)
说明：启动NRF24L01发送一次数据
入口：u8 *txbuf	待发送数据首地址
出口：U8	发送完成状况
备注：无
****************************************/
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
  u16 i=0;	
	NRF24L01_CE_L;																						//片选
	NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);		//写数据到TX BUF  32个字节
	NRF24L01_CE_H;//启动发送
	while(NRF24L01_IRQ!=0)																		//等待发送完成
	{
		i++;
		if(i==255) break;
	}
	sta = NRF24L01_Read_Reg(STATUS);  												//读取状态寄存器的值
	NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS, sta); 					//清除TX_DS或MAX_RT中断标志
	if (sta & MAX_TX)																					//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX, 0xFF);											//清除TX FIFO寄存器 
		return MAX_TX;
	}
	if (sta & TX_OK)																					//发送完成
	{
		return TX_OK;
	}
		return 0xFF;																							//其他原因发送失败
}


unsigned char NRF_Transparent_Data[NRF_RX_BUFFER_SIZE];
unsigned char NRF_Transparent_Update=0;
unsigned char NRF_Transparent_Cnt=0;
systime  nrf_rssi_delta;
float nrf_last_time=0;
float nrf_soft_rssi=0;
uint32_t nrf_tx_max_cnt=0,nrf_tx_ok_cnt=0,nrf_rx_ok_cnt=0;
void NRF24L01_State_Check(unsigned char * Rx_Buf)
{
  u8 status= NRF24L01_Read_Reg(STATUS);  											//读取状态寄存器的值
	if(status & RX_OK)//接收到数据
	{
		nrf_rx_ok_cnt++;
		uint8_t rx_fifo_len=NRF24L01_Read_Reg(R_RX_PL_WID);   //读取缓存数据长度
		if(rx_fifo_len<33)
		{
			NRF24L01_Read_Buf(RD_RX_PLOAD, Rx_Buf, rx_fifo_len);	//读取数据		
			NRF24L01_Write_Reg(FLUSH_RX, 0xFF);										//清除RX FIFO寄存器
			Serial_Data_Send(Rx_Buf, rx_fifo_len);								//串口透传发送
			for(uint16_t i=0;i<rx_fifo_len;i++)
			{
			  NCLink_Data_Prase_Prepare(Rx_Buf[i]);
			}
		}
		else
		{
		  NRF24L01_Write_Reg(FLUSH_RX, 0xFF);										//清除RX FIFO寄存器
		}
		NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS, status);	
	}
	
	
	if (status & MAX_TX)//达到最大重发次数
	{
		nrf_tx_max_cnt++;
		NRF24L01_Write_Reg(FLUSH_TX, 0xFF);											//清除TX FIFO寄存器	
		NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS, status);
	}	
	
	if (status & TX_OK)//发送成功
	{
		nrf_tx_ok_cnt++;
    NRF24L01_Write_Reg(FLUSH_TX, 0xFF);											//清除TX FIFO寄存器
		NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS, status);
	}
	
	
	Get_Systime(&nrf_rssi_delta);
	if(nrf_rssi_delta.current_time-nrf_last_time>1000)
	{
		 nrf_soft_rssi=100*nrf_tx_ok_cnt/(nrf_tx_max_cnt+nrf_tx_ok_cnt);
		 nrf_tx_max_cnt=0;
		 nrf_tx_ok_cnt=0;
	   nrf_last_time=nrf_rssi_delta.current_time;
	}
}



void NRF24L01_Mode(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_ClearITPendingBit(EXTI_Line12);//清空中断标志 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12); //选择中断管脚PB12
	//定义EXTI结构体
	//由于发送模式下已经将中断线切断，所以当切换成接收模式时，需要重新连接起来
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;							//EXTI线中断开通
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				    //定义为中断还是事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;				//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;							//使能EXTI线中断
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);   

	NRF24L01_CE_L;
	NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);	  //写TX节点地址 
	NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x01);    						  //使能通道0的自动应答     0x01
	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_RXADDR,0x01);						  //使能通道0的接收地址     0x01
	
	NRF24L01_Write_Reg(WRITE_REG_NRF+SETUP_RETR,0x1a);					  //设置自动重发间隔时间:500us + 86us;最大自动重发次数:15次	
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH,40);	    						  //设置RF通信频率		  
	//NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x0f);						//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x07); 							//设置TX发射参数,0db增益,1Mbps,低噪声增益开启
	//NRF24L01_Write_Reg(WRITE_REG_NRF+RX_PW_P0,RX_PLOAD_WIDTH);	//选择通道0的有效数据宽度 	    	   
	//NRF24L01_Write_Reg(WRITE_REG_NRF+NRF24L01_CONFIG,0x0f);			//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	
	NRF24L01_Write_Reg(WRITE_REG_NRF + NRF24L01_CONFIG, 0x0e);   		 // IRQ收发完成中断开启,16位CRC,主发送
	NRF24L01_Write_Reg(FLUSH_TX,0xff);
	NRF24L01_Write_Reg(FLUSH_RX,0xff);

	SPI2_ReadWriteByte(0x50);
	SPI2_ReadWriteByte(0x73);
	NRF24L01_Write_Reg(WRITE_REG_NRF+0x1c,0x01);
	NRF24L01_Write_Reg(WRITE_REG_NRF+0x1d,0x06);
		
	NRF24L01_CE_H; 																							//CE为高,进入接收模式

	u8 sta= NRF24L01_Read_Reg(STATUS);
	NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS, sta);
}


void NRF24L01_Duplex_TxPacket(unsigned char * Tx_Buf)
{
	//NRF24L01_State_Check(g_NRFRevData);	
	NRF24L01_CE_L;			//StandBy I模式	
	//NRF24L01_Write_Buf(WRITE_REG_NRF + RX_ADDR_P0, (u8*)rc_pair.tx_addr,TX_ADR_WIDTH); // 装载接收端地址
	NRF24L01_Write_Buf(WR_TX_PLOAD, Tx_Buf, TX_PLOAD_WIDTH); 			 // 装载数据	
	NRF24L01_CE_H;
}






/***************************************
函数名：u8 NRF24L01_RxPacket(u8 *rxbuf)
说明：启动NRF24L01接收一次数据
入口：u8 *txbuf	待接收数据首地址
出口：u8	0：接收完成
1：接收不成功
备注：无
****************************************/
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							    
	sta = NRF24L01_Read_Reg(STATUS);  							//读取状态寄存器的值    	 
	NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS,sta); 			//清除TX_DS或MAX_RT中断标志
	if (sta & RX_OK)											//接收到数据
	{
	NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH);	//读取数据
	NRF24L01_Write_Reg(FLUSH_RX, 0xFF);						//清除RX FIFO寄存器 
	return 0; 
	}
	return 1;													//没收到任何数据
}

/*****************************************************
函数名：void NRF24L01_RX_Mode(void)
说明：初始化NRF24L01到RX模式
入口：无
出口：无
备注：
设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
当CE变高后,即进入RX模式,并可以接收数据了
******************************************************/
void NRF24L01_RX_Mode(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_ClearITPendingBit(EXTI_Line12);//清空中断标志 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12); //选择中断管脚PB12
	//定义EXTI结构体
	//由于发送模式下已经将中断线切断，所以当切换成接收模式时，需要重新连接起来
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;							//EXTI线中断开通
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				    //定义为中断还是事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;				//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;							//使能EXTI线中断
	EXTI_Init(&EXTI_InitStructure);

	NRF24L01_CE_L;
	NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);	//写TX节点地址 
	NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x01);    						//使能通道0的自动应答    
	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_RXADDR,0x01);						//使能通道0的接收地址  	 
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH,40);	    						//设置RF通信频率		  
	NRF24L01_Write_Reg(WRITE_REG_NRF+RX_PW_P0,RX_PLOAD_WIDTH);	//选择通道0的有效数据宽度 	    
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x0f);						//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(WRITE_REG_NRF+NRF24L01_CONFIG,0x0f);			//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	NRF24L01_CE_H; 																							//CE为高,进入接收模式 
}

/*****************************************************************************************
函数名：void NRF24L01_TX_Mode(void)
说明：初始化NRF24L01到TX模式
入口：无
出口：无
备注：
设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
PWR_UP,CRC使能
CE为高大于10us,则启动发送
******************************************************************************************/
void NRF24L01_TX_Mode(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;//定义EXTI结构体
	//由于接收模式下的IRQ引脚设置为中断输入引脚，所以当切换成发送模式时，需要将中断输入引脚的功能取消
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;//EXTI线中断开通
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//定义为中断还是事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;//失能EXTI线中断
	EXTI_Init(&EXTI_InitStructure);

	NRF24L01_CE_L;	    
	NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);	//写TX节点地址 
	NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); 	//设置TX节点地址,主要为了使能ACK
	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x01); //使能通道0自动应答    
	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_RXADDR,0x01); //使能通道0的接收地址  
	NRF24L01_Write_Reg(WRITE_REG_NRF+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:15次
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH,40);//设置RF通道为40
	
	
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x0f);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(WRITE_REG_NRF+NRF24L01_CONFIG,0x0e);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,发送模式,开启所有中断
	NRF24L01_CE_H;															    //CE为高,10us后启动发送
}	


uint8_t address_unique[5];
void get_unique_repair(void)
{
  //获取CPU唯一ID
  cpu_id[0]=*(uint32_t*)(0x1ffff7e8);
  cpu_id[1]=*(uint32_t*)(0x1ffff7ec);
  cpu_id[2]=*(uint32_t*)(0x1ffff7f0);
   
	
	address_unique[0]=rc_pair.tx_addr[0]=(cpu_id[0]^cpu_id[1])%10;
	address_unique[1]=rc_pair.tx_addr[1]=(cpu_id[1]^cpu_id[2])%10;
	address_unique[2]=rc_pair.tx_addr[2]=(cpu_id[0]^cpu_id[2])%10;
	address_unique[3]=rc_pair.tx_addr[3]=cpu_id[0]%10;
	address_unique[4]=rc_pair.tx_addr[4]=cpu_id[1]%10;
	
	rc_pair.rx_addr[0]=(cpu_id[0]^cpu_id[1])%10;
	rc_pair.rx_addr[1]=(cpu_id[1]^cpu_id[2])%10;
	rc_pair.rx_addr[2]=(cpu_id[0]^cpu_id[2])%10;
	rc_pair.rx_addr[3]=cpu_id[0]%10;
	rc_pair.rx_addr[4]=cpu_id[1]%10;
	
	rc_pair.addr_chl[0]=address_unique[0];
	rc_pair.addr_chl[1]=address_unique[1];
	rc_pair.addr_chl[2]=address_unique[2];
	rc_pair.addr_chl[3]=address_unique[1];
	rc_pair.addr_chl[4]=address_unique[2];		
	rc_pair.addr_chl[5]=2*(rc_pair.addr_chl[0]+rc_pair.addr_chl[1]+rc_pair.addr_chl[2]+rc_pair.addr_chl[3]+rc_pair.addr_chl[4]);

	
	ReadFlashParameterThree(RC_TX_ADDR0,
										 &Table_Parameter_Read[RC_TX_ADDR0],
										 &Table_Parameter_Read[RC_TX_ADDR1],
										 &Table_Parameter_Read[RC_TX_ADDR2]);

	ReadFlashParameterTwo(RC_TX_ADDR3,
										 &Table_Parameter_Read[RC_TX_ADDR3],
										 &Table_Parameter_Read[RC_TX_ADDR4]);
											 
	ReadFlashParameterOne(RC_PAIR_CHL,&Table_Parameter_Read[RC_PAIR_CHL]);
	
	
	if(isnan(Table_Parameter_Read[RC_TX_ADDR0])==0
	 &&isnan(Table_Parameter_Read[RC_TX_ADDR1])==0
	 &&isnan(Table_Parameter_Read[RC_TX_ADDR2])==0
	 &&isnan(Table_Parameter_Read[RC_TX_ADDR3])==0
	 &&isnan(Table_Parameter_Read[RC_TX_ADDR4])==0)
	{
		rc_pair.tx_addr[0]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR0]);
		rc_pair.tx_addr[1]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR1]);
		rc_pair.tx_addr[2]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR2]);
		rc_pair.tx_addr[3]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR3]);
		rc_pair.tx_addr[4]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR4]);

		rc_pair.rx_addr[0]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR0]);
		rc_pair.rx_addr[1]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR1]);
		rc_pair.rx_addr[2]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR2]);
		rc_pair.rx_addr[3]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR3]);
		rc_pair.rx_addr[4]=(uint8_t)(Table_Parameter_Read[RC_TX_ADDR4]);
	}
	
	
	
	if(isnan(Table_Parameter_Read[RC_PAIR_CHL])==0)
	{
		rc_pair.channel=Table_Parameter_Read[RC_PAIR_CHL];
	}
	else
	{
	  rc_pair.channel=rc_pair.addr_chl[5];
	}
	
}


uint16_t pair_cnt=0;
void rc_pair_run(void)
{
	if(GPIO_ReadInputDataBit(_button.state[ENTER].port,_button.state[ENTER].pin)==0)
	{
		g_NRFSendData[0]=rc_pair.tx_addr[0];
		g_NRFSendData[1]=rc_pair.tx_addr[1];
		g_NRFSendData[2]=rc_pair.tx_addr[2];
		g_NRFSendData[3]=rc_pair.tx_addr[3];
		g_NRFSendData[4]=rc_pair.tx_addr[4];
		
		g_NRFSendData[5]=rc_pair.rx_addr[0];
		g_NRFSendData[6]=rc_pair.rx_addr[1];
		g_NRFSendData[7]=rc_pair.rx_addr[2];
		g_NRFSendData[8]=rc_pair.rx_addr[3];
		g_NRFSendData[9]=rc_pair.rx_addr[4];
		
		g_NRFSendData[10]=rc_pair.channel;//频道
		
		while(1)
		{	
			u8 sta= NRF24L01_Read_Reg(STATUS);  											//读取状态寄存器的值
			if(sta & RX_OK)//接收到数据
			{
				nrf_rx_ok_cnt++;
				uint8_t rx_fifo_len=NRF24L01_Read_Reg(R_RX_PL_WID);   //读取缓存数据长度
				//NRF24L01_Read_Buf(RD_RX_PLOAD, g_NRFRevData, rx_fifo_len);	//读取数据
				NRF24L01_Write_Reg(FLUSH_RX, 0xFF);										//清除RX FIFO寄存器 
			}

			if (sta & MAX_TX)																					//达到最大重发次数
			{
				NRF24L01_Write_Reg(FLUSH_TX, 0xFF);											//清除TX FIFO寄存器
				nrf_tx_max_cnt++;
			}

			if (sta & TX_OK)																					//达到最大重发次数
			{
				nrf_tx_ok_cnt++;
			}
			
			
			NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS, sta);
			NRF24L01_CE_L;			//StandBy I模式	
			NRF24L01_Write_Buf(WRITE_REG_NRF + RX_ADDR_P0, (u8*)TX_ADDRESS,TX_ADR_WIDTH); // 装载接收端地址
			NRF24L01_Write_Buf(WR_TX_PLOAD, g_NRFSendData, TX_PLOAD_WIDTH); 			 			  // 装载数据	
			NRF24L01_CE_H;
			delay_ms(5);

			delay_ms(50);
			GPIO_SetBits(GPIOC,GPIO_Pin_12);   
			delay_ms(50);
			GPIO_ResetBits(GPIOC,GPIO_Pin_12);
			
			if(nrf_tx_ok_cnt>=10) 
			{
				GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_SET);
				delay_ms(100);	
				pair_cnt++;
				if(pair_cnt>=5) break;
			}
		}
	}
	
	NRF24L01_CE_L;
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH		 ,rc_pair.channel);//设置RF通道
	NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)rc_pair.rx_addr,RX_ADR_WIDTH);//写RX节点地址
	NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR	 ,(u8*)rc_pair.tx_addr,TX_ADR_WIDTH);	//写TX节点地址	
	NRF24L01_CE_H; 																							//CE为高,进入接收模式
	u8 sta= NRF24L01_Read_Reg(STATUS);	
	if(sta & RX_OK)//接收到数据
	{
		NRF24L01_Write_Reg(FLUSH_RX, 0xFF);										//清除RX FIFO寄存器 
	}
	if (sta & MAX_TX)																					//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX, 0xFF);											//清除TX FIFO寄存器
	}	
	NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS, sta);
	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);   	
}





typedef enum
{
  TX_MODE=0,
  RX_MODE
}NRF_MODE;

uint16_t tx_cnt=0;      //发送次数计数
uint16_t rx_cnt=0;      //接收次数计数
#define nrf_err_max 2
NRF_MODE _nrf_mode=TX_MODE;
void nrf_tx_rx_exchange(void)
{
  if(_nrf_mode==TX_MODE)//发送模式下
	{
	  if(NRF24L01_TxPacket(g_NRFSendData)==TX_OK)
		{
		  tx_cnt=0;
			_nrf_mode=RX_MODE;
			NRF24L01_RX_Mode();//一旦发送成功则变成接收模式
		}
		tx_cnt++;
		if(tx_cnt>=nrf_err_max) //如果连续发送Max次都失败，则切换为接收模式
		{
			tx_cnt=0;
			_nrf_mode=RX_MODE;
			NRF24L01_RX_Mode();//一旦发送成功则变成接收模式	
		}
	}
  else//接收模式下
	{
		if (NRF24L01_RxPacket(g_NRFRevData)==0)//一旦接收成功则变成发送模式；
		{
			rx_cnt=0;
			_nrf_mode=TX_MODE;
			NRF24L01_TX_Mode();
		}
		rx_cnt++;
		if (rx_cnt>=nrf_err_max)//如果连续接收Max次都失败，则切换为发送模式
		{
		 rx_cnt=0;
		 _nrf_mode=TX_MODE;
		 NRF24L01_TX_Mode();
		}
	}
}


systime  nrf_isr_dealt;
uint16_t isr;
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)//判断某个线上的中断是否发生 
	{
			Get_Systime(&nrf_isr_dealt);
			//NRF24L01_State_Check(g_NRFRevData);
			isr++;
			EXTI_ClearITPendingBit(EXTI_Line12);   //清除 LINE 上的中断标志位
	}     
}
