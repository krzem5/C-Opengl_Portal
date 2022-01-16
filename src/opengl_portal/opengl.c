#ifndef _MSC_VER
#error Currently only Windows is supported
#endif
#include <windows.h>
#include <opengl.h>



#define DECL_FUNC(nm) __##nm##_type nm
#define LOAD_FUNC(nm) nm=(__##nm##_type)wglGetProcAddress(#nm)



DECL_FUNC(glActiveTexture);
DECL_FUNC(glAttachShader);
DECL_FUNC(glBindAttribLocation);
DECL_FUNC(glBindBuffer);
DECL_FUNC(glBindVertexArray);
DECL_FUNC(glBufferData);
DECL_FUNC(glCompileShader);
DECL_FUNC(glCreateProgram);
DECL_FUNC(glCreateShader);
DECL_FUNC(glDeleteBuffers);
DECL_FUNC(glDeleteProgram);
DECL_FUNC(glDeleteShader);
DECL_FUNC(glDeleteVertexArrays);
DECL_FUNC(glDetachShader);
DECL_FUNC(glEnableVertexAttribArray);
DECL_FUNC(glGenBuffers);
DECL_FUNC(glGenVertexArrays);
DECL_FUNC(glGetProgramInfoLog);
DECL_FUNC(glGetProgramiv);
DECL_FUNC(glGetQueryiv);
DECL_FUNC(glGetShaderInfoLog);
DECL_FUNC(glGetShaderiv);
DECL_FUNC(glGetUniformLocation);
DECL_FUNC(glLinkProgram);
DECL_FUNC(glShaderSource);
DECL_FUNC(glUniform1i);
DECL_FUNC(glUniformMatrix4fv);
DECL_FUNC(glUseProgram);
DECL_FUNC(glVertexAttribPointer);
DECL_FUNC(wglSwapIntervalEXT);



void init_gl(void){
	LOAD_FUNC(glActiveTexture);
	LOAD_FUNC(glAttachShader);
	LOAD_FUNC(glBindAttribLocation);
	LOAD_FUNC(glBindBuffer);
	LOAD_FUNC(glBindVertexArray);
	LOAD_FUNC(glBufferData);
	LOAD_FUNC(glCompileShader);
	LOAD_FUNC(glCreateProgram);
	LOAD_FUNC(glCreateShader);
	LOAD_FUNC(glDeleteBuffers);
	LOAD_FUNC(glDeleteProgram);
	LOAD_FUNC(glDeleteShader);
	LOAD_FUNC(glDeleteVertexArrays);
	LOAD_FUNC(glDetachShader);
	LOAD_FUNC(glEnableVertexAttribArray);
	LOAD_FUNC(glGenBuffers);
	LOAD_FUNC(glGenVertexArrays);
	LOAD_FUNC(glGetProgramInfoLog);
	LOAD_FUNC(glGetProgramiv);
	LOAD_FUNC(glGetQueryiv);
	LOAD_FUNC(glGetShaderInfoLog);
	LOAD_FUNC(glGetShaderiv);
	LOAD_FUNC(glGetUniformLocation);
	LOAD_FUNC(glLinkProgram);
	LOAD_FUNC(glShaderSource);
	LOAD_FUNC(glUniform1i);
	LOAD_FUNC(glUniformMatrix4fv);
	LOAD_FUNC(glUseProgram);
	LOAD_FUNC(glVertexAttribPointer);
	LOAD_FUNC(wglSwapIntervalEXT);
}
