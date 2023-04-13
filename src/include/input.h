#ifndef __INPUT_H__
#define __INPUT_H__ 1
#include <stdint.h>



#define BUTTON_LEFT 1
#define BUTTON_MIDDLE 2
#define BUTTON_RIGHT 4
#define BUTTON_LEFT_PRESS 8
#define BUTTON_MIDDLE_PRESS 16
#define BUTTON_RIGHT_PRESS 32



#define KEY_PRESSED(v) (inp_dt->k[(v)>>6]&(1ull<<((v)&63)))



typedef struct __INPUT_DATA{
	uint64_t k[4];
	uint64_t kp[4];
	float m_dx;
	float m_dy;
	float m_ddx;
	float m_ddy;
	uint8_t m_btn;
} input_data_t;



extern input_data_t* inp_dt;



void end_input_data(void);



#endif
