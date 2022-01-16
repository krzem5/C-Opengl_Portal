#ifndef __SHADER_H__
#define __SHADER_H__ 1
#include <opengl.h>



typedef struct __SHADER{
	GLint _m;
	GLint _mvp;
	GLint _tex;
	GLuint _vs;
	GLuint _fs;
	GLuint _p;
} shader_t;



void create_shader(shader_t* s,const char* v,const char* f);



void free_shader(shader_t* s);



void set_shader_global(const shader_t* s,const float* m,const float* mvp,GLenum tx);



void use_shader(const shader_t* s);



#endif
