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
#include "rc.h"

void Tim1_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_DeInit(TIM1);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  TIM_TimeBaseStructure.TIM_Period=5000;
  TIM_TimeBaseStructure.TIM_Prescaler= (72-1);
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
  TIM_Cmd(TIM1, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC初始化结构体
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;//串口中断2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);   
}






void Tim2_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period=500-1;
	TIM_TimeBaseStructure.TIM_Prescaler= (72-1);
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}



rc RC_Data;
void RC_All_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;  	  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	
  

											
  for(uint16_t i=0;i<RC_CHL_MAX;i++)
	{		
		uint16_t j=3*i;
		ReadFlashParameterThree(RC_CAL_ROLL_MIN+j,
													 &Table_Parameter_Read[RC_CAL_ROLL_MIN+j],
													 &Table_Parameter_Read[RC_CAL_ROLL_MIN+j+1],
													 &Table_Parameter_Read[RC_CAL_ROLL_MIN+j+2]);
		if(isnan(Table_Parameter_Read[RC_CAL_ROLL_MIN+j])==0
		 &&isnan(Table_Parameter_Read[RC_CAL_ROLL_MIN+j+1])==0
		 &&isnan(Table_Parameter_Read[RC_CAL_ROLL_MIN+j+2])==0)
		{	
			RC_Data.cal[i].min=Table_Parameter_Read[RC_CAL_ROLL_MIN+j];
			RC_Data.cal[i].max=Table_Parameter_Read[RC_CAL_ROLL_MIN+j+1];
			RC_Data.cal[i].offset=Table_Parameter_Read[RC_CAL_ROLL_MIN+j+2];
		}
		else
		{
			RC_Data.cal[i].min=1000;
			RC_Data.cal[i].max=2000;
			RC_Data.cal[i].offset=0;
		}
	}

	ReadFlashParameterThree(RC_MAP_CH5,
													&Table_Parameter_Read[RC_MAP_CH5],
													&Table_Parameter_Read[RC_MAP_CH5+1],
													&Table_Parameter_Read[RC_MAP_CH5+2]);
	ReadFlashParameterThree(RC_MAP_CH8,
													&Table_Parameter_Read[RC_MAP_CH8],
													&Table_Parameter_Read[RC_MAP_CH8+1],
													&Table_Parameter_Read[RC_MAP_CH8+2]);
	
	if(isnan(Table_Parameter_Read[RC_MAP_CH5])==0
		&&isnan(Table_Parameter_Read[RC_MAP_CH6])==0
		&&isnan(Table_Parameter_Read[RC_MAP_CH7])==0
		&&isnan(Table_Parameter_Read[RC_MAP_CH8])==0
		&&isnan(Table_Parameter_Read[RC_MAP_CH9])==0
		&&isnan(Table_Parameter_Read[RC_MAP_CH10])==0)
	{
	  RC_Data.rock_ch_remap[0]=0;
		RC_Data.rock_ch_remap[1]=1;
		RC_Data.rock_ch_remap[2]=2;
		RC_Data.rock_ch_remap[3]=3;
		RC_Data.func_ch_remap[0]=Table_Parameter_Read[RC_MAP_CH5];
		RC_Data.func_ch_remap[1]=Table_Parameter_Read[RC_MAP_CH6];
		RC_Data.func_ch_remap[2]=Table_Parameter_Read[RC_MAP_CH7];
		RC_Data.func_ch_remap[3]=Table_Parameter_Read[RC_MAP_CH8];
		RC_Data.func_ch_remap[4]=Table_Parameter_Read[RC_MAP_CH9];
		RC_Data.func_ch_remap[5]=Table_Parameter_Read[RC_MAP_CH10];	
	}
	else
	{
	  RC_Data.rock_ch_remap[0]=0;
		RC_Data.rock_ch_remap[1]=1;
		RC_Data.rock_ch_remap[2]=2;
		RC_Data.rock_ch_remap[3]=3;
		RC_Data.func_ch_remap[0]=SWA;
		RC_Data.func_ch_remap[1]=SWB;
		RC_Data.func_ch_remap[2]=SWC;
		RC_Data.func_ch_remap[3]=SWD;
		RC_Data.func_ch_remap[4]=VRA;
		RC_Data.func_ch_remap[5]=VRB;
	}
	
	ReadFlashParameterThree(LOSE_CTRL_PROTECT_ENABLE,
												&Table_Parameter_Read[LOSE_CTRL_PROTECT_ENABLE],
												&Table_Parameter_Read[LOSE_CTRL_PROTECT_ENABLE+1],
												&Table_Parameter_Read[LOSE_CTRL_PROTECT_ENABLE+2]);
	if(isnan(Table_Parameter_Read[LOSE_CTRL_PROTECT_ENABLE])==0
		&&isnan(Table_Parameter_Read[LOSE_CTRL_PROTECT_ENABLE+1])==0
		&&isnan(Table_Parameter_Read[LOSE_CTRL_PROTECT_ENABLE+2])==0)
	{
		RC_Data.lose_ctrl_protect=Table_Parameter_Read[LOSE_CTRL_PROTECT_ENABLE];
		RC_Data.lose_ctrl_protect_channel=Table_Parameter_Read[LOSE_CTRL_PROTECT_ENABLE+1];
		RC_Data.lose_ctrl_protect_value=Table_Parameter_Read[LOSE_CTRL_PROTECT_ENABLE+2];
	}
	else
	{
		RC_Data.lose_ctrl_protect=1;
		RC_Data.lose_ctrl_protect_channel=7;
		RC_Data.lose_ctrl_protect_value=2000;
	}
	
	
	ReadFlashParameterOne(RC_SAFE_VOLTAGE,&Table_Parameter_Read[RC_SAFE_VOLTAGE]);
	if(isnan(Table_Parameter_Read[RC_SAFE_VOLTAGE])==0)
	{
		RC_Data.safe_vbat_v=Table_Parameter_Read[RC_SAFE_VOLTAGE];
	}
	else
	{
	  RC_Data.safe_vbat_v=3.70f;
	}
	
	ReadFlashParameterOne(FLIGHT_SAFE_VOLTAGE,&Table_Parameter_Read[FLIGHT_SAFE_VOLTAGE]);
	if(isnan(Table_Parameter_Read[FLIGHT_SAFE_VOLTAGE])==0)
	{
		RC_Data.flight_safe_vbat_v=Table_Parameter_Read[FLIGHT_SAFE_VOLTAGE];
	}
	else
	{
	  RC_Data.flight_safe_vbat_v=10.5f;
	}
	
	ReadFlashParameterOne(FLIGHT_SAFE_VOLTAGE_ENABLE,&Table_Parameter_Read[FLIGHT_SAFE_VOLTAGE_ENABLE]);
	if(isnan(Table_Parameter_Read[FLIGHT_SAFE_VOLTAGE_ENABLE])==0)
	{
		RC_Data.flight_safe_vbat_enable=Table_Parameter_Read[FLIGHT_SAFE_VOLTAGE_ENABLE];
	}
	else
	{
	  RC_Data.flight_safe_vbat_enable=0;
	}
	
	Tim1_Init();
	Tim2_Init();
}




systime  nrf_dealt[2];
float nrf_dealt_t=0;
uint16_t rc_send_cnt=0;
uint16_t rc_gps_cnt=0;
void Remote_Ctrl_Prase(void)
{
	RC_Data.rcdata[RC_ROLL_CHANNEL]=RC_Data.cal[RC_ROLL_CHANNEL].max-(RC_Data.cal[RC_ROLL_CHANNEL].max-RC_Data.cal[RC_ROLL_CHANNEL].min)*ADC_value[5]/4095;
	RC_Data.rcdata[RC_PITCH_CHANNEL]=RC_Data.cal[RC_PITCH_CHANNEL].max-(RC_Data.cal[RC_PITCH_CHANNEL].max-RC_Data.cal[RC_PITCH_CHANNEL].min)*ADC_value[4]/4095;
	RC_Data.rcdata[RC_THR_CHANNEL]=RC_Data.cal[RC_THR_CHANNEL].max-(RC_Data.cal[RC_THR_CHANNEL].max-RC_Data.cal[RC_THR_CHANNEL].min)*ADC_value[1]/4095;
	RC_Data.rcdata[RC_YAW_CHANNEL]=RC_Data.cal[RC_YAW_CHANNEL].max-(RC_Data.cal[RC_YAW_CHANNEL].max-RC_Data.cal[RC_YAW_CHANNEL].min)*ADC_value[2]/4095;
	
	RC_Data.rcdata[RC_VRA_CHANNEL]=RC_Data.cal[RC_VRA_CHANNEL].max-(RC_Data.cal[RC_VRA_CHANNEL].max-RC_Data.cal[RC_VRA_CHANNEL].min)*ADC_value[3]/4095;

	RC_Data.rcdata[RC_VRB_CHANNEL]=RC_Data.cal[RC_VRB_CHANNEL].max-(RC_Data.cal[RC_VRB_CHANNEL].max-RC_Data.cal[RC_VRB_CHANNEL].min)*ADC_value[6]/4095;
	
	RC_Data.rcdata[RC_SWA_CHANNEL]=RC_Data.cal[RC_SWA_CHANNEL].max-(RC_Data.cal[RC_SWA_CHANNEL].max-RC_Data.cal[RC_SWA_CHANNEL].min)*GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
	RC_Data.rcdata[RC_SWB_CHANNEL]=RC_Data.cal[RC_SWB_CHANNEL].max-(RC_Data.cal[RC_SWB_CHANNEL].max-RC_Data.cal[RC_SWB_CHANNEL].min)*GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
	RC_Data.rcdata[RC_SWC_CHANNEL]=RC_Data.cal[RC_SWC_CHANNEL].max-(RC_Data.cal[RC_SWC_CHANNEL].max-RC_Data.cal[RC_SWC_CHANNEL].min)*GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5);
	RC_Data.rcdata[RC_SWD_CHANNEL]=RC_Data.cal[RC_SWD_CHANNEL].max-(RC_Data.cal[RC_SWD_CHANNEL].max-RC_Data.cal[RC_SWD_CHANNEL].min)*GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4);
	
	
//	static uint32 t=0;
//	t++;
//	RC_Data.rcdata[0]=1500+500*sinf(0.01f*t+3.14/8);
//	RC_Data.rcdata[1]=1500+500*cosf(0.01f*t+3.14/7);
//	RC_Data.rcdata[2]=1500+500*sinf(0.01f*t+3.14/6);
//	RC_Data.rcdata[3]=1500+500*cosf(0.01f*t+3.14/5);
//	RC_Data.rcdata[4]=1500+500*sinf(0.01f*t+3.14/4);
//	RC_Data.rcdata[5]=1500+500*cosf(0.01f*t+3.14/3);
//	RC_Data.rcdata[6]=1500+500*sinf(0.01f*t+3.14/2);
//	RC_Data.rcdata[7]=1500+500*cosf(0.01f*t+3.14/2.5);
	
  
  for(uint16_t i=0;i<RC_CHL_MAX;i++)
	{	
		RC_Data.rcdata[i]=RC_Data.rcdata[i]+RC_Data.cal[i].offset;
		if(RC_Data.rcdata[i]>RC_Data.cal[i].max)  RC_Data.rcdata[i]=RC_Data.cal[i].max;
		if(RC_Data.rcdata[i]<RC_Data.cal[i].min)  RC_Data.rcdata[i]=RC_Data.cal[i].min;
	}	

  RC_Data.vbat_mv=2*3300*(ADC_value[0])/4095;	
	static uint16_t _check_cnt=0;
	_check_cnt++;
	if(_check_cnt%200==0)
	{
		if(RC_Data.vbat_mv<=RC_Data.safe_vbat_v*1000)  rc_beep.time=50;
		
		if(vbat<=RC_Data.flight_safe_vbat_v&&RC_Data.flight_safe_vbat_enable==1)  rc_beep.time=100;
	}
	
	
	
	//通道重映射
	RC_Data.rcdata_original[RC_ROLL_CHANNEL] =RC_Data.rcdata[RC_Data.rock_ch_remap[0]];
	RC_Data.rcdata_original[RC_PITCH_CHANNEL]=RC_Data.rcdata[RC_Data.rock_ch_remap[1]];
	RC_Data.rcdata_original[RC_THR_CHANNEL]	 =RC_Data.rcdata[RC_Data.rock_ch_remap[2]];
	RC_Data.rcdata_original[RC_YAW_CHANNEL]	 =RC_Data.rcdata[RC_Data.rock_ch_remap[3]];
	RC_Data.rcdata_original[RC_SWA_CHANNEL]	 =RC_Data.rcdata[RC_Data.func_ch_remap[0]+4];
	RC_Data.rcdata_original[RC_SWB_CHANNEL]  =RC_Data.rcdata[RC_Data.func_ch_remap[1]+4];
	RC_Data.rcdata_original[RC_SWC_CHANNEL]  =RC_Data.rcdata[RC_Data.func_ch_remap[2]+4];
	RC_Data.rcdata_original[RC_SWD_CHANNEL]  =RC_Data.rcdata[RC_Data.func_ch_remap[3]+4];
	RC_Data.rcdata_original[RC_VRA_CHANNEL]  =RC_Data.rcdata[RC_Data.func_ch_remap[4]+4];
	RC_Data.rcdata_original[RC_VRB_CHANNEL]  =RC_Data.rcdata[RC_Data.func_ch_remap[5]+4];
	

	uint16_t _cnt=0;
	rc_send_cnt++;
	if(rc_send_cnt==1)
	{
		g_NRFSendData[_cnt++]=0xA2;
		g_NRFSendData[_cnt++]=0xA1;
		g_NRFSendData[_cnt++]=0x01;
		
		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_ROLL_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_ROLL_CHANNEL]&0xff;

		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_PITCH_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_PITCH_CHANNEL]&0xff;

		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_THR_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_THR_CHANNEL]&0xff;
		
		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_YAW_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_YAW_CHANNEL]&0xff;

		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_SWA_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_SWA_CHANNEL]&0xff;

		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_SWB_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_SWB_CHANNEL]&0xff;

		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_SWC_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_SWC_CHANNEL]&0xff;
		
		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_SWD_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_SWD_CHANNEL]&0xff;	

		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_VRA_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_VRA_CHANNEL]&0xff;	
		
		g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_VRB_CHANNEL]>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_VRB_CHANNEL]&0xff;

		//失控保护通道设置
		g_NRFSendData[_cnt++]=RC_Data.lose_ctrl_protect;
		g_NRFSendData[_cnt++]=RC_Data.lose_ctrl_protect_channel;

		g_NRFSendData[_cnt++]=(RC_Data.lose_ctrl_protect_value>>8)&0xff;
		g_NRFSendData[_cnt++]=RC_Data.lose_ctrl_protect_value&0xff;
		
		g_NRFSendData[_cnt++]=0xFC;
		g_NRFSendData[_cnt++]=0xFF;
		uint8_t sum = 0;
		for(uint8_t i=0;i<_cnt;i++) sum ^= g_NRFSendData[i];
		g_NRFSendData[_cnt++]=sum;
		
 }
 else  if(rc_send_cnt==2)
 {
	 	if(_button.state[RIGHT].press==SHORT_PRESS)
		{
			rc_gps_okay=1;
			_button.state[RIGHT].press=NO_PRESS;
			rc_gps_cnt++;
			g_NRFSendData[_cnt++]=0xA2;
			g_NRFSendData[_cnt++]=0xA1;
			g_NRFSendData[_cnt++]=0x02;
			//遥控器解析的GPS数据发送
			g_NRFSendData[_cnt++]=rc_gps_okay;
			g_NRFSendData[_cnt++]=BYTE3(gps_pvt.lon);
			g_NRFSendData[_cnt++]=BYTE2(gps_pvt.lon);
			g_NRFSendData[_cnt++]=BYTE1(gps_pvt.lon);
			g_NRFSendData[_cnt++]=BYTE0(gps_pvt.lon);
			g_NRFSendData[_cnt++]=BYTE3(gps_pvt.lat);
			g_NRFSendData[_cnt++]=BYTE2(gps_pvt.lat);
			g_NRFSendData[_cnt++]=BYTE1(gps_pvt.lat);
			g_NRFSendData[_cnt++]=BYTE0(gps_pvt.lat);
			g_NRFSendData[_cnt++]=0x00;
			g_NRFSendData[_cnt++]=0x00;
			g_NRFSendData[_cnt++]=0x00;
			g_NRFSendData[_cnt++]=0x00;	
			g_NRFSendData[_cnt++]=0x00;
			g_NRFSendData[_cnt++]=0x00;	
			g_NRFSendData[_cnt++]=0x00;
			g_NRFSendData[_cnt++]=0x00;	
			g_NRFSendData[_cnt++]=0x00;
			g_NRFSendData[_cnt++]=0x00;	
			g_NRFSendData[_cnt++]=0x00;
			g_NRFSendData[_cnt++]=0x00;	
			g_NRFSendData[_cnt++]=0x00;
			g_NRFSendData[_cnt++]=0x00;	
			g_NRFSendData[_cnt++]=0x00;//27
			g_NRFSendData[_cnt++]=0xFC;
			g_NRFSendData[_cnt++]=0xFF;			
		}
		else
		{
			g_NRFSendData[_cnt++]=0xA2;
			g_NRFSendData[_cnt++]=0xA1;
			g_NRFSendData[_cnt++]=0x01;
			
			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_ROLL_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_ROLL_CHANNEL]&0xff;

			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_PITCH_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_PITCH_CHANNEL]&0xff;

			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_THR_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_THR_CHANNEL]&0xff;
			
			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_YAW_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_YAW_CHANNEL]&0xff;

			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_SWA_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_SWA_CHANNEL]&0xff;

			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_SWB_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_SWB_CHANNEL]&0xff;

			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_SWC_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_SWC_CHANNEL]&0xff;
			
			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_SWD_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_SWD_CHANNEL]&0xff;	

			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_VRA_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_VRA_CHANNEL]&0xff;	
			
			g_NRFSendData[_cnt++]=(RC_Data.rcdata_original[RC_VRB_CHANNEL]>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.rcdata_original[RC_VRB_CHANNEL]&0xff;

			//失控保护通道设置
			g_NRFSendData[_cnt++]=RC_Data.lose_ctrl_protect;
			g_NRFSendData[_cnt++]=RC_Data.lose_ctrl_protect_channel;

			g_NRFSendData[_cnt++]=(RC_Data.lose_ctrl_protect_value>>8)&0xff;
			g_NRFSendData[_cnt++]=RC_Data.lose_ctrl_protect_value&0xff;
			
			g_NRFSendData[_cnt++]=0xFC;
			g_NRFSendData[_cnt++]=0xFF;
			uint8_t sum1 = 0,sum2 = 0;
			for(uint8_t i=0;i<_cnt;i++) sum1 ^= g_NRFSendData[i];
			for(uint8_t i=0;i<_cnt;i++) sum2 += g_NRFSendData[i];
			g_NRFSendData[_cnt++]=sum1;
			g_NRFSendData[_cnt++]=sum2;
		}
		rc_send_cnt=0;
 }
}


systime  tim1_dealt;
void TIM1_UP_IRQHandler(void)//5ms刷新一次
{
  if( TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET )
  {
		Get_Systime(&tim1_dealt);
    Remote_Ctrl_Prase();//遥控器数据打包
		NRF24L01_State_Check(g_NRFRevData);//无线状态检查+接收回传数据
		if(Transparent_Update==1)//串口透明传输
		{
		  Transparent_Update=0;
		  NRF24L01_Duplex_TxPacket(Transparent_Data);
//      NRF24L01_TxPacket(Transparent_Data);	
		}
		else//发送遥控器数据
		{
	    NRF24L01_Duplex_TxPacket(g_NRFSendData);
//      NRF24L01_TxPacket(g_NRFSendData);				
		}	
		Read_Button_State_All();
		beep_run();
		Bling_Working(0);
		GPS_Data_Prase();
    TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
  }
}

systime  tim2_dealt;
void TIM2_IRQHandler(void)
{
  if( TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET )
  {
    Get_Systime(&tim2_dealt);		
		Usb_Hid_Receive();//USB接收查询
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);		
	}
}






















//	 if(NRF_Transparent_Update==1)
//	 {
//		 NRF_Transparent_Update=0;
//		Serial_Data_Send(NRF_Transparent_Data,NRF_Transparent_Cnt);								//串口透传发送
//		for(uint16_t i=0;i<NRF_Transparent_Cnt;i++)
//		{
//			NCLink_Data_Prase_Prepare(NRF_Transparent_Data[i]);
//		}
//	 } 

