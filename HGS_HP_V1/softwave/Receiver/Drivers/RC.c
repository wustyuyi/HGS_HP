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
#include "rc.h"

void Tim1_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC初始化结构体

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_DeInit(TIM1);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  TIM_TimeBaseStructure.TIM_Period=2500-1;
  TIM_TimeBaseStructure.TIM_Prescaler= (systemclk_mhz-1);
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
  TIM_Cmd(TIM1, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);   
}


//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = 1000-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值     计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =systemclk_mhz-1; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设

}



uint16_t rc_gps_cnt=0;
rc RC_Data;
void RC_All_Init(void)
{	
	RC_Data.rcdata[RC_ROLL_CHANNEL]=1500;
	RC_Data.rcdata[RC_PITCH_CHANNEL]=1500;
	RC_Data.rcdata[RC_THR_CHANNEL]=1000;
	RC_Data.rcdata[RC_YAW_CHANNEL]=1500;
			
	RC_Data.rcdata[RC_SWA_CHANNEL]=1000;
	RC_Data.rcdata[RC_SWB_CHANNEL]=1000;
	RC_Data.rcdata[RC_SWC_CHANNEL]=1000;
	RC_Data.rcdata[RC_SWD_CHANNEL]=1000;

	RC_Data.rcdata[RC_VRA_CHANNEL]=1000;
	RC_Data.rcdata[RC_VRB_CHANNEL]=1000;	
	
	RC_Data.lose_ctrl_protect=0;
	RC_Data.lose_ctrl_protect_channel=7;
	RC_Data.lose_ctrl_protect_value=1000;
	
	Tim1_Init();
	TIM3_Init();
}

void Remote_Ctrl_Prase(void)
{
  if(g_NRFRevData[0]==0xA2&&g_NRFRevData[1]==0xA1
	 &&g_NRFRevData[27]==0xFC&&g_NRFRevData[28]==0xFF)
	{	
		if(g_NRFRevData[2]==0x01)
		{
			uint8_t sum1 = 0,sum2 = 0;
			for(uint8_t i=0;i<29;i++)  sum1 ^= g_NRFRevData[i];
			for(uint8_t i=0;i<29;i++)  sum2 += g_NRFRevData[i];
			if(sum1!=g_NRFRevData[29])  return;
			if(sum2!=g_NRFRevData[30])  return;
			
			
			RC_Data.rcdata[RC_ROLL_CHANNEL]=g_NRFRevData[3]<<8|g_NRFRevData[4];
			RC_Data.rcdata[RC_PITCH_CHANNEL]=g_NRFRevData[5]<<8|g_NRFRevData[6];
			RC_Data.rcdata[RC_THR_CHANNEL]=g_NRFRevData[7]<<8|g_NRFRevData[8];
			RC_Data.rcdata[RC_YAW_CHANNEL]=g_NRFRevData[9]<<8|g_NRFRevData[10];
					
			RC_Data.rcdata[RC_SWA_CHANNEL]=g_NRFRevData[11]<<8|g_NRFRevData[12];
			RC_Data.rcdata[RC_SWB_CHANNEL]=g_NRFRevData[13]<<8|g_NRFRevData[14];
			RC_Data.rcdata[RC_SWC_CHANNEL]=g_NRFRevData[15]<<8|g_NRFRevData[16];
			RC_Data.rcdata[RC_SWD_CHANNEL]=g_NRFRevData[17]<<8|g_NRFRevData[18];

			RC_Data.rcdata[RC_VRA_CHANNEL]=g_NRFRevData[19]<<8|g_NRFRevData[20];
			RC_Data.rcdata[RC_VRB_CHANNEL]=g_NRFRevData[21]<<8|g_NRFRevData[22];
			
			
			RC_Data.lose_ctrl_protect=g_NRFRevData[23];
			RC_Data.lose_ctrl_protect_channel=g_NRFRevData[24];
			RC_Data.lose_ctrl_protect_value=g_NRFRevData[25]<<8|g_NRFRevData[26];
		}
		else if(g_NRFRevData[2]==0x02)
		{
			RC_Data.gps_ok=g_NRFRevData[3];
			RC_Data.gps_lng =((int32_t)(*(g_NRFRevData+4)<<24)|(*(g_NRFRevData+5)<<16)|(*(g_NRFRevData+6)<<8)|*(g_NRFRevData+7));
			RC_Data.gps_lat =((int32_t)(*(g_NRFRevData+8)<<24)|(*(g_NRFRevData+9)<<16)|(*(g_NRFRevData+10)<<8)|*(g_NRFRevData+11));
			
			if(RC_Data.gps_ok==1)
			{
				NCLink_GS_Send_GPS_Guide_Flight(RC_Data.gps_lng,RC_Data.gps_lat);
				rc_gps_cnt++;
			}
		}
		RC_Data.prase_success=1;
	}
  else
	{
	  RC_Data.prase_success=0;
	}		
}


uint16_t sbus_output_cnt=0;
uint32_t lose_ctrl_cnt=0;
systime  tim1_dealt;
void TIM1_UP_IRQHandler(void)//5ms刷新一次
{
  if( TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET )
  {
		Get_Systime(&tim1_dealt);
   lose_ctrl_cnt++;
	 if(lose_ctrl_cnt>5000) lose_ctrl_cnt=5000;
	 if((lose_ctrl_cnt>=1000||nrf_soft_rssi<10)//信号强度小于10% 
		 &&RC_Data.lose_ctrl_protect==1)//持续2.5S未检测到遥控器数据，执行失控保护
	 {
	   RC_Data.rcdata[RC_Data.lose_ctrl_protect_channel-1]=RC_Data.lose_ctrl_protect_value;
	 }
 
	 if(Transparent_Update==1&&RC_Data.prase_success==0)
	 {
		 Transparent_Update=0;
		 USART1_Send_Dma(Transparent_Data,Transparent_Cnt);
	 }

	 
    sbus_output_cnt++;
		if(sbus_output_cnt%6==0)//15ms
		{
		  sbus_output();
		}
		Bling_Working(0);
    TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
  }
}

systime  tim3_dealt;
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
	{
		Get_Systime(&tim3_dealt);
		//NRF24L01_State_Check(g_NRFRevData);
		nrf_soft_rssi_get();
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源
	}
}


