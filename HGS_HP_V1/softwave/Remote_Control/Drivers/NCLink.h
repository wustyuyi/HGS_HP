#ifndef __NCLINK_H__
#define __NCLINK_H__

#define BYTE0(dwTemp)  (*((char *)(&dwTemp)))
#define BYTE1(dwTemp)  (*((char *)(&dwTemp)+1))
#define BYTE2(dwTemp)  (*((char *)(&dwTemp)+2))
#define BYTE3(dwTemp)  (*((char *)(&dwTemp)+3))
	
#define NCLINK_STATUS         0x01
#define NCLINK_SENSER         0x02
#define NCLINK_RCDATA         0x03
#define NCLINK_GPS 		        0x04
#define NCLINK_OBS_NE         0x05
#define NCLINK_OBS_UOP        0x06
#define NCLINK_FUS_U          0x07
#define NCLINK_FUS_NE         0x08
#define NCLINK_USER           0x09
#define NCLINK_SEND_CAL_RAW   0x11
#define NCLINK_SEND_CAL_PARA  0x12



#define NCLINK_SEND_PID1_3    0x0A
#define NCLINK_SEND_PID4_6    0x0B
#define NCLINK_SEND_PID7_9    0x0C
#define NCLINK_SEND_PID10_12  0x0D
#define NCLINK_SEND_PID13_15  0x0E
#define NCLINK_SEND_PID16_18  0x0F
#define NCLINK_SEND_PARA      0x10
#define NCLINK_SEND_RC        0x11
#define NCLINK_SEND_DIS       0x12
#define NCLINK_SEND_CAL       0x13
#define NCLINK_SEND_CAL_READ  0x14

#define NCLINK_SEND_CHECK     0xF0



extern uint8_t NCLink_Head[2];
extern uint8_t NCLink_End[2];
extern uint8_t NCLink_Send_Ask_Flag[10],NCLink_Send_Check_Flag[20];
extern uint8_t unlock_flag,takeoff_flag;
extern uint8_t rc_update_flag;

extern uint8_t cal_flag,cal_step,cal_cmd,shutdown_now_cal_flag;

void Serial_Data_Send(uint8_t *buf, uint32_t cnt);
void Float2Byte(float *FloatValue, unsigned char *Byte, unsigned char Subscript);
void Byte2Float(unsigned char *Byte, unsigned char Subscript, float *FloatValue);


													
													
void NCLink_GS_Send_RCData(uint16_t ch0,uint16_t ch1,uint16_t ch2,uint16_t ch3,
	                         uint16_t ch4,uint16_t ch5,uint16_t ch6,uint16_t ch7,
													 uint16_t ch8,uint16_t ch9,uint8_t unlock_flag,uint8_t takeoff_flag);//地面站指令发送RC数据													
													
													
													


void NCLink_Data_Prase_Prepare(uint8_t data);
void NCLink_Data_Prase_Process(uint8_t *data_buf,uint8_t num);


//第一帧数据，功能字0x01  数据长度12
extern float pitch,roll,yaw;//姿态角
extern float pitch_gyro,roll_gyro,yaw_gyro;//姿态角速度
extern float vbat;
extern float imu_temp;
extern uint8_t fly_mode;//飞行模式
extern uint8_t armed_flag;//解锁标志

//第二帧数据，功能字0x02  数据长度18
extern int16_t ax,ay,az;
extern int16_t gx,gy,gz;
extern int16_t mx,my,mz;


//第三帧数据，功能字0x03  数据长度16
extern int16_t nrc[8];


//第四帧数据，功能字0x04  数据长度14
extern double gps_lng,gps_lat,gps_alt;
extern int16_t gps_pdop;
extern uint8_t gps_state;
extern uint8_t gps_satellite_num;

//第五帧数据，功能字0x05  数据长度8
extern float lat_vel_obs,lng_vel_obs;
extern float lat_pos_obs,lng_pos_obs;

//第六帧数据，功能字0x06  数据长度8
extern float alt_obs_baro,alt_obs_ult;
extern float opt_vel_p,opt_vel_r;


//第七帧数据，功能字0x06  数据长度8
extern float alt_pos_fus;//融合高度
extern float alt_vel_fus;//融合高度
extern float alt_accel_fus;//融合加速度

//第八帧数据，功能字0x08  数据长度24
extern float lat_pos_fusion,lng_pos_fusion;
extern float lat_vel_fusion,lng_vel_fusion;
extern float lat_accel_fusion,lng_accel_fusion;


//第九帧数据，功能字0x09  数据长度36
extern float userdata[9];

//第10、11、12、13、14、15帧数据，功能字0x0A、0x0B、0x0C、0x0D、0x0E、0x0F  数据长度18
extern uint16_t kp[18];
extern uint16_t ki[18];
extern uint16_t kd[18];

//第16帧数据，功能字0x10  数据长度16
extern uint16_t targeheight,safeheight,safevbat,maxheight;
extern uint16_t maxradius,maxupvel,maxdownvel,maxhorvel;

//第17帧数据，功能字11  数据长度36
extern uint8_t gyro_auto_cal_flag;
extern float gyro_x_raw,gyro_y_raw,gyro_z_raw;
extern float acce_x_raw,acce_y_raw,acce_z_raw;
extern float mag_x_raw,mag_y_raw,mag_z_raw;


//第17帧数据，功能字12  数据长度56
extern float gyro_x_offset,gyro_y_offset,gyro_z_offset;
extern float acce_x_offset,acce_y_offset,acce_z_offset;
extern float acce_x_scale,acce_y_scale,acce_z_scale;
extern float mag_x_offset,mag_y_offset,mag_z_offset;
extern float pitch_offset,roll_offset;




#endif




