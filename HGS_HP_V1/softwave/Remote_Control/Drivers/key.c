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
#include "key.h"






rc_buttton _button;
void Key_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;  	  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	

	_button.state[UP].port=GPIOB;
	_button.state[UP].pin=GPIO_Pin_5;
	_button.state[UP].value=1;
	_button.state[UP].last_value=1;
	
	_button.state[DOWN].port=GPIOB;
	_button.state[DOWN].pin=GPIO_Pin_6;
	_button.state[DOWN].value=1;
	_button.state[DOWN].last_value=1;

	_button.state[LEFT].port=GPIOB;
	_button.state[LEFT].pin=GPIO_Pin_4;
	_button.state[LEFT].value=1;
	_button.state[LEFT].last_value=1;	
	
	_button.state[RIGHT].port=GPIOB;
	_button.state[RIGHT].pin=GPIO_Pin_7;	
	_button.state[RIGHT].value=1;
	_button.state[RIGHT].last_value=1;	
		
	_button.state[EXIT].port=GPIOC;
	_button.state[EXIT].pin=GPIO_Pin_0;
	_button.state[EXIT].value=1;
	_button.state[EXIT].last_value=1;

	_button.state[ENTER].port=GPIOC;
	_button.state[ENTER].pin=GPIO_Pin_3;
	_button.state[ENTER].value=1;
	_button.state[ENTER].last_value=1;
	
	_button.state[SWITCH_UP].port=GPIOC;
	_button.state[SWITCH_UP].pin=GPIO_Pin_2;
	_button.state[SWITCH_UP].value=1;
	_button.state[SWITCH_UP].last_value=1;
	
	_button.state[SWITCH_DOWN].port=GPIOC;
	_button.state[SWITCH_DOWN].pin=GPIO_Pin_1;
	_button.state[SWITCH_DOWN].value=1;
	_button.state[SWITCH_DOWN].last_value=1;
}

void Read_Button_State_One(button_state *button)
{
  button->value=GPIO_ReadInputDataBit(button->port,button->pin);
	if(button->value==0)
	{
		if(button->last_value==1)//首次按下
		{
			button->press_time=millis();//记录按下的时间点
			button->in_time=millis();//记录按下的时间点
			button->in_press_cnt=0;
		}
		else
		{
			if(millis()-button->in_time>IN_PRESS_LIMIT)//持续按下
			{
				button->in_time=millis();
				button->press=IN_PRESS;
				rc_beep.time=1;
				if(button->press==IN_PRESS)  button->in_press_cnt++;
			}
		}
	}
  else
	{
		if(button->last_value==0)//按下后释放
		{
			button->release_time=millis();//记录释放时的时间
			if(button->release_time-button->press_time>LONG_PRESS_LIMIT)
			{
			   button->press=LONG_PRESS;
				 rc_beep.time=50;
			}
			else
			{
			   button->press=SHORT_PRESS;
				 rc_beep.time=10;
			}
		}
	}
	button->last_value=button->value;
}


void Read_Button_State_All(void)
{
  for(uint16_t i=0;i<BUTTON_NUM;i++)
	{
	  Read_Button_State_One(&_button.state[i]);
	}
}

