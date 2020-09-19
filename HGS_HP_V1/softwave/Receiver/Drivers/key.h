#ifndef __KEY_H
#define __KEY_H


#define LONG_PRESS_LIMIT  1000//2000ms

typedef enum {
	UP=0,
	BUTTON_NUM
}BUTTON;

typedef enum
{
	NO_PRESS=0,
	SHORT_PRESS,
  LONG_PRESS,	
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
}button_state;

typedef struct
{
  button_state state[BUTTON_NUM];
}rc_buttton;


void Key_Init(void);
void Read_Button_State_All(void);

extern rc_buttton _button;
#endif


