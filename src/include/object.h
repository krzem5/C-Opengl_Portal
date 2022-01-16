#ifndef __OBJECT_H__
#define __OBJECT_H__ 1
#include <camera.h>
#include <opengl.h>
#include <shader.h>
#include <texture.h>
#include <transform.h>



typedef struct __OBJECT{
	const shader_t* s;
	const texture_t* tx;
	transform_t t;
	GLsizei _vl;
	GLsizei _sz;
	GLuint _va;
	GLuint _vb[3];
} object_t;



void create_object(object_t* o,const float* vl,unsigned int vll,const float* uvl,unsigned int uvll,const float* nl,unsigned int nll,const shader_t* s,const texture_t* tx);



void draw_object(const object_t* o,const camera_t* c);



void free_object(object_t* o);



#endif
