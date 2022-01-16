#include <input.h>
#include <stdint.h>



#define MOUSE_SMOOTH 0.25f



static input_data_t _inp_dt={
	{
		0,
		0,
		0,
		0
	},
	{
		0,
		0,
		0,
		0
	},
	0,
	0,
	0,
	0,
	0
};



input_data_t* inp_dt=&_inp_dt;



void end_input_data(void){
	inp_dt->kp[0]=0;
	inp_dt->kp[1]=0;
	inp_dt->kp[2]=0;
	inp_dt->kp[3]=0;
	inp_dt->m_dx=inp_dt->m_dx*MOUSE_SMOOTH+inp_dt->m_ddx*(1-MOUSE_SMOOTH);
	inp_dt->m_dy=inp_dt->m_dy*MOUSE_SMOOTH+inp_dt->m_ddy*(1-MOUSE_SMOOTH);
	inp_dt->m_ddx=0;
	inp_dt->m_ddy=0;
	inp_dt->m_btn&=~(BUTTON_LEFT_PRESS|BUTTON_MIDDLE_PRESS|BUTTON_RIGHT_PRESS);
}
