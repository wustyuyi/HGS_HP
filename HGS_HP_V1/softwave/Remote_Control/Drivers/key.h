#ifndef __KEY_H
#define __KEY_H


#define LONG_PRESS_LIMIT  1000//2000ms
#define IN_PRESS_LIMIT  	250//2000ms


#define RC_MAX_LIMIT 2100 
#define RC_MIN_LIMIT 900
#define RC_MID_LIMIT 1500
#define RC_OFFSET_LIMIT 100


typedef enum {
	UP=0,
	DOWN,
	LEFT,
	RIGHT,
	EXIT,
	ENTER,
	SWITCH_UP,
	SWITCH_DOWN,
	BUTTON_NUM
}BUTTON;

typedef enum
{
	NO_PRESS=0,
	SHORT_PRESS,
  LONG_PRESS,
  IN_PRESS,	
}press_state;

typedef struct
{
	press_state press;
  uint8_t value;
	uint8_t last_value;	
	GPIO_TypeDef *port;
	uint16_t pin;
	uint32_t press_time;
  uint32_t release_time; 
  uint32_t in_time; 
	uint32_t in_press_cnt;
}button_state;

typedef struct
{
  button_state state[BUTTON_NUM];
}rc_buttton;


void Key_Init(void);
void Read_Button_State_All(void);

extern rc_buttton _button;
#endif


