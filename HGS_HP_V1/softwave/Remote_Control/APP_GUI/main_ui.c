#include "main.h" 
#include "main_ui.h"


// constrain a value
float constrain_float(float amt, float low, float high) 
{
  // the check for NaN as a float prevents propogation of
  // floating point errors through any function that uses
  // constrain_float(). The normal float semantics already handle -Inf
  // and +Inf
  if (isnan(amt)) {
    return (low+high)*0.5f;
  }
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}


const unsigned char gps_ico[]={ 
0x0F,0xE0,0x1F,0xF0,0x38,0x38,0x30,0x18,0x61,0x0C,0x63,0x8C,0x67,0xCC,0x63,0x8C,0x31,0x18,0x38,0x38,0x18,0x30,0x0C,0x60,0x06,0xC0,0x03,0x80,0x01,0x00,/*"F:\NCQ\V1.0\无名创新遥控器\gps (3).bmp",0*/
};/* (15 X 15 )*/
const unsigned char signal_ico_no[]={
0x88,0x00,0xE0,0x50,0x00,0xE0,0x20,0x0E,0xE0,0x50,0x0E,0xE0,0x88,0x0E,0xE0,0x00,0xEE,0xE0,0x00,0xEE,0xE0,0x00,0xEE,0xE0,0x0E,0xEE,0xE0,0x0E,0xEE,0xE0,0xEE,0xEE,
0xE0,0xEE,0xEE,0xE0,0xEE,0xEE,0xE0,0xEE,0xEE,0xE0,0xEE,0xEE,0xE0,/*"F:\NCQ\V1.0\无名创新遥控器\sigal.bmp",0*/
};/* (20 X 15 )*/
const unsigned char signal_ico_okay[]={
0x00,0x00,0x70,0xE9,0x00,0x70,0xAA,0x07,0x70,0xAC,0x07,0x70,0xAA,0x07,0x70,0xE9,0x77,0x70,0x00,0x77,0x70,0x00,0x77,0x70,0x0E,0x77,0x70,0x0E,0x77,0x70,0xEE,0x77,
0x70,0xEE,0x77,0x70,0xEE,0x77,0x70,0xEE,0x77,0x70,0xEE,0x77,0x70
};/* (20 X 15 )*/
const unsigned char lock_ico[]={
0x03,0x80,0x0F,0xE0,0x1F,0xF0,0x18,0x30,0x18,0x30,0x18,0x30,0x18,0x30,0x3F,0xF8,0x3F,0xF8,0x3F,0xF8,0x3F,0xF8,0x3F,0xF8,0x3F,0xF8,0x3F,0xF8,0x3F,0xF8,/*"F:\NCQ\V1.0\无名创新遥控器\lock.bmp",0*/
};/* (15 X 15 )*/
const unsigned char unlock_ico[]={
0x00,0x78,0x00,0xFC,0x01,0xFE,0x01,0x86,0x01,0x86,0x01,0x86,0x01,0x86,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,/*"F:\NCQ\V1.0\无名创新遥控器\unlock.bmp",0*/
};/* (15 X 15 )*/
const unsigned char power_ico5[]={
0x00,0x00,0x00,0x00,0xFF,0xF8,0xFF,0xF8,0xAA,0xA8,0xAA,0xAE,0xAA,0xAE,0xAA,0xAE,0xAA,0xAE,0xAA,0xAE,0xAA,0xA8,0xFF,0xF8,0xFF,0xF8,0x00,0x00,0x00,0x00
};/* (15 X 15 )*/
const unsigned char power_ico4[]={
0x00,0x00,0x00,0x00,0xFF,0xF8,0xFF,0xF8,0xAA,0x88,0xAA,0x8E,0xAA,0x8E,0xAA,0x8E,0xAA,0x8E,0xAA,0x8E,0xAA,0x88,0xFF,0xF8,0xFF,0xF8,0x00,0x00,0x00,0x00,/*"F:\NCQ\V1.0\无名创新遥控器\power.bmp",0*/
};/* (15 X 15 )*/
const unsigned char power_ico3[]={
0x00,0x00,0x00,0x00,0xFF,0xF8,0xFF,0xF8,0xAA,0x08,0xAA,0x0E,0xAA,0x0E,0xAA,0x0E,0xAA,0x0E,0xAA,0x0E,0xAA,0x08,0xFF,0xF8,0xFF,0xF8,0x00,0x00,0x00,0x00
};/* (15 X 15 )*/
const unsigned char power_ico2[]={
0x00,0x00,0x00,0x00,0xFF,0xF8,0xFF,0xF8,0xA8,0x08,0xA8,0x0E,0xA8,0x0E,0xA8,0x0E,0xA8,0x0E,0xA8,0x0E,0xA8,0x08,0xFF,0xF8,0xFF,0xF8,0x00,0x00,0x00,0x00
};/* (15 X 15 )*/
const unsigned char power_ico1[]={
0x00,0x00,0x00,0x00,0xFF,0xF8,0xFF,0xF8,0xA0,0x08,0xA0,0x0E,0xA0,0x0E,0xA0,0x0E,0xA0,0x0E,0xA0,0x0E,0xA0,0x08,0xFF,0xF8,0xFF,0xF8,0x00,0x00,0x00,0x00
};/* (15 X 15 )*/
const unsigned char power_ico0[]={
0x00,0x00,0x00,0x00,0xFF,0xF8,0xFF,0xF8,0x80,0x08,0x80,0x0E,0x80,0x0E,0x80,0x0E,0x80,0x0E,0x80,0x0E,0x80,0x08,0xFF,0xF8,0xFF,0xF8,0x00,0x00,0x00,0x00
};/* (15 X 15 )*/


void main_window_show(void)
{
	uint16_t base_x=10,bash_y=0;
	int16_t x1=0,y1=0;
	int16_t x2=0,y2=0;
 
  GUI_Circle(32+base_x,32+bash_y,10,1);
  GUI_Circle(91-base_x,32+bash_y,10,1);
	
	GUI_Square(17+base_x,17+bash_y,30,1);
	GUI_Square(76-base_x,17+bash_y,30,1);
	
  x1=15*(RC_Data.rcdata[RC_ROLL_CHANNEL]-1500)/500;
	y1=15*(RC_Data.rcdata[RC_PITCH_CHANNEL]-1500)/500;
  GUI_CircleFill(91+x1-base_x,32+y1+bash_y,2,1);

	x2=15*(RC_Data.rcdata[RC_YAW_CHANNEL]-1500)/500;
	y2=15*(RC_Data.rcdata[RC_THR_CHANNEL]-1500)/500;
	GUI_CircleFill(32+x2+base_x,32-y2+bash_y,2,1);
	//拨动开关
  if(RC_Data.rcdata[RC_SWA_CHANNEL]==1000) GUI_Circle(32,5,5,1); 
	else GUI_CircleFill(32,5,5,1);
	
  if(RC_Data.rcdata[RC_SWB_CHANNEL]==1000) GUI_Circle(52,5,5,1); 
	else GUI_CircleFill(52,5,5,1);

  if(RC_Data.rcdata[RC_SWC_CHANNEL]==1000) GUI_Circle(72,5,5,1); 
	else GUI_CircleFill(72,5,5,1);
	
	if(RC_Data.rcdata[RC_SWD_CHANNEL]==1000) GUI_Circle(92,5,5,1); 
	else GUI_CircleFill(92,5,5,1);
	//电位器
	GUI_Rectangle(0,0,20,10,1);
	x1=20*(RC_Data.rcdata[RC_VRA_CHANNEL]-1000)/1000;
	GUI_RectangleFill(0,0,x1,10,1);

	GUI_Rectangle(107,0,127,10,1);
	x2=20*(RC_Data.rcdata[RC_VRB_CHANNEL]-1000)/1000;
	GUI_RectangleFill(107,0,107+x2,10,1);


	GUI_PutNumber(0,16,RC_Data.rcdata[RC_VRA_CHANNEL],FONT5x7);
	GUI_PutNumber(102,16,RC_Data.rcdata[RC_VRB_CHANNEL],FONT5x7);


  GUI_PutNumber(30,50,RC_Data.rcdata[RC_YAW_CHANNEL],FONT5x7);
	GUI_PutNumber(70,50,RC_Data.rcdata[RC_ROLL_CHANNEL],FONT5x7);
	GUI_PutNumber(0,32,RC_Data.rcdata[RC_THR_CHANNEL],FONT5x7);
	GUI_PutNumber(102,32,RC_Data.rcdata[RC_PITCH_CHANNEL],FONT5x7);

//	GUI_PutString(0,55,"RV:"); GUI_PutNumber(20,55,RC_Data.vbat_mv/1000.0,FONT5x7);
//	GUI_PutString(65,55,"FV:");GUI_PutNumber(85,55,11.2,FONT5x7);
	
//GUI_LoadPic(32,64,gps_ico,30,30);
	
}




uint8_t menu_item_cnt=1;
void menu_ui_show()
{
	static uint8_t x_base=35;
	GUI_Rectangle(0,0,127,63,1);
	
	
	OLED_ShowChinese(1,2,43);  //失控保护
	OLED_ShowChinese(17,2,44);
	OLED_ShowChinese(33,2,45); 
	OLED_ShowChinese(49,2,46); 
	OLED_ShowChinese(65,2,55);
	
	if(RC_Data.lose_ctrl_protect==1) 
	{
		OLED_ShowChinese(82,2,47);
	}		
	else
	{
		OLED_ShowChinese(82,2,49);
	}
	
	if(RC_Data.lose_ctrl_protect==1) 
	{
		OLED_ShowChinese(82,20,56+RC_Data.lose_ctrl_protect_channel-1);
	}		
	else
	{
		OLED_ShowChinese(82,20,56+RC_Data.lose_ctrl_protect_channel-1);
	}
	
	OLED_ShowChinese(1,20,53);  //通道
	OLED_ShowChinese(17,20,54);
	OLED_ShowChinese(33,20,6); 
	OLED_ShowChinese(49,20,7); 
	OLED_ShowChinese(65,20,55);

	
	OLED_ShowChinese(1,38,16);  //通道
	OLED_ShowChinese(17,38,17);
	OLED_ShowChinese(33,38,6); 
	OLED_ShowChinese(49,38,7); 
	OLED_ShowChinese(65,38,55);
	GUI_PutNumber(70,46,RC_Data.lose_ctrl_protect_value,FONT5x7);
	
	
	
	GUI_Circle(80+x_base,8,8,1);
	GUI_Circle(80+x_base,28,8,1);
	GUI_Circle(80+x_base,48,8,1);
	
	
	
	
	
	
	if(_button.state[SWITCH_UP].press==SHORT_PRESS)
	{
	  menu_item_cnt--;
	  if(menu_item_cnt<1) menu_item_cnt=3;
		_button.state[SWITCH_UP].press=NO_PRESS;
	}
	
	if(_button.state[SWITCH_DOWN].press==SHORT_PRESS)
	{
	  menu_item_cnt++;
	  if(menu_item_cnt>3) menu_item_cnt=1;
		_button.state[SWITCH_DOWN].press=NO_PRESS;
	}	
	
	if(menu_item_cnt==1) GUI_CircleFill(80+x_base,8,3,1);
	else if(menu_item_cnt==2) GUI_CircleFill(80+x_base,28,3,1);
	else GUI_CircleFill(80+x_base,48,3,1);

	
	if(menu_item_cnt==1)
	{
		if(_button.state[UP].press==SHORT_PRESS)
		{
      if(RC_Data.lose_ctrl_protect==0) RC_Data.lose_ctrl_protect=1;
      else RC_Data.lose_ctrl_protect=0;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      if(RC_Data.lose_ctrl_protect==0) RC_Data.lose_ctrl_protect=1;
      else RC_Data.lose_ctrl_protect=0;	
			_button.state[DOWN].press=NO_PRESS;
		}
	}	
	
	
	if(menu_item_cnt==2)
	{
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.lose_ctrl_protect_channel--;
			if(RC_Data.lose_ctrl_protect_channel<5)  RC_Data.lose_ctrl_protect_channel=10; 			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.lose_ctrl_protect_channel++;
			if(RC_Data.lose_ctrl_protect_channel>10)  RC_Data.lose_ctrl_protect_channel=5;			
			_button.state[DOWN].press=NO_PRESS;
		}
	}


	if(menu_item_cnt==3)
	{
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.lose_ctrl_protect_value+=10;
			if(RC_Data.lose_ctrl_protect_value>2000)  RC_Data.lose_ctrl_protect_value=2000;			
			_button.state[UP].press=NO_PRESS;  
		}
		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
			RC_Data.lose_ctrl_protect_value-=10;
			if(RC_Data.lose_ctrl_protect_value<1000)  RC_Data.lose_ctrl_protect_value=1000; 			
			_button.state[DOWN].press=NO_PRESS;
		}
	}


	if(_button.state[EXIT].press==LONG_PRESS)//恢复默认参数
	{
		RC_Data.lose_ctrl_protect=1;
		RC_Data.lose_ctrl_protect_channel=7;
		RC_Data.lose_ctrl_protect_value=2000;
		WriteFlashParameter_Three(LOSE_CTRL_PROTECT_ENABLE,
															RC_Data.lose_ctrl_protect,
															RC_Data.lose_ctrl_protect_channel,
															RC_Data.lose_ctrl_protect_value,
															&Table_Parameter);
		_button.state[EXIT].press=NO_PRESS;
	}

	if(_button.state[ENTER].press==LONG_PRESS)//保存当前参数到flash
	{
		WriteFlashParameter_Three(LOSE_CTRL_PROTECT_ENABLE,
															RC_Data.lose_ctrl_protect,
															RC_Data.lose_ctrl_protect_channel,
															RC_Data.lose_ctrl_protect_value,
															&Table_Parameter);
		_button.state[ENTER].press=NO_PRESS;
	}	
}





void core_interface_show(void)
{
	uint8_t y_base=5;
	if(nrf_soft_rssi>10) GUI_LoadPic(0,0,(unsigned char *)signal_ico_okay,20,15);//信号连接界面
	else  GUI_LoadPic(0,0,(unsigned char *)signal_ico_no,20,15);
	
	GUI_PutNumber(25,5,nrf_soft_rssi,FONT5x7);
	GUI_PutChar8_8(45,5,'%');
	
	
	GUI_LoadPic(55,0,(unsigned char *)gps_ico,15,15);
	GUI_PutNumber(75,5,gps_satellite_num,FONT5x7);
	
	
	if(armed_flag) GUI_LoadPic(90,0,(unsigned char *)unlock_ico,15,15);
	else  GUI_LoadPic(90,0,(unsigned char *)lock_ico,15,15);
	
	
	if(RC_Data.vbat_mv>=4200)  			GUI_LoadPic(108,0,(unsigned char *)power_ico5,15,15);
	else if(RC_Data.vbat_mv>=4000)  GUI_LoadPic(108,0,(unsigned char *)power_ico4,15,15);
	else if(RC_Data.vbat_mv>=3800)  GUI_LoadPic(108,0,(unsigned char *)power_ico3,15,15);
	else if(RC_Data.vbat_mv>=3600)  GUI_LoadPic(108,0,(unsigned char *)power_ico2,15,15);
	else if(RC_Data.vbat_mv>=3500)  GUI_LoadPic(108,0,(unsigned char *)power_ico1,15,15);
	else   GUI_LoadPic(108,0,(unsigned char *)power_ico0,15,15);
 
  GUI_PutString(0,20-y_base,"Hm");      GUI_PutNumber(35,20-y_base,alt_pos_fus/100.0f,FONT5x7);               						
	GUI_PutString(0,28-y_base,"HV");      GUI_PutNumber(35,28-y_base,alt_vel_fus/100.0f,FONT5x7);               							
  GUI_PutString(0,36-y_base,"Dm");      GUI_PutNumber(35,36-y_base,0.01f*sqrt(lat_pos_fusion*lat_pos_fusion+
																																			 lng_pos_fusion*lng_pos_fusion),FONT5x7);               							
	GUI_PutString(0,44-y_base,"DV");      GUI_PutNumber(35,44-y_base,0.01f*sqrt(lat_vel_fusion*lat_vel_fusion+
																																			 lng_vel_fusion*lng_vel_fusion),FONT5x7);               						
	GUI_PutString(0,52-y_base,"VB(V)");   GUI_PutNumber(35,52-y_base,RC_Data.vbat_mv/1000.0,FONT5x7);       
	GUI_PutString(0,60-y_base,"RB(V)");   GUI_PutNumber(35,60-y_base,vbat,FONT5x7);          
	
	GUI_PutString(95,22-y_base,"RPYT");
	GUI_Rectangle(80,20-y_base,127,63,1);
	GUI_PutNumber(85,30-y_base,roll,FONT5x7);
	GUI_PutNumber(85,38-y_base,pitch,FONT5x7);
	GUI_PutNumber(85,46-y_base,yaw,FONT5x7);
	GUI_PutNumber(85,54-y_base,imu_temp,FONT5x7);
}


void rc_cal_show(void)
{
	static uint16_t check_number=0;
	int16_t x1,y1=10;
	GUI_Rectangle(0,0+y1,40,6+y1,1);
	x1=40*(RC_Data.rcdata[RC_ROLL_CHANNEL]-RC_Data.cal[RC_ROLL_CHANNEL].min)/(RC_Data.cal[RC_ROLL_CHANNEL].max-RC_Data.cal[RC_ROLL_CHANNEL].min);
	GUI_RectangleFill(0,0+y1,x1,6+y1,1);
	
	GUI_Rectangle(0,15+y1,40,21+y1,1);
	x1=40*(RC_Data.rcdata[RC_PITCH_CHANNEL]-RC_Data.cal[RC_PITCH_CHANNEL].min)/(RC_Data.cal[RC_PITCH_CHANNEL].max-RC_Data.cal[RC_PITCH_CHANNEL].min);
	GUI_RectangleFill(0,15+y1,x1,21+y1,1);

	GUI_Rectangle(0,30+y1,40,36+y1,1);
	x1=40*(RC_Data.rcdata[RC_THR_CHANNEL]-RC_Data.cal[RC_THR_CHANNEL].min)/(RC_Data.cal[RC_THR_CHANNEL].max-RC_Data.cal[RC_THR_CHANNEL].min);
	GUI_RectangleFill(0,30+y1,x1,36+y1,1);

	GUI_Rectangle(0,45+y1,40,51+y1,1);
	x1=40*(RC_Data.rcdata[RC_YAW_CHANNEL]-RC_Data.cal[RC_YAW_CHANNEL].min)/(RC_Data.cal[RC_YAW_CHANNEL].max-RC_Data.cal[RC_YAW_CHANNEL].min);
	GUI_RectangleFill(0,45+y1,x1,51+y1,1);	
	
	GUI_RLine(20,0,63,1);


	GUI_PutString(0,0,"R:");GUI_PutNumber(15,0	,RC_Data.rcdata[RC_ROLL_CHANNEL] ,FONT5x7);
	GUI_PutString(0,16,"P:");GUI_PutNumber(15,16,RC_Data.rcdata[RC_PITCH_CHANNEL],FONT5x7);
	GUI_PutString(0,32,"T:");GUI_PutNumber(15,32,RC_Data.rcdata[RC_THR_CHANNEL]  ,FONT5x7);
	GUI_PutString(0,48,"Y:");GUI_PutNumber(15,48,RC_Data.rcdata[RC_YAW_CHANNEL]  ,FONT5x7);
	
	
	
	GUI_PutString(45,0,"MIN  MAX  OFF");
	GUI_PutNumber(45,10,RC_Data.cal[RC_ROLL_CHANNEL].min,FONT5x7);
	GUI_PutNumber(72,10,RC_Data.cal[RC_ROLL_CHANNEL].max,FONT5x7);
	GUI_PutNumber(102,10,RC_Data.cal[RC_ROLL_CHANNEL].offset,FONT5x7);
	
	
	GUI_PutNumber(45,25,RC_Data.cal[RC_PITCH_CHANNEL].min,FONT5x7);
	GUI_PutNumber(72,25,RC_Data.cal[RC_PITCH_CHANNEL].max,FONT5x7);
	GUI_PutNumber(102,25,RC_Data.cal[RC_PITCH_CHANNEL].offset,FONT5x7);
	
	GUI_PutNumber(45,40,RC_Data.cal[RC_THR_CHANNEL].min,FONT5x7);
	GUI_PutNumber(72,40,RC_Data.cal[RC_THR_CHANNEL].max,FONT5x7);
	GUI_PutNumber(102,40,RC_Data.cal[RC_THR_CHANNEL].offset,FONT5x7);
	
	GUI_PutNumber(45,55,RC_Data.cal[RC_YAW_CHANNEL].min,FONT5x7);
	GUI_PutNumber(72,55,RC_Data.cal[RC_YAW_CHANNEL].max,FONT5x7);
	GUI_PutNumber(102,55,RC_Data.cal[RC_YAW_CHANNEL].offset,FONT5x7);
	
	
	if(_button.state[SWITCH_UP].press==SHORT_PRESS)
	{
	  check_number--;
	  if(check_number<1) check_number=12;
		_button.state[SWITCH_UP].press=NO_PRESS;
	}
	
	if(_button.state[SWITCH_DOWN].press==SHORT_PRESS)
	{
	  check_number++;
	  if(check_number>12) check_number=1;
		_button.state[SWITCH_DOWN].press=NO_PRESS;
	}
	
	if(check_number==1)
	{
		GUI_HLine(48,20,68,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].min++;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].min+=_button.state[UP].in_press_cnt;			
			_button.state[UP].press=NO_PRESS;
		}		
		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].min--; 
			_button.state[DOWN].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].min-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}		
		if(RC_Data.cal[RC_ROLL_CHANNEL].min>RC_MID_LIMIT)	RC_Data.cal[RC_ROLL_CHANNEL].min=RC_MID_LIMIT;	
		if(RC_Data.cal[RC_ROLL_CHANNEL].min<RC_MIN_LIMIT)	RC_Data.cal[RC_ROLL_CHANNEL].min=RC_MIN_LIMIT;	
	}
	else if(check_number==2)
	{
	  GUI_HLine(70,20,90,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].max++;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].max+=_button.state[UP].in_press_cnt;		
			_button.state[UP].press=NO_PRESS;
		}		
		

		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].max--; 	
			_button.state[DOWN].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].max-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}	
		if(RC_Data.cal[RC_ROLL_CHANNEL].max>RC_MAX_LIMIT)	RC_Data.cal[RC_ROLL_CHANNEL].max=RC_MAX_LIMIT;	
		if(RC_Data.cal[RC_ROLL_CHANNEL].max<RC_MID_LIMIT)	RC_Data.cal[RC_ROLL_CHANNEL].max=RC_MID_LIMIT;	
	}
	else if(check_number==3)
	{
	  GUI_HLine(102,20,122,1);
		
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].offset++;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].offset+=_button.state[UP].in_press_cnt;			
			_button.state[UP].press=NO_PRESS;
		}		
		

		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].offset--; 
			_button.state[DOWN].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_ROLL_CHANNEL].offset-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}
		if(RC_Data.cal[RC_ROLL_CHANNEL].offset>RC_OFFSET_LIMIT)			RC_Data.cal[RC_ROLL_CHANNEL].offset=RC_OFFSET_LIMIT;	
		if(RC_Data.cal[RC_ROLL_CHANNEL].offset<-RC_OFFSET_LIMIT)		RC_Data.cal[RC_ROLL_CHANNEL].offset=-RC_OFFSET_LIMIT;		
	}	
	else if(check_number==4)
	{
	  GUI_HLine(48,35,68,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].min++;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].min+=_button.state[UP].in_press_cnt;		
			_button.state[UP].press=NO_PRESS;
		}		
		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].min--; 
			_button.state[DOWN].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].min-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}		
		if(RC_Data.cal[RC_PITCH_CHANNEL].min>RC_MID_LIMIT)	RC_Data.cal[RC_PITCH_CHANNEL].min=RC_MID_LIMIT;	
		if(RC_Data.cal[RC_PITCH_CHANNEL].min<RC_MIN_LIMIT)		RC_Data.cal[RC_PITCH_CHANNEL].min=RC_MIN_LIMIT;
	}
	else if(check_number==5)
	{
	  GUI_HLine(70,35,90,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].max++;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].max+=_button.state[UP].in_press_cnt;	
			_button.state[UP].press=NO_PRESS;
		}		
		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].max--; 
			_button.state[DOWN].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].max-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}
		if(RC_Data.cal[RC_PITCH_CHANNEL].max>RC_MAX_LIMIT)	RC_Data.cal[RC_PITCH_CHANNEL].max=RC_MAX_LIMIT;	
		if(RC_Data.cal[RC_PITCH_CHANNEL].max<RC_MID_LIMIT)	RC_Data.cal[RC_PITCH_CHANNEL].max=RC_MID_LIMIT;
	}	
	else if(check_number==6)
	{
	  GUI_HLine(102,35,122,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].offset++;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].offset+=_button.state[UP].in_press_cnt;			
			_button.state[UP].press=NO_PRESS;
		}		
		

		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].offset--; 
			_button.state[DOWN].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_PITCH_CHANNEL].offset-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}
		if(RC_Data.cal[RC_PITCH_CHANNEL].offset>RC_OFFSET_LIMIT)	RC_Data.cal[RC_PITCH_CHANNEL].offset=RC_OFFSET_LIMIT;	
		if(RC_Data.cal[RC_PITCH_CHANNEL].offset<-RC_OFFSET_LIMIT)		RC_Data.cal[RC_PITCH_CHANNEL].offset=-RC_OFFSET_LIMIT;		
	}
	else if(check_number==7)
	{
	  GUI_HLine(48,50,68,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].min++;	
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].min+=_button.state[UP].in_press_cnt;	
			_button.state[UP].press=NO_PRESS;
		}		
		

		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].min--; 	
			_button.state[DOWN].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].min-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}		
		
		if(RC_Data.cal[RC_THR_CHANNEL].min>RC_MID_LIMIT)	RC_Data.cal[RC_THR_CHANNEL].min=RC_MID_LIMIT;	
		if(RC_Data.cal[RC_THR_CHANNEL].min<RC_MIN_LIMIT)		RC_Data.cal[RC_THR_CHANNEL].min=RC_MIN_LIMIT;	
	}		
	else if(check_number==8)
	{
	  GUI_HLine(70,50,90,9);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].max++;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].max+=_button.state[UP].in_press_cnt;		
			_button.state[UP].press=NO_PRESS;
		}		
		

		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].max--; 
			_button.state[DOWN].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].max-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}
		if(RC_Data.cal[RC_THR_CHANNEL].max>RC_MAX_LIMIT)	RC_Data.cal[RC_THR_CHANNEL].max=RC_MAX_LIMIT;	
		if(RC_Data.cal[RC_THR_CHANNEL].max<RC_MID_LIMIT)		RC_Data.cal[RC_THR_CHANNEL].max=RC_MID_LIMIT;	
	}		
	else if(check_number==9)
	{
	  GUI_HLine(102,50,122,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].offset++;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].offset+=_button.state[UP].in_press_cnt;	
			_button.state[UP].press=NO_PRESS;
		}		
		

		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].offset--; 
			_button.state[DOWN].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_THR_CHANNEL].offset-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}	
		if(RC_Data.cal[RC_THR_CHANNEL].offset>RC_OFFSET_LIMIT)	RC_Data.cal[RC_THR_CHANNEL].offset=RC_OFFSET_LIMIT;	
		if(RC_Data.cal[RC_THR_CHANNEL].offset<-RC_OFFSET_LIMIT)		RC_Data.cal[RC_THR_CHANNEL].offset=-RC_OFFSET_LIMIT;	
	}		
	else if(check_number==10)
	{
	  GUI_HLine(48,63,68,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].min++;			
			_button.state[UP].press=NO_PRESS;
		}		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].min+=_button.state[UP].in_press_cnt;	
			_button.state[UP].press=NO_PRESS;
		}		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].min--; 
			_button.state[DOWN].press=NO_PRESS;
		}	
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].min-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}		
		if(RC_Data.cal[RC_YAW_CHANNEL].min>RC_MID_LIMIT)	RC_Data.cal[RC_YAW_CHANNEL].min=RC_MID_LIMIT;	
		if(RC_Data.cal[RC_YAW_CHANNEL].min<RC_MIN_LIMIT)	RC_Data.cal[RC_YAW_CHANNEL].min=RC_MIN_LIMIT;	
	}
	else if(check_number==11)
	{
	  GUI_HLine(70,63,90,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].max++;			
			_button.state[UP].press=NO_PRESS;
		}		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].max+=_button.state[UP].in_press_cnt;	
			_button.state[UP].press=NO_PRESS;
		}		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].max--; 
			_button.state[DOWN].press=NO_PRESS;
		}	
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].max-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}		
		if(RC_Data.cal[RC_YAW_CHANNEL].max>RC_MAX_LIMIT)	RC_Data.cal[RC_YAW_CHANNEL].max=RC_MAX_LIMIT;	
		if(RC_Data.cal[RC_YAW_CHANNEL].max<RC_MID_LIMIT)	RC_Data.cal[RC_YAW_CHANNEL].max=RC_MID_LIMIT;
	}
  else
	{
    GUI_HLine(102,63,122,1);
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].offset++;			
			_button.state[UP].press=NO_PRESS;
		}		
		if(_button.state[UP].press==IN_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].offset+=_button.state[UP].in_press_cnt;	
			_button.state[UP].press=NO_PRESS;
		}		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].offset--; 
			_button.state[DOWN].press=NO_PRESS;
		}	
		if(_button.state[DOWN].press==IN_PRESS)
		{
      RC_Data.cal[RC_YAW_CHANNEL].offset-=_button.state[DOWN].in_press_cnt; 
			_button.state[DOWN].press=NO_PRESS;
		}		
		if(RC_Data.cal[RC_YAW_CHANNEL].offset>RC_OFFSET_LIMIT)	RC_Data.cal[RC_YAW_CHANNEL].offset=RC_OFFSET_LIMIT;	
		if(RC_Data.cal[RC_YAW_CHANNEL].offset<-RC_OFFSET_LIMIT)		RC_Data.cal[RC_YAW_CHANNEL].offset=-RC_OFFSET_LIMIT;
	}	
	
	if(_button.state[EXIT].press==LONG_PRESS)//恢复默认参数
	{
		for(uint16_t i=0;i<RC_CHL_MAX;i++)
		{	
			RC_Data.cal[i].max=2000;
			RC_Data.cal[i].min=1000;
			RC_Data.cal[i].offset=0;
		}
		WriteFlashParameter_Three(RC_CAL_ROLL_MIN,
															RC_Data.cal[RC_ROLL_CHANNEL].min,
															RC_Data.cal[RC_ROLL_CHANNEL].max,
															RC_Data.cal[RC_ROLL_CHANNEL].offset,
															&Table_Parameter);

		WriteFlashParameter_Three(RC_CAL_PITCH_MIN,
															RC_Data.cal[RC_PITCH_CHANNEL].min,
															RC_Data.cal[RC_PITCH_CHANNEL].max,
															RC_Data.cal[RC_PITCH_CHANNEL].offset,
															&Table_Parameter);

		WriteFlashParameter_Three(RC_CAL_THR_MIN,
															RC_Data.cal[RC_THR_CHANNEL].min,
															RC_Data.cal[RC_THR_CHANNEL].max,
															RC_Data.cal[RC_THR_CHANNEL].offset,
															&Table_Parameter);

		WriteFlashParameter_Three(RC_CAL_YAW_MIN,
															RC_Data.cal[RC_YAW_CHANNEL].min,
															RC_Data.cal[RC_YAW_CHANNEL].max,
															RC_Data.cal[RC_YAW_CHANNEL].offset,
															&Table_Parameter);
		_button.state[EXIT].press=NO_PRESS;
	}

	if(_button.state[ENTER].press==LONG_PRESS)//保存当前参数到flash
	{
		WriteFlashParameter_Three(RC_CAL_ROLL_MIN,
															RC_Data.cal[RC_ROLL_CHANNEL].min,
															RC_Data.cal[RC_ROLL_CHANNEL].max,
															RC_Data.cal[RC_ROLL_CHANNEL].offset,
															&Table_Parameter);
		
		WriteFlashParameter_Three(RC_CAL_PITCH_MIN,
															RC_Data.cal[RC_PITCH_CHANNEL].min,
															RC_Data.cal[RC_PITCH_CHANNEL].max,
															RC_Data.cal[RC_PITCH_CHANNEL].offset,
															&Table_Parameter);

		WriteFlashParameter_Three(RC_CAL_THR_MIN,
															RC_Data.cal[RC_THR_CHANNEL].min,
															RC_Data.cal[RC_THR_CHANNEL].max,
															RC_Data.cal[RC_THR_CHANNEL].offset,
															&Table_Parameter);

		WriteFlashParameter_Three(RC_CAL_YAW_MIN,
															RC_Data.cal[RC_YAW_CHANNEL].min,
															RC_Data.cal[RC_YAW_CHANNEL].max,
															RC_Data.cal[RC_YAW_CHANNEL].offset,
															&Table_Parameter);
		_button.state[ENTER].press=NO_PRESS;
	}
}




int8_t chl_map_number=0;
void rc_chl_choose_show(void)
{
	GUI_PutString(0,0, "Channel-5 :");
	GUI_PutString(0,10,"Channel-6 :");
	GUI_PutString(0,20,"Channel-7 :");
	GUI_PutString(0,30,"Channel-8 :");
	GUI_PutString(0,40,"Channel-9 :");
	GUI_PutString(0,50,"Channel-10:");
  for(uint16_t i=0;i<CH_MAP_NUM;i++)	
	{
		if(RC_Data.func_ch_remap[i]==SWA) GUI_PutString(80,10*i, "SWA");
		else 	if(RC_Data.func_ch_remap[i]==SWB) GUI_PutString(80,10*i, "SWB");
		else 	if(RC_Data.func_ch_remap[i]==SWC) GUI_PutString(80,10*i, "SWC");
		else 	if(RC_Data.func_ch_remap[i]==SWD) GUI_PutString(80,10*i, "SWD");
		else 	if(RC_Data.func_ch_remap[i]==VRA) GUI_PutString(80,10*i, "VRA");
		else 	if(RC_Data.func_ch_remap[i]==VRB) GUI_PutString(80,10*i, "VRB");
		
		if(chl_map_number==i) 
		GUI_CircleFill(110,10*i+3,3,1);	
		//GUI_PutString(100,10*i, "VRB");
	}
	
	
	if(_button.state[SWITCH_UP].press==SHORT_PRESS)
	{
		chl_map_number--;
		if(chl_map_number<0) chl_map_number=5;
		_button.state[SWITCH_UP].press=NO_PRESS;
	}

	if(_button.state[SWITCH_DOWN].press==SHORT_PRESS)
	{
		chl_map_number++;
		if(chl_map_number>5) chl_map_number=0;
		_button.state[SWITCH_DOWN].press=NO_PRESS;
	}
	
	for(uint16_t i=0;i<CH_MAP_NUM;i++)
	{
		if(chl_map_number==i)
		{
			if(_button.state[UP].press==SHORT_PRESS)
			{
				RC_Data.func_ch_remap[i]--;
				if(RC_Data.func_ch_remap[i]<0) RC_Data.func_ch_remap[i]=5;
				_button.state[UP].press=NO_PRESS;
			}

			if(_button.state[DOWN].press==SHORT_PRESS)
			{
				RC_Data.func_ch_remap[i]++;
				if(RC_Data.func_ch_remap[i]>5) RC_Data.func_ch_remap[i]=0;
				_button.state[DOWN].press=NO_PRESS;
			}
		}
	}
	
	if(_button.state[EXIT].press==LONG_PRESS)//恢复默认参数
	{
		RC_Data.func_ch_remap[0]=SWA;
		RC_Data.func_ch_remap[1]=SWB;
		RC_Data.func_ch_remap[2]=SWC;
		RC_Data.func_ch_remap[3]=SWD;
		RC_Data.func_ch_remap[4]=VRA;
		RC_Data.func_ch_remap[5]=VRB;
		WriteFlashParameter_Three(RC_MAP_CH5,
															RC_Data.func_ch_remap[0],
															RC_Data.func_ch_remap[1],
															RC_Data.func_ch_remap[2],
															&Table_Parameter);

		WriteFlashParameter_Three(RC_MAP_CH8,
															RC_Data.func_ch_remap[3],
															RC_Data.func_ch_remap[4],
															RC_Data.func_ch_remap[5],
															&Table_Parameter);
		_button.state[EXIT].press=NO_PRESS;
	}

	if(_button.state[ENTER].press==LONG_PRESS)//保存当前参数到flash
	{
		WriteFlashParameter_Three(RC_MAP_CH5,
															RC_Data.func_ch_remap[0],
															RC_Data.func_ch_remap[1],
															RC_Data.func_ch_remap[2],
															&Table_Parameter);

		WriteFlashParameter_Three(RC_MAP_CH8,
															RC_Data.func_ch_remap[3],
															RC_Data.func_ch_remap[4],
															RC_Data.func_ch_remap[5],
															&Table_Parameter);
		_button.state[ENTER].press=NO_PRESS;
	}
}



void fc_gps_data_show()
{
	GUI_PutString(35,0,"fc_gps_data");
	int8_t y_offset=-10;
  GUI_PutString(0,20+y_offset,"gps_lng:");      GUI_PutNumber(60,20+y_offset,gps_lng,FONT5x7);               						
	GUI_PutString(0,28+y_offset,"gps_lat:");      GUI_PutNumber(60,28+y_offset,gps_lat,FONT5x7);               							
  GUI_PutString(0,36+y_offset,"gps_alt:");   	  GUI_PutNumber(60,36+y_offset,gps_alt,FONT5x7);               							
	GUI_PutString(0,44+y_offset,"gps_pdop:");     GUI_PutNumber(60,44+y_offset,gps_pdop,FONT5x7);               						
	GUI_PutString(0,52+y_offset,"gps_state:");   	GUI_PutNumber(60,52+y_offset,gps_state,FONT5x7);       
	GUI_PutString(0,60+y_offset,"gps_sate:");   	GUI_PutNumber(60,60+y_offset,gps_satellite_num,FONT5x7); 
}


void user_data_show()
{
	GUI_PutString(35,0,"user_data");
	int8_t y_offset=-10;
  GUI_PutString(0,20+y_offset,"data1:");    GUI_PutNumber(60,20+y_offset,userdata[0],FONT5x7);               						
	GUI_PutString(0,28+y_offset,"data2:");    GUI_PutNumber(60,28+y_offset,userdata[1],FONT5x7);               							
  GUI_PutString(0,36+y_offset,"data3:");    GUI_PutNumber(60,36+y_offset,userdata[2],FONT5x7);               							
	GUI_PutString(0,44+y_offset,"data4:");    GUI_PutNumber(60,44+y_offset,userdata[3],FONT5x7);               						
	GUI_PutString(0,52+y_offset,"data5:");   	GUI_PutNumber(60,52+y_offset,userdata[4],FONT5x7);       
	GUI_PutString(0,60+y_offset,"data6:");   	GUI_PutNumber(60,60+y_offset,userdata[5],FONT5x7); 
}

void imu_data_show()
{
	GUI_PutString(35,0,"imu_data");
	int8_t y_offset=-10;
  GUI_PutString(0,20+y_offset,"ax      ay      az:");    
	GUI_PutNumber(0,28+y_offset,ax,FONT5x7);   GUI_PutNumber(50,28+y_offset,ay,FONT5x7);  GUI_PutNumber(90,28+y_offset,az,FONT5x7);

  GUI_PutString(0,36+y_offset,"gx      gy      gz:");    
	GUI_PutNumber(0,44+y_offset,gx,FONT5x7);   GUI_PutNumber(50,44+y_offset,gy,FONT5x7);  GUI_PutNumber(90,44+y_offset,gz,FONT5x7);

  GUI_PutString(0,52+y_offset,"mx      my      mz:");    
	GUI_PutNumber(0,60+y_offset,mx,FONT5x7);   GUI_PutNumber(50,60+y_offset,my,FONT5x7);  GUI_PutNumber(90,60+y_offset,mz,FONT5x7);
	

}



float Draw_Wave_Buf[2][128];
void draw_ins_wave(void)
{
	uint16_t temp1=0,temp2=0;	
	for(uint16_t i=127;i>0;i--)
	{
		Draw_Wave_Buf[0][i]=Draw_Wave_Buf[0][i-1];
		Draw_Wave_Buf[1][i]=Draw_Wave_Buf[1][i-1];
	}	
	Draw_Wave_Buf[0][0]=100*alt_vel_fus;
	Draw_Wave_Buf[1][0]=100*alt_accel_fus;	
		
	for(uint16_t i=0;i<128;i++)
	{
		temp1=(uint16_t)(16-16*constrain_float((Draw_Wave_Buf[0][i]/400),-1,1));
		temp2=(uint16_t)(47+16*constrain_float((Draw_Wave_Buf[1][i]/4000),-1,1));		
	  GUI_Point(i, temp1, 1);
		GUI_Point(i, temp2, 1);
	}	
}


void draw_gps_wave(void)
{
	uint16_t x1=0,y1=0,x2=0,y2=0;
	float Map_Scale=0;
	GUI_Line(31,31,95,31,1);
	GUI_Line(63,0,63,63,1);
	GUI_Circle(63,31,31,1);
	GUI_PutString(0,0,"gps_map");
	
	GUI_PutString(66,0,"N");
	GUI_PutString(100,31,"E");
	
	float Distance_From_Home=sqrt(lng_pos_fusion*lng_pos_fusion+lat_pos_fusion*lat_pos_fusion);
	GUI_PutString(0,40,"dis:");    
	GUI_PutNumber(0,50,Distance_From_Home,FONT5x7);
	
	if(Distance_From_Home>=1000)   		Map_Scale=10000;//超过10m，量程设置为100m
  else if(Distance_From_Home>=500)   Map_Scale=1000;//超过5m，量程设置为10m
  else 	Map_Scale=500;//默认量程设置为5m
	
	x1=63+32*constrain_float(lng_pos_fusion/Map_Scale,-1.0f,1.0f);
	y1=31+32*constrain_float(lat_pos_fusion/Map_Scale,-1.0f,1.0f);

	x2=63+32*constrain_float(lng_pos_obs/Map_Scale,-1.0f,1.0f);
	y2=31+32*constrain_float(lat_pos_obs/Map_Scale,-1.0f,1.0f);	
	
	GUI_CircleFill(x1,y1,3,1);
	GUI_Circle(x2,y2,5,1);
}





uint8_t rc_gps_okay=0;
void rc_gps_data_show()
{
	float lat,lng;
	if((gps_pvt.fixtype==0x02||gps_pvt.fixtype==0x03)
		&&gps_pvt.numsv>=8
		&&gps_pvt.hacc*0.001f<=3.0f)
	{
	  rc_gps_okay=1;
	}
  else
	{
	  rc_gps_okay=0;
	}	
		
	lng=gps_pvt.lon*0.0000001f;
	lat=gps_pvt.lat*0.0000001f;
	GUI_PutString(0,0,"rc_gps");
	if(rc_gps_okay==1)
	{
	  GUI_PutString(40,0,"ok");
	}
	else GUI_PutString(40,0,"no");
	
	GUI_PutNumber(60,0,gps_pvt.year,FONT5x7); 
	GUI_PutNumber(90,0,gps_pvt.month,FONT5x7);
	GUI_PutNumber(105,0,gps_pvt.day,FONT5x7);
	
	
	
	
	int8_t y_offset=-10;
  GUI_PutString(0,20+y_offset,"lng:");      GUI_PutNumber(30,20+y_offset,(int32_t)(lng),FONT5x7); 
																						GUI_PutNumber(55,20+y_offset,(int32_t)((gps_pvt.lon-10000000*(int32_t)(lng))),FONT5x7);              						
	GUI_PutString(0,28+y_offset,"lat:");      GUI_PutNumber(30,28+y_offset,(int32_t)(lat),FONT5x7);
																						GUI_PutNumber(55,28+y_offset,(int32_t)((gps_pvt.lat-10000000*(int32_t)(lat))),FONT5x7);  
	
  GUI_PutString(0,36+y_offset,"alt:");   	  GUI_PutNumber(30,36+y_offset,gps_pvt.height*0.001f,FONT5x7);               							
	GUI_PutString(0,44+y_offset,"pdop:");     GUI_PutNumber(40,44+y_offset,gps_pvt.pdop*0.01f,FONT5x7);  
                                            GUI_PutNumber(80,44+y_offset,gps_pvt.hacc*0.001f,FONT5x7);
	
	GUI_PutString(0,52+y_offset,"state:");   	GUI_PutNumber(40,52+y_offset,gps_pvt.fixtype,FONT5x7);
  if(gps_pvt.fixtype==0x00)
	{
	  GUI_PutString(80,52+y_offset,"nofix");
	}
  else if(gps_pvt.fixtype==0x01)
	{
	  GUI_PutString(80,52+y_offset,"dead");
	}
	else if(gps_pvt.fixtype==0x02)
	{
	  GUI_PutString(80,52+y_offset,"2dfix");
	}
	else if(gps_pvt.fixtype==0x03)
	{
	  GUI_PutString(80,52+y_offset,"3dfix");
	}
	else if(gps_pvt.fixtype==0x04)
	{
	  GUI_PutString(80,52+y_offset,"gnssd");
	}
	else if(gps_pvt.fixtype==0x05)
	{
	  GUI_PutString(80,52+y_offset,"timeo");
	}
	else
	{
	  GUI_PutString(80,52+y_offset,"nogps");
	}
	
	
	GUI_PutString(0,60+y_offset,"sate:");   	GUI_PutNumber(40,60+y_offset,gps_pvt.numsv,FONT5x7);
	GUI_PutNumber(70,60+y_offset,gps_pvt.hour+8,FONT5x7); 
	GUI_PutNumber(85,60+y_offset,gps_pvt.min,FONT5x7);
	GUI_PutNumber(100,60+y_offset,gps_pvt.sec,FONT5x7);	
}


	
void vbat_protect_show()
{
	static uint8_t item_cnt=0;
	static uint8_t x_base=35;
	GUI_Rectangle(0,0,127,63,1);
	
	OLED_ShowChinese(1,2,76);
	OLED_ShowChinese(17,2,68); 
	OLED_ShowChinese(33,2,69);
	OLED_ShowChinese(49,2,66); 
	OLED_ShowChinese(65,2,67); 

	
	OLED_ShowChinese(1,20,70);  
	OLED_ShowChinese(17,20,71);
	OLED_ShowChinese(33,20,72); 
	OLED_ShowChinese(49,20,55);

	
	OLED_ShowChinese(1,38,73);  
	OLED_ShowChinese(17,38,74);
	OLED_ShowChinese(33,38,75); 
	OLED_ShowChinese(49,38,55);
	
	

	if(RC_Data.flight_safe_vbat_enable==1) 
	{
		OLED_ShowChinese(85,2,47);
	}		
	else
	{
		OLED_ShowChinese(85,2,49);
	}
	
	
	GUI_PutNumber(60,28,((int32_t)(RC_Data.flight_safe_vbat_v*1000)),FONT5x7);
	GUI_PutNumber(60,46,((int32_t)(RC_Data.safe_vbat_v*1000)),FONT5x7);
	
	
	GUI_Circle(80+x_base,8,8,1);
	GUI_Circle(80+x_base,28,8,1);
	GUI_Circle(80+x_base,48,8,1);
	
	
	if(_button.state[SWITCH_UP].press==SHORT_PRESS)
	{
	  item_cnt--;
	  if(item_cnt<1) item_cnt=3;
		_button.state[SWITCH_UP].press=NO_PRESS;
	}
	
	if(_button.state[SWITCH_DOWN].press==SHORT_PRESS)
	{
	  item_cnt++;
	  if(item_cnt>3) item_cnt=1;
		_button.state[SWITCH_DOWN].press=NO_PRESS;
	}	
	if(item_cnt==1)      GUI_CircleFill(80+x_base,8,3,1);
	else if(item_cnt==2) GUI_CircleFill(80+x_base,28,3,1);
	else if(item_cnt==3) GUI_CircleFill(80+x_base,48,3,1);


	if(item_cnt==1)
	{
		if(_button.state[UP].press==SHORT_PRESS)
		{
       if(RC_Data.flight_safe_vbat_enable==0) RC_Data.flight_safe_vbat_enable=1;
			 else RC_Data.flight_safe_vbat_enable=0;			
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
       if(RC_Data.flight_safe_vbat_enable==0) RC_Data.flight_safe_vbat_enable=1;
			 else RC_Data.flight_safe_vbat_enable=0;	
			_button.state[DOWN].press=NO_PRESS;
		}
	}

	
	if(item_cnt==2)
	{
		if(_button.state[UP].press==SHORT_PRESS)
		{
       RC_Data.flight_safe_vbat_v+=0.1f;		
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.flight_safe_vbat_v-=0.1f;
      if(RC_Data.flight_safe_vbat_v<0)	RC_Data.flight_safe_vbat_v=0;		
			_button.state[DOWN].press=NO_PRESS;
		}
	}	
	
	
	if(item_cnt==3)
	{
		if(_button.state[UP].press==SHORT_PRESS)
		{
      RC_Data.safe_vbat_v+=0.1f;		
			_button.state[UP].press=NO_PRESS;
		}
		
		if(_button.state[DOWN].press==SHORT_PRESS)
		{
      RC_Data.safe_vbat_v-=0.1f;
      if(RC_Data.safe_vbat_v<0)	RC_Data.safe_vbat_v=0;				
			_button.state[DOWN].press=NO_PRESS;
		}
	}



	if(_button.state[EXIT].press==LONG_PRESS)//恢复默认参数
	{
		RC_Data.flight_safe_vbat_enable=0;	
	  RC_Data.safe_vbat_v=3.70f;
	  RC_Data.flight_safe_vbat_v=10.5f;		
		WriteFlashParameter_Three(RC_SAFE_VOLTAGE,
															RC_Data.safe_vbat_v,
															RC_Data.flight_safe_vbat_v,
															RC_Data.flight_safe_vbat_enable,
															&Table_Parameter);
		_button.state[EXIT].press=NO_PRESS;
	}

	if(_button.state[ENTER].press==LONG_PRESS)//保存当前参数到flash
	{
		WriteFlashParameter_Three(RC_SAFE_VOLTAGE,
															RC_Data.safe_vbat_v,
															RC_Data.flight_safe_vbat_v,
															RC_Data.flight_safe_vbat_enable,
															&Table_Parameter);
		_button.state[ENTER].press=NO_PRESS;
	}	
}



void channel_setup_show()
{
	GUI_Rectangle(0,0,127,63,1);
	OLED_ShowChinese(26 ,2,53);
	OLED_ShowChinese(42,2,78); 
	OLED_ShowChinese(58,2,77);
	OLED_ShowChinese(74,2,54); 
  
	GUI_PutString(15,25,"2.4G+1000M*CHL");
  GUI_PutString(15,38,"CHL:"); 	
	GUI_PutNumber(80,38,rc_pair.channel,FONT5x7);
	
	GUI_PutString(15,50,"FRQ:");
  GUI_PutNumber(50,50,0.001f*(2400+rc_pair.channel),FONT5x7);
	GUI_PutString(90,50,"GHz");
	
	
	if(_button.state[UP].press==SHORT_PRESS)
	{
		rc_pair.channel+=1;	
    if(rc_pair.channel>125)	rc_pair.channel=0; 		
		_button.state[UP].press=NO_PRESS;
	}

	if(_button.state[DOWN].press==SHORT_PRESS)
	{
		rc_pair.channel-=1;
		if(rc_pair.channel<0)	rc_pair.channel=125;				
		_button.state[DOWN].press=NO_PRESS;
	}
	
	
	if(_button.state[EXIT].press==LONG_PRESS)//恢复默认参数
	{
		rc_pair.channel=rc_pair.addr_chl[5];
		WriteFlashParameter(RC_PAIR_CHL,
												rc_pair.channel,
												&Table_Parameter);
		_button.state[EXIT].press=NO_PRESS;
	}

	if(_button.state[ENTER].press==LONG_PRESS)//保存当前参数到flash
	{
		WriteFlashParameter(RC_PAIR_CHL,
												rc_pair.channel,
												&Table_Parameter);
		_button.state[ENTER].press=NO_PRESS;
	}	
		
}


void address_setup_show()
{
	static uint8_t _item_cnt=1;
	GUI_Rectangle(0,0,127,63,1);
	OLED_ShowChinese(26 ,2,53);
	OLED_ShowChinese(42,2,78); 
	OLED_ShowChinese(58,2,79);
	OLED_ShowChinese(74,2,80); 
  
	GUI_PutString(5,20," A1  A2  A3  A4  A5");
	
	GUI_PutNumber(10,28  ,rc_pair.tx_addr[0],FONT5x7);
	GUI_PutNumber(35,28 ,rc_pair.tx_addr[1],FONT5x7);
	GUI_PutNumber(60,28 ,rc_pair.tx_addr[2],FONT5x7);
	GUI_PutNumber(85,28 ,rc_pair.tx_addr[3],FONT5x7);
	GUI_PutNumber(105,28,rc_pair.tx_addr[4],FONT5x7);
	
	
	
	if(_button.state[SWITCH_UP].press==SHORT_PRESS)
	{
		_item_cnt--;
		if(_item_cnt<1) _item_cnt=5;
		_button.state[SWITCH_UP].press=NO_PRESS;
	}

	if(_button.state[SWITCH_DOWN].press==SHORT_PRESS)
	{
		_item_cnt++;
		if(_item_cnt>5) _item_cnt=1;
		_button.state[SWITCH_DOWN].press=NO_PRESS;
	}	

	if(_item_cnt==1)      { GUI_Line(10,38,28,38,1);}
	else if(_item_cnt==2) { GUI_Line(35,38,53,38,1);}
	else if(_item_cnt==3) { GUI_Line(60,38,78,38,1);}
	else if(_item_cnt==4) { GUI_Line(85,38,103,38,1);}
	else if(_item_cnt==5) { GUI_Line(105,38,127,38,1);}
	
	
	
	if(_button.state[UP].press==SHORT_PRESS)
	{
		rc_pair.tx_addr[_item_cnt-1]+=1;
		_button.state[UP].press=NO_PRESS;
	}

	if(_button.state[DOWN].press==SHORT_PRESS)
	{
		rc_pair.channel-=1;
		rc_pair.tx_addr[_item_cnt-1]-=1;			
		_button.state[DOWN].press=NO_PRESS;
	}
	
	
	
	
	
	
	if(_button.state[EXIT].press==LONG_PRESS)//恢复默认参数
	{	
		rc_pair.tx_addr[0]=rc_pair.addr_chl[0];
		rc_pair.tx_addr[1]=rc_pair.addr_chl[1];
		rc_pair.tx_addr[2]=rc_pair.addr_chl[2];
		rc_pair.tx_addr[3]=rc_pair.addr_chl[3];
		rc_pair.tx_addr[4]=rc_pair.addr_chl[4];		
		WriteFlashParameter_Three(RC_TX_ADDR0,
															rc_pair.tx_addr[0],
															rc_pair.tx_addr[1],
															rc_pair.tx_addr[2],
															&Table_Parameter);
		WriteFlashParameter_Two(RC_TX_ADDR3,
														rc_pair.tx_addr[3],
														rc_pair.tx_addr[4],
														&Table_Parameter);
		_button.state[EXIT].press=NO_PRESS;
	}

	if(_button.state[ENTER].press==LONG_PRESS)//保存当前参数到flash
	{
			WriteFlashParameter_Three(RC_TX_ADDR0,
																rc_pair.tx_addr[0],
																rc_pair.tx_addr[1],
																rc_pair.tx_addr[2],
																&Table_Parameter);
			WriteFlashParameter_Two(RC_TX_ADDR3,
															rc_pair.tx_addr[3],
															rc_pair.tx_addr[4],
															&Table_Parameter);
		_button.state[ENTER].press=NO_PRESS;
	}	
		
}




#define rc_max_page 13

int16_t page_number=2;
void openrc_ui_show(void)
{
	if(_button.state[EXIT].press==SHORT_PRESS)
	{
	  page_number--;
	  if(page_number<0) page_number=rc_max_page;
		_button.state[EXIT].press=NO_PRESS;
	}

	if(_button.state[ENTER].press==SHORT_PRESS)
	{
	  page_number++;
	  if(page_number>rc_max_page) page_number=0;
		_button.state[ENTER].press=NO_PRESS;
	}
  
	switch(page_number)
	{
	  case 0:main_window_show();break;
		case 1:menu_ui_show();break;
		case 2:core_interface_show();break;
		case 3:rc_cal_show();break;
		case 4:rc_chl_choose_show();break;
		case 5:fc_gps_data_show();break;
		case 6:user_data_show();break;
		case 7:imu_data_show();break;
		case 8:draw_ins_wave();break;
		case 9:draw_gps_wave();break;
		case 10:rc_gps_data_show();break;
		case 11:vbat_protect_show();break;
		case 12:channel_setup_show();break;
		case 13:address_setup_show();break;
	  default:break;
	}
	GUI_Exec();
	GUI_ClearSCR();	
}



