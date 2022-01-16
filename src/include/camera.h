#ifndef __CAMERA_H__
#define __CAMERA_H__ 1
#include <opengl.h>
#include <transform.h>
#include <stdint.h>



typedef struct __CAMERA{
	uint32_t w;
	uint32_t h;
	float n;
	float f;
	float pm[16];
	transform_t t;
} camera_t;



void create_camera(camera_t* c,uint32_t w,uint32_t h,float n,float f);



void resize_camera(camera_t* c,uint32_t w,uint32_t h);



void update_camera(camera_t* c);



void use_camera(const camera_t* c);



#endif
