/*----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：540707961
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               修改日期:2018/8/30
*               版本：慧飞者——V1.0.1
*               版权所有，盗版必究。
*               Copyright(C) 武汉科技大学无名科创团队 2017-2025
*               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _FLIGHT_PARAMETER_TABLE_H_
#define _FLIGHT_PARAMETER_TABLE_H_


#define FLASH_EEPROM_ENABLE 1
#define PARAMETER_TABLE_STARTADDR 0x0801F000//0x0803C000 //0x08060000 
#define PARAMETER_TABLE_STARTADDR_EEPROM 100


#define FLIGHT_PARAMETER_TABLE_NUM  100
typedef struct
{
   float Parameter_Table[FLIGHT_PARAMETER_TABLE_NUM];
}FLIGHT_PARAMETER;


typedef enum
{
  RC_CAL_ROLL_MIN=0,
	RC_CAL_ROLL_MAX,
	RC_CAL_ROLL_OFFSET,
	RC_CAL_PITCH_MIN,
	RC_CAL_PITCH_MAX,
	RC_CAL_PITCH_OFFSET,
	RC_CAL_THR_MIN,
	RC_CAL_THR_MAX,
	RC_CAL_THR_OFFSET,
 	RC_CAL_YAW_MIN,
	RC_CAL_YAW_MAX,
	RC_CAL_YAW_OFFSET,
	RC_CAL_CH5_MIN,
	RC_CAL_CH5_MAX,
	RC_CAL_CH5_OFFSET,
	RC_CAL_CH6_MIN,
	RC_CAL_CH6_MAX,
	RC_CAL_CH6_OFFSET,	
	RC_CAL_CH7_MIN,
	RC_CAL_CH7_MAX,
	RC_CAL_CH7_OFFSET,	
	RC_CAL_CH8_MIN,
	RC_CAL_CH8_MAX,
	RC_CAL_CH8_OFFSET,
	RC_CAL_CH9_MIN,
	RC_CAL_CH9_MAX,
	RC_CAL_CH9_OFFSET,
	RC_CAL_CH10_MIN,
	RC_CAL_CH10_MAX,
	RC_CAL_CH10_OFFSET,
	RC_MAP_CH1,
	RC_MAP_CH2,
	RC_MAP_CH3,
	RC_MAP_CH4,
	RC_MAP_CH5,
  RC_MAP_CH6,
	RC_MAP_CH7,
	RC_MAP_CH8,
	RC_MAP_CH9,
	RC_MAP_CH10,
	LOSE_CTRL_PROTECT_ENABLE,
	LOSE_CTRL_PROTECT_CHL,
	LOSE_CTRL_PROTECT_VALUE,
	RC_SAFE_VOLTAGE,
	FLIGHT_SAFE_VOLTAGE,
	FLIGHT_SAFE_VOLTAGE_ENABLE,
	RC_PAIR_CHL,
	RC_TX_ADDR0,
	RC_TX_ADDR1,
	RC_TX_ADDR2,
	RC_TX_ADDR3,
	RC_TX_ADDR4,
	FLIGHT_PARAMETER_NUM,
}FLIGHT_PARAMETER_TABLE;




void ReadFlashParameterALL(volatile FLIGHT_PARAMETER *WriteData);
uint8_t ReadFlashParameterOne(uint16_t Label,float *ReadData);
uint8_t ReadFlashParameterTwo(uint16_t Label,float *ReadData1,float *ReadData2);
uint8_t ReadFlashParameterThree(uint16_t Label,float *ReadData1,float *ReadData2,float *ReadData3);
   
   
void WriteFlashParameter(uint16_t Label,float WriteData,volatile FLIGHT_PARAMETER *Table);
void WriteFlashParameter_Two(uint16_t Label,
                         float WriteData1,
                         float WriteData2,
                         volatile FLIGHT_PARAMETER *Table);
void WriteFlashParameter_Three(uint16_t Label,
                         float WriteData1,
                         float WriteData2,
                         float WriteData3,
                         volatile FLIGHT_PARAMETER *Table);
uint8_t ReadFlashParameterTwo(uint16_t Label,float *ReadData1,float *ReadData2);
extern volatile FLIGHT_PARAMETER Table_Parameter;
extern float Table_Parameter_Read[FLIGHT_PARAMETER_TABLE_NUM];
#endif

