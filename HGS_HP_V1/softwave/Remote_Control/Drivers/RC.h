#ifndef __RC_H
#define __RC_H

typedef enum 
{
	RC_ROLL_CHANNEL=0,
	RC_PITCH_CHANNEL,
	RC_THR_CHANNEL,
	RC_YAW_CHANNEL,
	RC_SWA_CHANNEL,
	RC_SWB_CHANNEL,
	RC_SWC_CHANNEL,
	RC_SWD_CHANNEL,
	RC_VRA_CHANNEL,
	RC_VRB_CHANNEL,
	RC_CHL_MAX
}RC_CHL_MAP;

typedef enum
{
  SWA=0,
  SWB,
  SWC,
  SWD,
  VRA,
  VRB,
	CH_MAP_NUM
}CH_REMAP;


typedef struct
{
  uint16_t max;
	uint16_t min;
  int16_t offset;
}rc_cal_data;


typedef struct
{
	uint16_t rcdata_original[RC_CHL_MAX];
  uint16_t rcdata[RC_CHL_MAX];
	uint16_t vbat_mv;
	rc_cal_data cal[RC_CHL_MAX];
	int8_t rock_ch_remap[4];
	int8_t func_ch_remap[6];
	uint8_t lose_ctrl_protect;
	int8_t lose_ctrl_protect_channel;
	uint16_t lose_ctrl_protect_value;
	float safe_vbat_v;
	float flight_safe_vbat_v;
	uint8_t flight_safe_vbat_enable;
}rc;






void Remote_Ctrl_Prase(void);
void RC_All_Init(void);



extern rc RC_Data;

#endif


