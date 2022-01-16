#ifndef __TEXTURE_H__
#define __TEXTURE_H__ 1
#include <opengl.h>
#include <stdint.h>



typedef struct __TEXTURE{
	uint32_t w;
	uint32_t h;
	GLenum id;
	GLint _h;
} texture_t;



void create_texture(texture_t* t,const void* dt,uint32_t w,uint32_t h);



void free_texture(texture_t* t);



void use_texture(const texture_t* t);



#endif
