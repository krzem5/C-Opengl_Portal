#ifndef __OPENGL_H__
#define __OPENGL_H__ 1
#ifndef APIENTRY
#define APIENTRY __stdcall
#endif
#ifndef WINGDIAPI
#define WINGDIAPI __declspec(dllimport)
#endif
#include <GL/gl.h>



#define __DECL_FUNC(nm,r,...) typedef r (APIENTRY *__##nm##_type)(__VA_ARGS_);extern __##nm##_type nm



#define GL_ARRAY_BUFFER 0x8892
#define GL_COMPILE_STATUS 0x8b81
#define GL_FRAGMENT_SHADER 0x8b30
#define GL_INFO_LOG_LENGTH 0x8b84
#define GL_LINK_STATUS 0x8b82
#define GL_QUERY_COUNTER_BITS_ARB 0x8864
#define GL_SAMPLES_PASSED_ARB 0x8914
#define GL_STATIC_DRAW 0x88e4
#define GL_TEXTURE0 0x84c0
#define GL_VERTEX_SHADER 0x8b31



typedef char GLchar;



__DECL_FUNC(glActiveTexture,void,GLenum);
__DECL_FUNC(glAttachShader,void,GLuint,GLuint);
__DECL_FUNC(glBindAttribLocation,void,GLuint,GLuint,const GLchar*);
__DECL_FUNC(glBindBuffer,void,GLenum,GLuint);
__DECL_FUNC(glBindVertexArray,void,GLuint);
__DECL_FUNC(glBufferData,void,GLenum,GLsizeiptr,const void*,GLenum);
__DECL_FUNC(glCompileShader,void,GLuint);
__DECL_FUNC(glCreateProgram,GLuint,void);
__DECL_FUNC(glCreateShader,GLuint,GLenum);
__DECL_FUNC(glDeleteBuffers,void,GLsizei,const GLuint*);
__DECL_FUNC(glDeleteProgram,void,GLuint);
__DECL_FUNC(glDeleteShader,void,GLuint);
__DECL_FUNC(glDeleteVertexArrays,void,GLsizei,const GLuint*);
__DECL_FUNC(glDetachShader,void,GLuint,GLuint);
__DECL_FUNC(glEnableVertexAttribArray,void,GLuint);
__DECL_FUNC(glGenBuffers,void,GLsizei,GLuint*);
__DECL_FUNC(glGenVertexArrays,void,GLsizei,GLuint*);
__DECL_FUNC(glGetProgramInfoLog,void,GLuint,GLsizei,GLsizei*,GLchar*);
__DECL_FUNC(glGetProgramiv,void,GLuint,GLenum,GLint*);
__DECL_FUNC(glGetQueryiv,void,GLenum,GLenum,GLint*);
__DECL_FUNC(glGetShaderInfoLog,void,GLuint,GLsizei,GLsizei*,GLchar*);
__DECL_FUNC(glGetShaderiv,void,GLuint,GLenum,GLint*);
__DECL_FUNC(glGetUniformLocation,GLint,GLuint,const GLchar*);
__DECL_FUNC(glLinkProgram,void,GLuint);
__DECL_FUNC(glShaderSource,void,GLuint,GLsizei,const GLchar*const*,const GLint*);
__DECL_FUNC(glUniform1i,void,GLint,GLsizei,const GLint*);
__DECL_FUNC(glUniformMatrix4fv,void,GLint,GLsizei,GLboolean,const GLfloat*);
__DECL_FUNC(glUseProgram,void,GLuint);
__DECL_FUNC(glVertexAttribPointer,void,GLuint,GLint,GLenum,GLboolean,GLsizei,const void*);
__DECL_FUNC(wglSwapIntervalEXT,int,int);



void init_gl(void);



#endif
