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
#include "ppm.h"

#define ppm_offset (0)
#define ppm_scale 1


#define PPM_OUT_H  {GPIO_WriteBit(GPIOC,GPIO_Pin_8,Bit_SET)  ;GPIO_WriteBit(GPIOC,GPIO_Pin_11,Bit_SET);}	//输出高电平
#define PPM_OUT_L  {GPIO_WriteBit(GPIOC,GPIO_Pin_8,Bit_RESET);GPIO_WriteBit(GPIOC,GPIO_Pin_11,Bit_RESET);}//输出低电平


//定时器初始化与PPM输出引脚初始化
void ppm_init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;  	  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	
	
		NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC初始化结构体
	
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	  TIM_DeInit(TIM3);
		TIM_TimeBaseStructure.TIM_Period=500-1;
		TIM_TimeBaseStructure.TIM_Prescaler=systemclk_mhz/ppm_scale-1;
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM3, ENABLE);

	
	
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure); 
		PPM_OUT_L;
}



systime  tim3_dealt;
uint16_t ppm_test[8]={1000,1500,1400,1300,1600,1750,1850,1950};
void TIM3_IRQHandler(void)
{
	uint16_t time=0;
	static uint8_t ppm_count=1;  //步骤计数
	static uint16_t toal_time=0;//总的通道高+低电平时间
  if( TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET )
  {
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);		
		switch(ppm_count)
    {
    case 1://第一通道开始  -----------------------------（1）
        PPM_OUT_H;
				time=RC_Data.rcdata[0]-500;//(通道高电平时间在500us~1500us）
				toal_time+=time;
		    time=ppm_scale*time+ppm_offset;
        TIM_SetAutoreload(TIM3,(uint16_t)(time-1));
        ppm_count++;
        break;
    case 2://第一通道结束,开始0.5ms低电平---------------（2）
        PPM_OUT_L;
				toal_time+=500;
        TIM_SetAutoreload(TIM3,500*ppm_scale-1);
        ppm_count++;
        break;
    case 3://第二通道开始------------------------------（3）
        PPM_OUT_H;
				time=RC_Data.rcdata[1]-500;
				toal_time+=time;
		    time=ppm_scale*time+ppm_offset;
        TIM_SetAutoreload(TIM3,(uint16_t)(time-1));
        ppm_count++;
        break;
    case 4://第二通道结束,开始0.5ms低电平
        PPM_OUT_L;
				toal_time+=500;
        TIM_SetAutoreload(TIM3,500*ppm_scale-1);
        ppm_count++;
        break;
    case 5://第三通道开始
        PPM_OUT_H;
				time=RC_Data.rcdata[2]-500;
				toal_time+=time;
		    time=ppm_scale*time+ppm_offset;
        TIM_SetAutoreload(TIM3,(uint16_t)(time-1));
        ppm_count++;
        break;
    case 6://第三通道结束,开始0.5ms低电平
        PPM_OUT_L;
				toal_time+=500;
        TIM_SetAutoreload(TIM3,500*ppm_scale-1);
        ppm_count++;
        break;
    case 7://第四通道开始
        PPM_OUT_H;
        time=RC_Data.rcdata[3]-500;
				toal_time+=time;
		    time=ppm_scale*time+ppm_offset;
        TIM_SetAutoreload(TIM3,(uint16_t)(time-1));
        ppm_count++;
        break;
    case 8://第四通道结束,开始0.5ms低电平---------------（4）
        PPM_OUT_L;
				toal_time+=500;
        TIM_SetAutoreload(TIM3,500*ppm_scale-1);
        ppm_count++;
        break;
    case 9://第5通道开始
        PPM_OUT_H;
        time=RC_Data.rcdata[4]-500;
				toal_time+=time;
		    time=ppm_scale*time+ppm_offset;
        TIM_SetAutoreload(TIM3,(uint16_t)(time-1));
        ppm_count++;
        break;
    case 10://第5通道结束,开始0.5ms低电平---------------（4）
        PPM_OUT_L;
				toal_time+=500;
        TIM_SetAutoreload(TIM3,500*ppm_scale-1);
        ppm_count++;
        break;
    case 11://第6通道开始
        PPM_OUT_H;
        time=RC_Data.rcdata[5]-500;
				toal_time+=time;
		    time=ppm_scale*time+ppm_offset;
        TIM_SetAutoreload(TIM3,(uint16_t)(time-1));
        ppm_count++;
        break;
    case 12://第6通道结束,开始0.5ms低电平---------------（4）
        PPM_OUT_L;
				toal_time+=500;
        TIM_SetAutoreload(TIM3,500*ppm_scale-1);
        ppm_count++;
        break;
    case 13://第7通道开始
        PPM_OUT_H;
        time=RC_Data.rcdata[6]-500;
				toal_time+=time;
		    time=ppm_scale*time+ppm_offset;
        TIM_SetAutoreload(TIM3,(uint16_t)(time-1));
        ppm_count++;
        break;
    case 14://第7通道结束,开始0.5ms低电平---------------（4）
        PPM_OUT_L;
				toal_time+=500;
        TIM_SetAutoreload(TIM3,500*ppm_scale-1);
        ppm_count++;
        break;
    case 15://第8通道开始
        PPM_OUT_H;
        time=RC_Data.rcdata[7]-500;
				toal_time+=time;
		    time=ppm_scale*time+ppm_offset;
        TIM_SetAutoreload(TIM3,(uint16_t)(time-1));
        ppm_count++;
        break;
    case 16://第8通道结束,开始0.5ms低电平---------------（4）
        PPM_OUT_L;
				toal_time+=500;
        TIM_SetAutoreload(TIM3,500*ppm_scale-1);
        ppm_count++;
        break;
    case 17://8路信号全部结束，20ms剩下的时间高电平----------（5）
        PPM_OUT_H;
				time=19500-toal_time;
		    time=ppm_scale*time+ppm_offset;
        TIM_SetAutoreload(TIM3,(uint16_t)(time-1));
        ppm_count++;
        break;
    case 18://重新开始---------------------------------（6）
        PPM_OUT_L;
        TIM_SetAutoreload(TIM3,500*ppm_scale-1);
				toal_time=0;//通道高电平清零，重新开始
        ppm_count=1;
		    Get_Systime(&tim3_dealt);
				break;
    }		
  }
}
//void TIM2_IRQHandler(void)
//{
//	uint16_t time=0;
//	static uint8_t ppm_count=1;  //步骤计数
//	static uint16_t toal_time=0;//总的通道高+低电平时间
//  if( TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET )
//  {		
//		switch(ppm_count)
//    {
//    case 1://第一通道开始  -----------------------------（1）
//        PPM_OUT_H;
//				time=RC_Data.rcdata[0]-500;//(通道高电平时间在500us~1500us）
//				toal_time+=time;
//        TIM_SetAutoreload(TIM2,(uint16_t)(time-1));
//        ppm_count++;
//        break;
//    case 2://第一通道结束,开始0.5ms低电平---------------（2）
//        PPM_OUT_L;
//				toal_time+=500;
//        TIM_SetAutoreload(TIM2,499);
//        ppm_count++;
//        break;
//    case 3://第二通道开始------------------------------（3）
//        PPM_OUT_H;
//				time=RC_Data.rcdata[1]-500;
//				toal_time+=time;
//        TIM_SetAutoreload(TIM2,(uint16_t)(time-1));
//        ppm_count++;
//        break;
//    case 4://第二通道结束,开始0.5ms低电平
//        PPM_OUT_L;
//				toal_time+=500;
//        TIM_SetAutoreload(TIM2,499);
//        ppm_count++;
//        break;
//    case 5://第三通道开始
//        PPM_OUT_H;
//				time=RC_Data.rcdata[2]-500;
//				toal_time+=time;
//        TIM_SetAutoreload(TIM2,(uint16_t)(time-1));
//        ppm_count++;
//        break;
//    case 6://第三通道结束,开始0.5ms低电平
//        PPM_OUT_L;
//				toal_time+=500;
//        TIM_SetAutoreload(TIM2,499);
//        ppm_count++;
//        break;
//    case 7://第四通道开始
//        PPM_OUT_H;
//        time=RC_Data.rcdata[3]-500;
//				toal_time+=time;
//        TIM_SetAutoreload(TIM2,(uint16_t)(time-1));
//        ppm_count++;
//        break;
//    case 8://第四通道结束,开始0.5ms低电平---------------（4）
//        PPM_OUT_L;
//				toal_time+=500;
//        TIM_SetAutoreload(TIM2,499);
//        ppm_count++;
//        break;
//    case 9://第5通道开始
//        PPM_OUT_H;
//        time=RC_Data.rcdata[4]-500;
//				toal_time+=time;
//        TIM_SetAutoreload(TIM2,(uint16_t)(time-1));
//        ppm_count++;
//        break;
//    case 10://第5通道结束,开始0.5ms低电平---------------（4）
//        PPM_OUT_L;
//				toal_time+=500;
//        TIM_SetAutoreload(TIM2,499);
//        ppm_count++;
//        break;
//    case 11://第6通道开始
//        PPM_OUT_H;
//        time=RC_Data.rcdata[5]-500;
//				toal_time+=time;
//        TIM_SetAutoreload(TIM2,(uint16_t)(time-1));
//        ppm_count++;
//        break;
//    case 12://第6通道结束,开始0.5ms低电平---------------（4）
//        PPM_OUT_L;
//				toal_time+=500;
//        TIM_SetAutoreload(TIM2,499);
//        ppm_count++;
//        break;
//    case 13://第7通道开始
//        PPM_OUT_H;
//        time=RC_Data.rcdata[6]-500;
//				toal_time+=time;
//        TIM_SetAutoreload(TIM2,(uint16_t)(time-1));
//        ppm_count++;
//        break;
//    case 14://第7通道结束,开始0.5ms低电平---------------（4）
//        PPM_OUT_L;
//				toal_time+=500;
//        TIM_SetAutoreload(TIM2,499);
//        ppm_count++;
//        break;
//    case 15://第8通道开始
//        PPM_OUT_H;
//        time=RC_Data.rcdata[7]-500;
//				toal_time+=time;
//        TIM_SetAutoreload(TIM2,(uint16_t)(time-1));
//        ppm_count++;
//        break;
//    case 16://第8通道结束,开始0.5ms低电平---------------（4）
//        PPM_OUT_L;
//				toal_time+=500;
//        TIM_SetAutoreload(TIM2,499);
//        ppm_count++;
//        break;
//    case 17://8路信号全部结束，20ms剩下的时间高电平----------（5）
//        PPM_OUT_H;
//				time=19500-toal_time;
//        TIM_SetAutoreload(TIM2,(uint16_t)(time-1));
//        ppm_count++;
//        break;
//    case 18://重新开始---------------------------------（6）
//        PPM_OUT_L;
//        TIM_SetAutoreload(TIM2,499);
//				toal_time=0;//通道高电平清零，重新开始
//        ppm_count=1;
//		    Get_Systime(&tim2_dealt);
//				break;
//    }
//    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);		
//  }
//}

