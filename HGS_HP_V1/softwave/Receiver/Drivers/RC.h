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

typedef struct
{
  uint16_t rcdata[RC_CHL_MAX];
	uint16_t vbat_mv;
	uint8_t prase_success;
	uint8_t lose_ctrl_protect;
	int8_t lose_ctrl_protect_channel;
	uint16_t lose_ctrl_protect_value;
	uint8_t gps_ok;
  uint32_t gps_lng;
	uint32_t gps_lat;	
}rc;


void Remote_Ctrl_Prase(void);
void RC_All_Init(void);



extern rc RC_Data;

#endif


