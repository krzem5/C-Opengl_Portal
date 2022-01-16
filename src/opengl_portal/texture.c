#include <opengl.h>
#include <texture.h>
#include <stdint.h>



void create_texture(texture_t* t,const void* dt,uint32_t w,uint32_t h){
	t->id=0;
	glGenTextures(1,&(t->_h));
	glBindTexture(GL_TEXTURE_2D,t->_h);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,dt);
}



void free_texture(texture_t* t){
	glDeleteTextures(1,&(t->_h));
}



void use_texture(const texture_t* t){
	glActiveTexture(t->id+GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,t->_h);
}
