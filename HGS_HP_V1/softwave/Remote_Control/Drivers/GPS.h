#ifndef _GPS_H
#define _GPS_H


typedef struct
{
	uint8_t validdata :1;
	uint8_t validtime :1;
	uint8_t fullyresolved :1;
	uint8_t nc:5;
}validity_flag;



typedef struct
{
	uint8_t gnssfixok :1;
	uint8_t diffsoln :1;
	uint8_t psmstate :3;
	uint8_t headvehvalid :1;
	uint8_t nc:2;
}gps_flags;




typedef struct
{
	uint32_t itow;//4
	uint16_t year;//2
	uint8_t month;//1
	uint8_t day;//1
  uint8_t hour;//1
  uint8_t min;//1
  uint8_t sec;//1
	validity_flag valid;//1
  uint32_t tacc;//4
	int32_t nano;//4
	uint8_t fixtype;//1
	gps_flags flags;//1
	uint8_t reserved1;//1
	uint8_t numsv;//1
	int32_t lon;
	int32_t lat;
	int32_t height;
	int32_t hmsl;
	uint32_t hacc;
	uint32_t vacc;
	int32_t veln;
	int32_t vele;
	int32_t veld;
	int32_t gspeed;
	int32_t headmot;
	uint32_t sacc;
	uint32_t headacc;
	uint16_t pdop;
	uint8_t reserved2[6];
	int32_t headveh;
	uint8_t reserved3[4];
}pvt_data;






extern pvt_data gps_pvt;

void Ublox_Set_Output_PVT_10hz_Baud_Set(unsigned long Baud);
void Set_GPS_USART(void);
void GPS_Data_Prase(void);

#endif


