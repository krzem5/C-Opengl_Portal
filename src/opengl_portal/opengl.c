#ifndef _MSC_VER
#error Currently only Windows is supported
#endif
#include <windows.h>
#include <opengl.h>
#include <signal.h>
#include <stdio.h>



#define DECL_FUNC(nm) __##nm##_type nm
#define LOAD_FUNC(nm) o|=!(nm=(__##nm##_type)wglGetProcAddress(#nm));



DECL_FUNC(glActiveTexture);
DECL_FUNC(glAttachShader);
DECL_FUNC(glBindAttribLocation);
DECL_FUNC(glBindBuffer);
DECL_FUNC(glBindFramebufferEXT);
DECL_FUNC(glBindRenderbufferEXT);
DECL_FUNC(glBindVertexArray);
DECL_FUNC(glBufferData);
DECL_FUNC(glCheckFramebufferStatusEXT);
DECL_FUNC(glCompileShader);
DECL_FUNC(glCreateProgram);
DECL_FUNC(glCreateShader);
DECL_FUNC(glDeleteBuffers);
DECL_FUNC(glDeleteFramebuffersEXT);
DECL_FUNC(glDeleteProgram);
DECL_FUNC(glDeleteRenderbuffersEXT);
DECL_FUNC(glDeleteShader);
DECL_FUNC(glDeleteVertexArrays);
DECL_FUNC(glDetachShader);
DECL_FUNC(glEnableVertexAttribArray);
DECL_FUNC(glFramebufferRenderbufferEXT);
DECL_FUNC(glFramebufferTexture2DEXT);
DECL_FUNC(glGenBuffers);
DECL_FUNC(glGenFramebuffersEXT);
DECL_FUNC(glGenRenderbuffersEXT);
DECL_FUNC(glGenVertexArrays);
DECL_FUNC(glGetProgramInfoLog);
DECL_FUNC(glGetProgramiv);
DECL_FUNC(glGetQueryiv);
DECL_FUNC(glGetShaderInfoLog);
DECL_FUNC(glGetShaderiv);
DECL_FUNC(glGetUniformLocation);
DECL_FUNC(glLinkProgram);
DECL_FUNC(glRenderbufferStorageEXT);
DECL_FUNC(glShaderSource);
DECL_FUNC(glUniform1i);
DECL_FUNC(glUniformMatrix4fv);
DECL_FUNC(glUseProgram);
DECL_FUNC(glVertexAttribPointer);
DECL_FUNC(wglSwapIntervalEXT);



void init_gl(void){
	char o=0;
	LOAD_FUNC(glActiveTexture);
	LOAD_FUNC(glAttachShader);
	LOAD_FUNC(glBindAttribLocation);
	LOAD_FUNC(glBindBuffer);
	LOAD_FUNC(glBindFramebufferEXT);
	LOAD_FUNC(glBindRenderbufferEXT);
	LOAD_FUNC(glBindVertexArray);
	LOAD_FUNC(glBufferData);
	LOAD_FUNC(glCheckFramebufferStatusEXT);
	LOAD_FUNC(glCompileShader);
	LOAD_FUNC(glCreateProgram);
	LOAD_FUNC(glCreateShader);
	LOAD_FUNC(glDeleteBuffers);
	LOAD_FUNC(glDeleteFramebuffersEXT);
	LOAD_FUNC(glDeleteProgram);
	LOAD_FUNC(glDeleteRenderbuffersEXT);
	LOAD_FUNC(glDeleteShader);
	LOAD_FUNC(glDeleteVertexArrays);
	LOAD_FUNC(glDetachShader);
	LOAD_FUNC(glEnableVertexAttribArray);
	LOAD_FUNC(glFramebufferRenderbufferEXT);
	LOAD_FUNC(glFramebufferTexture2DEXT);
	LOAD_FUNC(glGenBuffers);
	LOAD_FUNC(glGenFramebuffersEXT);
	LOAD_FUNC(glGenRenderbuffersEXT);
	LOAD_FUNC(glGenVertexArrays);
	LOAD_FUNC(glGetProgramInfoLog);
	LOAD_FUNC(glGetProgramiv);
	LOAD_FUNC(glGetQueryiv);
	LOAD_FUNC(glGetShaderInfoLog);
	LOAD_FUNC(glGetShaderiv);
	LOAD_FUNC(glGetUniformLocation);
	LOAD_FUNC(glLinkProgram);
	LOAD_FUNC(glRenderbufferStorageEXT);
	LOAD_FUNC(glShaderSource);
	LOAD_FUNC(glUniform1i);
	LOAD_FUNC(glUniformMatrix4fv);
	LOAD_FUNC(glUseProgram);
	LOAD_FUNC(glVertexAttribPointer);
	LOAD_FUNC(wglSwapIntervalEXT);
	if (o){
		fputs("Failed to load all OpenGL functions\n",stdout);
		raise(SIGABRT);
	}
}
