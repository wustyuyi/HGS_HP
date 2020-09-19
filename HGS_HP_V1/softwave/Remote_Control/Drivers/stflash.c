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
#include "stflash.h"
#include "delay.h"
#include "main.h"
#include "stdio.h"


//初始化IIC接口
void AT24CXX_Init(void)
{
	while (AT24CXX_Check()) //检测不到24c02
	{
		//printf("cant check eeprom\n");
		delay_ms(700);
	}
	//printf("EEPROM OK\n");
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址
//返回值  :读到的数据
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{
	u8 temp = 0;
	SOFT_IIC_Start();
	if (EE_TYPE > AT24C16)
	{
		SOFT_IIC_Send_Byte(0XA0); //发送写命令
		SOFT_IIC_Wait_Ack();
		SOFT_IIC_Send_Byte(ReadAddr >> 8); //发送高地址
		SOFT_IIC_Wait_Ack();
	}
	else
		SOFT_IIC_Send_Byte(0XA0 + ((ReadAddr / 256) << 1)); //发送器件地址0XA0,写数据

	SOFT_IIC_Wait_Ack();
	SOFT_IIC_Send_Byte(ReadAddr % 256); //发送低地址
	SOFT_IIC_Wait_Ack();
	SOFT_IIC_Start();
	SOFT_IIC_Send_Byte(0XA1); //进入接收模式
	SOFT_IIC_Wait_Ack();
	temp = SOFT_IIC_Read_Byte(0);
	SOFT_IIC_Stop(); //产生一个停止条件
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(u16 WriteAddr, u8 DataToWrite)
{
	SOFT_IIC_Start();
	if (EE_TYPE > AT24C16)
	{
		SOFT_IIC_Send_Byte(0XA0); //发送写命令
		SOFT_IIC_Wait_Ack();
		SOFT_IIC_Send_Byte(WriteAddr >> 8); //发送高地址
	}
	else
	{
		SOFT_IIC_Send_Byte(0XA0 + ((WriteAddr / 256) << 1)); //发送器件地址0XA0,写数据
	}
	SOFT_IIC_Wait_Ack();
	SOFT_IIC_Send_Byte(WriteAddr % 256); //发送低地址
	SOFT_IIC_Wait_Ack();
	SOFT_IIC_Send_Byte(DataToWrite); //发送字节
	SOFT_IIC_Wait_Ack();
	SOFT_IIC_Stop(); //产生一个停止条件
	delay_ms(10);
}
//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(u16 WriteAddr, u32 DataToWrite, u8 Len)
{
	u8 t;
	for (t = 0; t < Len; t++)
	{
		AT24CXX_WriteOneByte(WriteAddr + t, (DataToWrite >> (8 * t)) & 0xff);
	}
}

//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址
//返回值     :数据
//Len        :要读出数据的长度2,4
u32 AT24CXX_ReadLenByte(u16 ReadAddr, u8 Len)
{
	u8 t;
	u32 temp = 0;
	for (t = 0; t < Len; t++)
	{
		temp <<= 8;
		temp += AT24CXX_ReadOneByte(ReadAddr + Len - t - 1);
	}
	return temp;
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(u16 ReadAddr, u8 *pBuffer, u16 NumToRead)
{
	while (NumToRead)
	{
		*pBuffer++ = AT24CXX_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(u16 WriteAddr, u8 *pBuffer, u16 NumToWrite)
{
	while (NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr, *pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}

//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功

uint8_t at24cx_data_write[10]={"helloworld"};
uint8_t at24cx_data_read[10]={};
u8 AT24CXX_Check(void)
{
	AT24CXX_Write(0,at24cx_data_write,10);
	AT24CXX_Read(0,at24cx_data_read,10);
	u8 temp;
	temp = AT24CXX_ReadOneByte(255); //避免每次开机都写AT24CXX
	if (temp == 0X55)
		return 0;
	else //排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(255, 0X55);
		temp = AT24CXX_ReadOneByte(255);
		if (temp == 0X55)
			return 0;
	}
	return 1;
}


