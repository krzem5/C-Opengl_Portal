#include <opengl.h>
#include <shader.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



static GLuint _load(const void* dt,GLenum t){
	GLuint o=glCreateShader(t);
	glShaderSource(o,1,(const GLchar**)(&dt),NULL);
	glCompileShader(o);
	GLint ok=0;
	glGetShaderiv(o,GL_COMPILE_STATUS,&ok);
	if (ok){
		return o;
	}
	GLint sz;
	glGetShaderiv(o,GL_INFO_LOG_LENGTH,&sz);
	GLchar* tmp=malloc(sz*sizeof(GLchar));
	glGetShaderInfoLog(o,sz,&sz,tmp);
	fwrite(tmp,sz,sizeof(GLchar),stdout);
	free(tmp);
	return 0;
}



void create_shader(shader_t* s,const char* v,const char* f){
	GLuint vs=_load(v,GL_VERTEX_SHADER);
	GLuint fs=_load(f,GL_FRAGMENT_SHADER);
	s->_p=glCreateProgram();
	glAttachShader(s->_p,vs);
	glAttachShader(s->_p,fs);
	glBindAttribLocation(s->_p,0,"pos");
	glBindAttribLocation(s->_p,1,"uv");
	glBindAttribLocation(s->_p,2,"norm");
	glLinkProgram(s->_p);
	glDetachShader(s->_p,vs);
	glDetachShader(s->_p,fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	GLint ok=0;
	glGetProgramiv(s->_p,GL_LINK_STATUS,&ok);
	if (ok){
		glUseProgram(s->_p);
		s->_m=glGetUniformLocation(s->_p,"m");
		s->_mvp=glGetUniformLocation(s->_p,"mvp");
		s->_tex=glGetUniformLocation(s->_p,"tex");
		return;
	}
	glDeleteProgram(s->_p);
	GLint sz;
	glGetProgramiv(s->_p,GL_INFO_LOG_LENGTH,&sz);
	GLchar* tmp=malloc(sz*sizeof(GLchar));
	glGetProgramInfoLog(s->_p,sz,&sz,tmp);
	fwrite(tmp,sz,sizeof(GLchar),stdout);
	free(tmp);
}



void free_shader(shader_t* s){
	glDeleteProgram(s->_p);
}



void set_shader_global(const shader_t* s,const float* m,const float* mvp,GLenum tx){
	glUniformMatrix4fv(s->_m,1,GL_FALSE,m);
	glUniformMatrix4fv(s->_mvp,1,GL_FALSE,mvp);
	glUniform1i(s->_tex,tx);
}



void use_shader(const shader_t* s){
	glUseProgram(s->_p);
}
