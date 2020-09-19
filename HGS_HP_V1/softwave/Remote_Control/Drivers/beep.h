#ifndef __BEEP_H
#define __BEEP_H


typedef enum{
	HF=0,
  IF,
  LF,
	FNUM	
}beep_freq;

typedef struct
{
  uint16_t time;
}beep;


extern beep rc_beep;


void Beep_PWM_Init(uint32_t period);
void beep_para_set(float percent,beep_freq type);
void beep_init(void);
void beep_run(void);
#endif










