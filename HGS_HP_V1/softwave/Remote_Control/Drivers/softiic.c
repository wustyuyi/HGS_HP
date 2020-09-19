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
#include "softiic.h"
#include "delay.h"




//MPU IIC 延时函数
void SOFT_IIC_Delay(void)
{
	delay_us(2);
}

//初始化IIC
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//先使能外设IO PORTB时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIO
	GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);			 //PB10,PB11 输出高
}



//IO方向设置
void SOFT_SDA_IN(void)        
{                           
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void SOFT_SDA_OUT(void)     
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


//产生IIC起始信号
void SOFT_IIC_Start(void)
{
	SOFT_SDA_OUT(); //sda线输出
	SOFT_IIC_SDA = 1;
	SOFT_IIC_SCL = 1;
	SOFT_IIC_Delay();
	SOFT_IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
	SOFT_IIC_Delay();
	SOFT_IIC_SCL = 0; //钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void SOFT_IIC_Stop(void)
{
	SOFT_SDA_OUT(); //sda线输出
	SOFT_IIC_SCL = 0;
	SOFT_IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
	SOFT_IIC_Delay();
	SOFT_IIC_SCL = 1;
	SOFT_IIC_SDA = 1; //发送I2C总线结束信号
	SOFT_IIC_Delay();
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 SOFT_IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	SOFT_SDA_IN(); //SDA设置为输入
	SOFT_IIC_SDA = 1;
	SOFT_IIC_Delay();
	SOFT_IIC_SCL = 1;
	SOFT_IIC_Delay();
	while (SOFT_READ_SDA)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			SOFT_IIC_Stop();
			return 1;
		}
	}
	SOFT_IIC_SCL = 0; //时钟输出0
	return 0;
}
//产生ACK应答
void SOFT_IIC_Ack(void)
{
	SOFT_IIC_SCL = 0;
	SOFT_SDA_OUT();
	SOFT_IIC_SDA = 0;
	SOFT_IIC_Delay();
	SOFT_IIC_SCL = 1;
	SOFT_IIC_Delay();
	SOFT_IIC_SCL = 0;
}
//不产生ACK应答
void SOFT_IIC_NAck(void)
{
	SOFT_IIC_SCL = 0;
	SOFT_SDA_OUT();
	SOFT_IIC_SDA = 1;
	SOFT_IIC_Delay();
	SOFT_IIC_SCL = 1;
	SOFT_IIC_Delay();
	SOFT_IIC_SCL = 0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void SOFT_IIC_Send_Byte(u8 txd)
{
	u8 t;
	SOFT_SDA_OUT();
	SOFT_IIC_SCL = 0; //拉低时钟开始数据传输
	for (t = 0; t < 8; t++)
	{
		SOFT_IIC_SDA = (txd & 0x80) >> 7;
		txd <<= 1;
		SOFT_IIC_SCL = 1;
		SOFT_IIC_Delay();
		SOFT_IIC_SCL = 0;
		SOFT_IIC_Delay();
	}
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 SOFT_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	SOFT_SDA_IN(); //SDA设置为输入
	for (i = 0; i < 8; i++)
	{
		SOFT_IIC_SCL = 0;
		SOFT_IIC_Delay();
		SOFT_IIC_SCL = 1;
		receive <<= 1;
		if (SOFT_READ_SDA)
			receive++;
		SOFT_IIC_Delay();
	}
	if (!ack)
		SOFT_IIC_NAck(); //发送nACK
	else
		SOFT_IIC_Ack(); //发送ACK
	return receive;
}
