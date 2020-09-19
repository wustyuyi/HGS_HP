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
#include "ADC.h"

uint16_t ADC_value[7];

/* 端口配置初始化 */
void ADC_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_initStructure;    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_initStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
	                              GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	    
	GPIO_initStructure.GPIO_Mode = GPIO_Mode_AIN;								    
	GPIO_Init(GPIOA,&GPIO_initStructure);	
}


/* adc配置 */ 
void ADC_Config(void)
{
		ADC_InitTypeDef ADC_initStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

		ADC_initStructure.ADC_ContinuousConvMode = DISABLE;					          //单次转换模式，每次由定时器4通道4触发采样开始		
		ADC_initStructure.ADC_DataAlign = ADC_DataAlign_Right;		          	//数据右对齐				
		ADC_initStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T4_CC4;	//外部定时器4通道4定时触发	
		ADC_initStructure.ADC_Mode = ADC_Mode_Independent;							
		ADC_initStructure.ADC_NbrOfChannel = 7;										
		ADC_initStructure.ADC_ScanConvMode = ENABLE;		                      //扫描模式						
		ADC_Init(ADC1,&ADC_initStructure);

		ADC_Cmd(ADC1,ENABLE);

		ADC_DMACmd(ADC1,ENABLE);

		RCC_ADCCLKConfig(RCC_PCLK2_Div8);                           //ADC时钟分频											
																																//通道配置，采样时间设置
		ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_71Cycles5);	
		ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_71Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_71Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_71Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_4,5,ADC_SampleTime_71Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_5,6,ADC_SampleTime_71Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_6,7,ADC_SampleTime_71Cycles5);

		ADC_ResetCalibration(ADC1);	                                              //复位校准				
		while(ADC_GetCalibrationStatus(ADC1));		                                //等待
		ADC_StartCalibration(ADC1);					                                			//启动校准
		while(ADC_GetCalibrationStatus(ADC1));		                                //等待校准完成

		ADC_ExternalTrigConvCmd(ADC1,ENABLE);	                                    //外部触发使能
}


void ADC_DMA_Config(void)
{
	DMA_InitTypeDef DMA_initStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_initStructure.DMA_BufferSize = 7;										
	DMA_initStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	                        //传输方向：外设->内存						
	DMA_initStructure.DMA_M2M = DMA_M2M_Disable;								
  DMA_initStructure.DMA_MemoryBaseAddr = (u32)ADC_value;				        
	DMA_initStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //DMA传输的内存数据大小：半字为单位			
	DMA_initStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						//内存地址自增
	DMA_initStructure.DMA_Mode = DMA_Mode_Circular;								
	DMA_initStructure.DMA_PeripheralBaseAddr = ((u32)&ADC1->DR);	            //外设地址			
	DMA_initStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//DMA传输的外设数据大小：半字为单位
	DMA_initStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//外设地址不变
	DMA_initStructure.DMA_Priority = DMA_Priority_Medium;						
	DMA_Init(DMA1_Channel1,&DMA_initStructure);
    
  DMA_ClearITPendingBit(DMA1_IT_TC1);			    

	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);	
    
	DMA_Cmd(DMA1_Channel1,ENABLE);	
}


//定时器初始化
void Tim4_Init(void)
{ 
	TIM_TimeBaseInitTypeDef TIM_timeBaseStucture;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_timeBaseStucture.TIM_ClockDivision = TIM_CKD_DIV1;       
	TIM_timeBaseStucture.TIM_Prescaler = 72-1;                	 
	TIM_timeBaseStucture.TIM_CounterMode = TIM_CounterMode_Up;	 
	TIM_timeBaseStucture.TIM_Period = 20000-1;		                //20ms周期			
	TIM_TimeBaseInit(TIM4,&TIM_timeBaseStucture);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 5000;					        //5ms触发	     
	TIM_OC4Init(TIM4,&TIM_OCInitStructure);
	
	TIM_ARRPreloadConfig(TIM4,ENABLE);							 
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);			 
	
	TIM_Cmd(TIM4,ENABLE);	    
}


void ADC_Config_All(void)
{
	ADC_GPIO_Init();
	ADC_Config();
	ADC_DMA_Config();
	Tim4_Init();
}

