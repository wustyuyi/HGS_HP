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
#include "main.h"//用户自己库函数头文件
#include "NCLink.h"


uint8_t NCLink_Head[2]={0xFF,0xFC};//数据帧头
uint8_t NCLink_End[2] ={0xA1,0xA2};//数据帧尾
uint8_t NCLink_Send_Ask_Flag[10]={0};//飞控接收获取参数命令请求，给地面站发送标志位
uint8_t NCLink_Send_Check_Flag[20]={0};//数据解析成功，飞控给地面站发送标志位
uint8_t nclink_databuf[100];//待发送数据缓冲区
uint8_t rc_update_flag=0;//遥控器数据更新标志位
uint8_t unlock_flag=0x02,takeoff_flag=0;//解锁、起飞标志位
uint8_t move_flag=0,mode_order=0;//SDK移动标志位、移动顺序
uint16_t move_distance=0;//SDK移动距离
uint8_t cal_flag=0,cal_step=0,cal_cmd=0,shutdown_now_cal_flag=0;//传感器校准标志位
/***************************************************************************************
@函数名：Serial_Data_Send(uint8_t *buf, uint32_t cnt)
@入口参数：buf:待发送数据
			     cnt:待发送字长
@出口参数：无
功能描述：串口发送函数
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void Serial_Data_Send(uint8_t *buf, uint32_t cnt)  
{
	//USART1_Send(buf,cnt);//用户移植时，重写此串口发送函数
  USART1_Send_Dma(buf,cnt);
	USB_TxWrite(buf,cnt);
}

/***************************************************************************************
@函数名：Pilot_Status_Tick(void) 
@入口参数：无
@出口参数：无
功能描述：飞控接收状态显示
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void Pilot_Status_Tick(void)  
{
	Bling_Set(&Light_R,500,100,0.2,0,GPIOC,GPIO_Pin_12,0);//用户移植时，重写此函数
}


union
{
unsigned char floatByte[4];
float floatValue;
}FloatUnion;
/***************************************************************************************
@函数名：void Float2Byte(float *FloatValue, unsigned char *Byte, unsigned char Subscript)
@入口参数：FloatValue:float值
			     Byte:数组
		       Subscript:指定从数组第几个元素开始写入
@出口参数：无
功能描述：将float数据转成4字节数据并存入指定地址
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void Float2Byte(float *FloatValue, unsigned char *Byte, unsigned char Subscript)
{
	FloatUnion.floatValue = (float)2;
	if(FloatUnion.floatByte[0] == 0)//小端模式
	{
		FloatUnion.floatValue = *FloatValue;
		Byte[Subscript]     = FloatUnion.floatByte[0];
		Byte[Subscript + 1] = FloatUnion.floatByte[1];
		Byte[Subscript + 2] = FloatUnion.floatByte[2];
		Byte[Subscript + 3] = FloatUnion.floatByte[3];
	}
	else//大端模式
	{
		FloatUnion.floatValue = *FloatValue;
		Byte[Subscript]     = FloatUnion.floatByte[3];
		Byte[Subscript + 1] = FloatUnion.floatByte[2];
		Byte[Subscript + 2] = FloatUnion.floatByte[1];
		Byte[Subscript + 3] = FloatUnion.floatByte[0];
	}
}


/***************************************************************************************
@函数名：void Byte2Float(unsigned char *Byte, unsigned char Subscript, float *FloatValue)
@入口参数：Byte:数组
			     Subscript:指定从数组第几个元素开始写入
		       FloatValue:float值
@出口参数：无
功能描述：从指定地址将4字节数据转成float数据
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void Byte2Float(unsigned char *Byte, unsigned char Subscript, float *FloatValue)
{
	FloatUnion.floatByte[0]=Byte[Subscript];
	FloatUnion.floatByte[1]=Byte[Subscript + 1];
	FloatUnion.floatByte[2]=Byte[Subscript + 2];
	FloatUnion.floatByte[3]=Byte[Subscript + 3];
	*FloatValue=FloatUnion.floatValue;
}


//第一帧数据，功能字0x01  数据长度24
float pitch=0,roll=0,yaw=0;//姿态角
float pitch_gyro=0,roll_gyro=0,yaw_gyro=0;//姿态角速度
float vbat=0;
float imu_temp=0;
uint8_t fly_mode=0;//飞行模式
uint8_t armed_flag=0;//解锁标志

//第二帧数据，功能字0x02  数据长度18
int16_t ax,ay,az;
int16_t gx,gy,gz;
int16_t mx,my,mz;


//第三帧数据，功能字0x03  数据长度16
int16_t nrc[8];

//第四帧数据，功能字0x04  数据长度14
double gps_lng=0,gps_lat=0,gps_alt=0;
int16_t gps_pdop=0;
uint8_t gps_state=0;
uint8_t gps_satellite_num=0;

//第五帧数据，功能字0x05  数据长度8
float lat_pos_obs=0,lng_pos_obs=0;
float lat_vel_obs=0,lng_vel_obs=0;

//第六帧数据，功能字0x06  数据长度16
float alt_obs_baro=0,alt_obs_ult=0;
float opt_vel_p=0,opt_vel_r=0;

//第七帧数据，功能字0x07  数据长度8
float alt_pos_fus=0;//融合高度
float alt_vel_fus=0;//融合高度
float alt_accel_fus=0;//融合高度

//第八帧数据，功能字0x08  数据长度24
float lat_pos_fusion=0,lng_pos_fusion=0;
float lat_vel_fusion=0,lng_vel_fusion=0;
float lat_accel_fusion=0,lng_accel_fusion=0;

//第九帧数据，功能字0x09  数据长度36
float userdata[9]={0};

//第10、11、12、13、14、15帧数据，功能字0x0A、0x0B、0x0C、0x0D、0x0E、0x0F  数据长度18
uint16_t kp[18]={0};
uint16_t ki[18]={0};
uint16_t kd[18]={0};


//第16帧数据，功能字11  数据长度36
uint8_t gyro_auto_cal_flag=0;
float gyro_x_raw=0;
float gyro_y_raw=0;
float gyro_z_raw=0;
float acce_x_raw=0;
float acce_y_raw=0;
float acce_z_raw=0;
float mag_x_raw=0;
float mag_y_raw=0;
float mag_z_raw=0;


//第17帧数据，功能字12  数据长度56
float gyro_x_offset;
float gyro_y_offset;
float gyro_z_offset;
float acce_x_offset;
float acce_y_offset;
float acce_z_offset;
float acce_x_scale;
float acce_y_scale;
float acce_z_scale;
float mag_x_offset;
float mag_y_offset;
float mag_z_offset;
float pitch_offset;
float roll_offset;


//第16帧数据，功能字0x10  数据长度16
uint16_t targeheight,safeheight,safevbat,maxheight;
uint16_t maxradius,maxupvel,maxdownvel,maxhorvel;








/***************************************************************************************
@函数名：NCLink_Data_Prase_Prepare(uint8_t data)
@入口参数：data:待解析数据
@出口参数：无
功能描述：飞控解析地面站数据准备，本函数放入串口中断函数内
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Data_Prase_Prepare(uint8_t data)//地面站数据解析
{
  static uint8_t buf[100];
  static uint8_t data_len = 0,data_cnt = 0;
  static uint8_t state = 0;
  if(state==0&&data==NCLink_Head[0])//判断帧头1
  {
    state=1;
    buf[0]=data;
  }
  else if(state==1&&data==NCLink_Head[1])//判断帧头2
  {
    state=2;
    buf[1]=data;
  }
  else if(state==2&&data<0XF1)//功能字节
  {
    state=3;
    buf[2]=data;
  }
  else if(state==3&&data<100)//有效数据长度
  {
    state = 4;
    buf[3]=data;
    data_len = data;
    data_cnt = 0;
  }
  else if(state==4&&data_len>0)//数据接收
  {
    data_len--;
    buf[4+data_cnt++]=data;
    if(data_len==0)  state = 5;
  }
  else if(state==5)//异或校验
  {
    state = 6;
    buf[4+data_cnt++]=data;
  }
	else if(state==6&&data==NCLink_End[0])//帧尾0
	{
			state = 7;
			buf[4+data_cnt++]=data;
	}
	else if(state==7&&data==NCLink_End[1])//帧尾1
	{
			state = 0;
			buf[4+data_cnt]=data;
		  NCLink_Data_Prase_Process(buf,data_cnt+5);//数据解析
	}
  else state = 0;
}

/***************************************************************************************
@函数名：NCLink_Data_Prase_Process(uint8_t *data_buf,uint8_t num)
@入口参数：data_buf:待解析数据帧
					 num:数据帧长
@出口参数：无
功能描述：根据提取出的数据帧，解析每一帧数据数据
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Data_Prase_Process(uint8_t *data_buf,uint8_t num)//飞控数据解析进程
{
  uint8_t sum = 0;
  for(uint8_t i=0;i<(num-3);i++)  sum ^= *(data_buf+i);
  if(!(sum==*(data_buf+num-3)))    																					return;//判断sum	
	if(!(*(data_buf)==NCLink_Head[0]&&*(data_buf+1)==NCLink_Head[1]))         return;//判断帧头
	if(!(*(data_buf+num-2)==NCLink_End[0]&&*(data_buf+num-1)==NCLink_End[1])) return;//帧尾校验  
		if(*(data_buf+2)==0X01)//飞控姿态基本信息
		{
			 roll =0.01f*((int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
			 pitch=0.01f*((int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
			 yaw  =0.01f*((int16_t)(*(data_buf+8)<<8)|*(data_buf+9));

			 roll_gyro =0.01f*((int32_t)(*(data_buf+10)<<24)|(*(data_buf+11)<<16)|(*(data_buf+12)<<8)|*(data_buf+13));
			 pitch_gyro =0.01f*((int32_t)(*(data_buf+14)<<24)|(*(data_buf+15)<<16)|(*(data_buf+16)<<8)|*(data_buf+17));
			 yaw_gyro =0.01f*((int32_t)(*(data_buf+18)<<24)|(*(data_buf+19)<<16)|(*(data_buf+20)<<8)|*(data_buf+21));

			 imu_temp =0.01f*((int16_t)(*(data_buf+22)<<8)|*(data_buf+23));
			 vbat=0.01f*((int16_t)(*(data_buf+24)<<8)|*(data_buf+25));

			 fly_mode=*(data_buf+26);
			 armed_flag=*(data_buf+27);
			 Pilot_Status_Tick();
		}
		else if(*(data_buf+2)==0X02)//IMU原始数据
		{
			ax=(int16_t)(*(data_buf+4)<<8)|*(data_buf+5);
			ay=(int16_t)(*(data_buf+6)<<8)|*(data_buf+7);
			az=(int16_t)(*(data_buf+8)<<8)|*(data_buf+9);
			gx=(int16_t)(*(data_buf+10)<<8)|*(data_buf+11);
			gy=(int16_t)(*(data_buf+12)<<8)|*(data_buf+13);
			gz=(int16_t)(*(data_buf+14)<<8)|*(data_buf+15);
			mx=(int16_t)(*(data_buf+16)<<8)|*(data_buf+17);
			my=(int16_t)(*(data_buf+18)<<8)|*(data_buf+19);
			mz=(int16_t)(*(data_buf+20)<<8)|*(data_buf+21);
		}
	    else if(*(data_buf+2)==0X03)//遥控器各个通道数据
    {
        nrc[0]=(int16_t)(*(data_buf+4)<<8)|*(data_buf+5);
        nrc[1]=(int16_t)(*(data_buf+6)<<8)|*(data_buf+7);
        nrc[2]=(int16_t)(*(data_buf+8)<<8)|*(data_buf+9);
        nrc[3]=(int16_t)(*(data_buf+10)<<8)|*(data_buf+11);
        nrc[4]=(int16_t)(*(data_buf+12)<<8)|*(data_buf+13);
        nrc[5]=(int16_t)(*(data_buf+14)<<8)|*(data_buf+15);
        nrc[6]=(int16_t)(*(data_buf+16)<<8)|*(data_buf+17);
        nrc[7]=(int16_t)(*(data_buf+18)<<8)|*(data_buf+19);
    }
    else if(*(data_buf+2)==0X04)//GPS定位数据
    {
        gps_lng=0.0000001f*((int32_t)(*(data_buf+4)<<24)|(*(data_buf+5)<<16)|(*(data_buf+6)<<8)|*(data_buf+7));
        gps_lat=0.0000001f*((int32_t)(*(data_buf+8)<<24)|(*(data_buf+9)<<16)|(*(data_buf+10)<<8)|*(data_buf+11));
        gps_alt=0.001f*((int32_t)(*(data_buf+12)<<24)|(*(data_buf+13)<<16)|(*(data_buf+14)<<8)|*(data_buf+15));
        gps_pdop=(int16_t)(*(data_buf+16)<<8)|*(data_buf+17);
        gps_state=*(data_buf+18);
        gps_satellite_num=*(data_buf+19);
    }
		else if(*(data_buf+2)==0X05)//GPS速度数据
    {
        lat_pos_obs =0.01f*((int32_t)(*(data_buf+4)<<24)|(*(data_buf+5)<<16)|(*(data_buf+6)<<8)|*(data_buf+7));
        lng_pos_obs =0.01f*((int32_t)(*(data_buf+8)<<24)|(*(data_buf+9)<<16)|(*(data_buf+10)<<8)|*(data_buf+11));
        lat_vel_obs =0.01f*((int32_t)(*(data_buf+12)<<24)|(*(data_buf+13)<<16)|(*(data_buf+14)<<8)|*(data_buf+15));
        lng_vel_obs =0.01f*((int32_t)(*(data_buf+16)<<24)|(*(data_buf+17)<<16)|(*(data_buf+18)<<8)|*(data_buf+19));
		}
		else if(*(data_buf+2)==0X06)//GPS速度数据
    {
        alt_obs_baro=0.01f*((int32_t)(*(data_buf+4)<<24)|(*(data_buf+5)<<16)|(*(data_buf+6)<<8)|*(data_buf+7));
        alt_obs_ult =0.01f*((int32_t)(*(data_buf+8)<<24)|(*(data_buf+9)<<16)|(*(data_buf+10)<<8)|*(data_buf+11));
        opt_vel_p   =0.01f*((int32_t)(*(data_buf+12)<<24)|(*(data_buf+13)<<16)|(*(data_buf+14)<<8)|*(data_buf+15));
        opt_vel_r   =0.01f*((int32_t)(*(data_buf+16)<<24)|(*(data_buf+17)<<16)|(*(data_buf+18)<<8)|*(data_buf+19));
		}
		else if(*(data_buf+2)==0X07)
    {
        alt_pos_fus=0.01f*((int32_t)(*(data_buf+4)<<24)|(*(data_buf+5)<<16)|(*(data_buf+6)<<8)|*(data_buf+7));
        alt_vel_fus=0.01f*((int32_t)(*(data_buf+8)<<24)|(*(data_buf+9)<<16)|(*(data_buf+10)<<8)|*(data_buf+11));
        alt_accel_fus=0.01f*((int32_t)(*(data_buf+12)<<24)|(*(data_buf+13)<<16)|(*(data_buf+14)<<8)|*(data_buf+15));
		}
		else if(*(data_buf+2)==0X08)
    {
        lat_pos_fusion   =0.01*((int32_t)(*(data_buf+4)<<24)|(*(data_buf+5)<<16)|(*(data_buf+6)<<8)|*(data_buf+7));
        lng_pos_fusion   =0.01*((int32_t)(*(data_buf+8)<<24)|(*(data_buf+9)<<16)|(*(data_buf+10)<<8)|*(data_buf+11));
        lat_vel_fusion   =0.01*((int32_t)(*(data_buf+12)<<24)|(*(data_buf+13)<<16)|(*(data_buf+14)<<8)|*(data_buf+15));
        lng_vel_fusion   =0.01*((int32_t)(*(data_buf+16)<<24)|(*(data_buf+17)<<16)|(*(data_buf+18)<<8)|*(data_buf+19));
        lat_accel_fusion =0.01*((int32_t)(*(data_buf+20)<<24)|(*(data_buf+21)<<16)|(*(data_buf+22)<<8)|*(data_buf+23));
        lng_accel_fusion =0.01*((int32_t)(*(data_buf+24)<<24)|(*(data_buf+25)<<16)|(*(data_buf+26)<<8)|*(data_buf+27));
		}
		else if(*(data_buf+2)==0X09)
    {
        Byte2Float(data_buf,4,&userdata[0]);
        Byte2Float(data_buf,8,&userdata[1]);
        Byte2Float(data_buf,12,&userdata[2]);
        Byte2Float(data_buf,16,&userdata[3]);
        Byte2Float(data_buf,20,&userdata[4]);
        Byte2Float(data_buf,24,&userdata[5]);
		}
		else if(*(data_buf+2)==0X0A)                             //PID1-3
    {
        kp[0]=((int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
        ki[0]=((int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
        kd[0]=((int16_t)(*(data_buf+8)<<8)|*(data_buf+9));
        kp[1]=((int16_t)(*(data_buf+10)<<8)|*(data_buf+11));
        ki[1]=((int16_t)(*(data_buf+12)<<8)|*(data_buf+13));
        kd[1]=((int16_t)(*(data_buf+14)<<8)|*(data_buf+15));
        kp[2]=((int16_t)(*(data_buf+16)<<8)|*(data_buf+17));
        ki[2]=((int16_t)(*(data_buf+18)<<8)|*(data_buf+19));
        kd[2]=((int16_t)(*(data_buf+20)<<8)|*(data_buf+21));
    }
    else if(*(data_buf+2)==0X0B)                             //PID4-6
    {
        kp[3]=((int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
        ki[3]=((int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
        kd[3]=((int16_t)(*(data_buf+8)<<8)|*(data_buf+9));
        kp[4]=((int16_t)(*(data_buf+10)<<8)|*(data_buf+11));
        ki[4]=((int16_t)(*(data_buf+12)<<8)|*(data_buf+13));
        kd[4]=((int16_t)(*(data_buf+14)<<8)|*(data_buf+15));
        kp[5]=((int16_t)(*(data_buf+16)<<8)|*(data_buf+17));
        ki[5]=((int16_t)(*(data_buf+18)<<8)|*(data_buf+19));
        kd[5]=((int16_t)(*(data_buf+20)<<8)|*(data_buf+21));
    }
    else if(*(data_buf+2)==0X0C)                             //PID7-9
    {
        kp[6]=((int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
        ki[6]=((int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
        kd[6]=((int16_t)(*(data_buf+8)<<8)|*(data_buf+9));
        kp[7]=((int16_t)(*(data_buf+10)<<8)|*(data_buf+11));
        ki[7]=((int16_t)(*(data_buf+12)<<8)|*(data_buf+13));
        kd[7]=((int16_t)(*(data_buf+14)<<8)|*(data_buf+15));
        kp[8]=((int16_t)(*(data_buf+16)<<8)|*(data_buf+17));
        ki[8]=((int16_t)(*(data_buf+18)<<8)|*(data_buf+19));
        kd[8]=((int16_t)(*(data_buf+20)<<8)|*(data_buf+21));
    }
    else if(*(data_buf+2)==0X0D)                             //PID7-9
    {
        kp[9]=((int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
        ki[9]=((int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
        kd[9]=((int16_t)(*(data_buf+8)<<8)|*(data_buf+9));
        kp[10]=((int16_t)(*(data_buf+10)<<8)|*(data_buf+11));
        ki[10]=((int16_t)(*(data_buf+12)<<8)|*(data_buf+13));
        kd[10]=((int16_t)(*(data_buf+14)<<8)|*(data_buf+15));
        kp[11]=((int16_t)(*(data_buf+16)<<8)|*(data_buf+17));
        ki[11]=((int16_t)(*(data_buf+18)<<8)|*(data_buf+19));
        kd[11]=((int16_t)(*(data_buf+20)<<8)|*(data_buf+21));
    }
    else if(*(data_buf+2)==0X0E)                             //PID7-9
    {
        kp[12]=((int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
        ki[12]=((int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
        kd[12]=((int16_t)(*(data_buf+8)<<8)|*(data_buf+9));
        kp[13]=((int16_t)(*(data_buf+10)<<8)|*(data_buf+11));
        ki[13]=((int16_t)(*(data_buf+12)<<8)|*(data_buf+13));
        kd[13]=((int16_t)(*(data_buf+14)<<8)|*(data_buf+15));
        kp[14]=((int16_t)(*(data_buf+16)<<8)|*(data_buf+17));
        ki[14]=((int16_t)(*(data_buf+18)<<8)|*(data_buf+19));
        kd[14]=((int16_t)(*(data_buf+20)<<8)|*(data_buf+21));
    }
    else if(*(data_buf+2)==0X0F)                             //PID7-9
    {
        kp[15]=((int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
        ki[15]=((int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
        kd[15]=((int16_t)(*(data_buf+8)<<8)|*(data_buf+9));
        kp[16]=((int16_t)(*(data_buf+10)<<8)|*(data_buf+11));
        ki[16]=((int16_t)(*(data_buf+12)<<8)|*(data_buf+13));
        kd[16]=((int16_t)(*(data_buf+14)<<8)|*(data_buf+15));
        kp[17]=((int16_t)(*(data_buf+16)<<8)|*(data_buf+17));
        ki[17]=((int16_t)(*(data_buf+18)<<8)|*(data_buf+19));
        kd[17]=((int16_t)(*(data_buf+20)<<8)|*(data_buf+21));
       
    }
    else if(*(data_buf+2)==0X10)
    {
        targeheight=((int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
        safeheight=((int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
        safevbat=((int16_t)(*(data_buf+8)<<8)|*(data_buf+9));
        maxheight=((int16_t)(*(data_buf+10)<<8)|*(data_buf+11));
        maxradius=((int16_t)(*(data_buf+12)<<8)|*(data_buf+13));
        maxupvel=((int16_t)(*(data_buf+14)<<8)|*(data_buf+15));
        maxdownvel=((int16_t)(*(data_buf+16)<<8)|*(data_buf+17));
        maxhorvel=((int16_t)(*(data_buf+18)<<8)|*(data_buf+19));
    }
		else if(*(data_buf+2)==0X11)
    {
        gyro_auto_cal_flag=*(data_buf+4);
        Byte2Float(data_buf, 5,&gyro_x_raw);
        Byte2Float(data_buf, 9,&gyro_y_raw);
        Byte2Float(data_buf,13,&gyro_z_raw);
        Byte2Float(data_buf,17,&acce_x_raw);
        Byte2Float(data_buf,21,&acce_y_raw);
        Byte2Float(data_buf,25,&acce_z_raw);
    }
    else if(*(data_buf+2)==0X12)
    {
        Byte2Float(data_buf, 4,&mag_x_raw);
        Byte2Float(data_buf, 8,&mag_y_raw);
        Byte2Float(data_buf,12,&mag_z_raw);
    }
    else if(*(data_buf+2)==0X13)
    {
        Byte2Float(data_buf,4, &gyro_x_offset);
        Byte2Float(data_buf,8, &gyro_y_offset);
        Byte2Float(data_buf,12,&gyro_z_offset);
        Byte2Float(data_buf,16,&mag_x_offset);
        Byte2Float(data_buf,20,&mag_y_offset);
        Byte2Float(data_buf,24,&mag_z_offset);
    }
    else if(*(data_buf+2)==0X14)
    {
        Byte2Float(data_buf,4, &acce_x_offset);
        Byte2Float(data_buf,8, &acce_y_offset);
        Byte2Float(data_buf,12,&acce_z_offset);
        Byte2Float(data_buf,16,&acce_x_scale);
        Byte2Float(data_buf,20,&acce_y_scale);
        Byte2Float(data_buf,24,&acce_z_scale);

    }
    else if(*(data_buf+2)==0X15)
    {
        Byte2Float(data_buf,4, &pitch_offset);
        Byte2Float(data_buf,8, &roll_offset);
        //uint8_t ch=0x07;
        //emit redrawparameter(ch);
    }
}





void NCLink_GS_Send_RCData(uint16_t ch0,uint16_t ch1,uint16_t ch2,uint16_t ch3,
	                         uint16_t ch4,uint16_t ch5,uint16_t ch6,uint16_t ch7,
													 uint16_t ch8,uint16_t ch9,uint8_t unlock_flag,uint8_t takeoff_flag)//地面站指令发送RC数据
{
  uint8_t data_to_send[50];
  uint8_t sum = 0,i=0,cnt=0;
  uint16_t _temp;
  data_to_send[cnt++]=NCLink_Head[1];
  data_to_send[cnt++]=NCLink_Head[0];
  data_to_send[cnt++]=0x09;
  data_to_send[cnt++]=0;

  _temp = ch0;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);
  _temp = ch1;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);
  _temp = ch2;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);
  _temp = ch3;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);
  _temp = ch4;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);
  _temp = ch5;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);
  _temp = ch6;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);
  _temp = ch7;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);
  _temp = ch8;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);
  _temp = ch9;
  data_to_send[cnt++]=BYTE1(_temp);
  data_to_send[cnt++]=BYTE0(_temp);


  data_to_send[cnt++]=BYTE0(unlock_flag);
  data_to_send[cnt++]=BYTE0(takeoff_flag);

  data_to_send[3] = cnt-4;
  for(i=0;i<cnt;i++) sum ^= data_to_send[i];
  data_to_send[cnt++]=sum;
  data_to_send[cnt++]=NCLink_End[0];
  data_to_send[cnt++]=NCLink_End[1];
//  
//	NRF24L01_CE_L;			//StandBy I模式	
//	NRF24L01_Write_Buf(WRITE_REG_NRF + RX_ADDR_P0, (u8*)rc_pair.tx_addr,TX_ADR_WIDTH); // 装载接收端地址
//	NRF24L01_Write_Buf(WR_TX_PLOAD, data_to_send, cnt); 			 // 装载数据	
//	NRF24L01_CE_H;
	NRF24L01_TxPacket(data_to_send);
}
