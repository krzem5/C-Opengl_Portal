#include <camera.h>
#include <input.h>
#include <transform.h>
#include <stdint.h>
#include <math.h>



#define CAMERA_FOV PI/4
#define PI 3.141592653589793f
#define SQRT_2 0.7071067811865475f
#define MOUSE_SENSITIVITY 0.01f
#define SPEED 0.05f



void create_camera(camera_t* c,uint32_t w,uint32_t h,float n,float f){
	zero_transform(&(c->t));
	c->t.sx=0;
	c->t.sy=0;
	c->t.sz=0;
	c->n=n;
	c->f=f;
	float a=1/(f-n);
	c->pm[1]=0;
	c->pm[2]=0;
	c->pm[3]=0;
	c->pm[4]=0;
	c->pm[6]=0;
	c->pm[7]=0;
	c->pm[8]=0;
	c->pm[9]=0;
	c->pm[10]=(n+f)*a;
	c->pm[11]=-2*n*f*a;
	c->pm[12]=0;
	c->pm[13]=0;
	c->pm[14]=1;
	c->pm[15]=0;
	resize_camera(c,w,h);
}



void resize_camera(camera_t* c,uint32_t w,uint32_t h){
	c->w=w;
	c->h=h;
	float a=1/tanf(CAMERA_FOV/2);
	c->pm[0]=a*((float)h)/w;
	c->pm[5]=a;
}



void update_camera(camera_t* c){
	c->t.rx-=inp_dt->m_dy*MOUSE_SENSITIVITY;
	if (c->t.rx>PI/2){
		c->t.rx=PI/2;
	}
	else if (c->t.rx<-PI/2){
		c->t.rx=-PI/2;
	}
	c->t.ry-=inp_dt->m_dx*MOUSE_SENSITIVITY;
	if (c->t.ry>PI){
		c->t.ry-=PI*2;
	}
	else if (c->t.ry<-PI){
		c->t.ry+=PI*2;
	}
	float fb=0;
	float lr=0;
	if (KEY_PRESSED('W')){
		fb++;
	}
	if (KEY_PRESSED('A')){
		lr--;
	}
	if (KEY_PRESSED('S')){
		fb--;
	}
	if (KEY_PRESSED('D')){
		lr++;
	}
	float m=(!fb||!lr?SPEED:SQRT_2*SPEED);
	fb*=m;
	lr*=m;
	float rs=sinf(c->t.ry);
	float rc=cosf(c->t.ry);
	c->t.x+=rc*lr-rs*fb;
	c->t.y=1.5f;
	c->t.z+=rs*lr+rc*fb;
	recalculate_transform(&(c->t));
}



void use_camera(const camera_t* c){
	glViewport(0,0,c->w,c->h);
}
