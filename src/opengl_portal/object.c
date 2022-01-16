#include <object.h>
#include <opengl.h>
#include <shader.h>
#include <transform.h>
#include <stdint.h>



void create_object(object_t* o,const float* vl,unsigned int vll,const float* uvl,unsigned int uvll,const float* nl,unsigned int nll,const shader_t* s,const texture_t* tx){
	o->s=s;
	o->tx=tx;
	zero_transform(&(o->t));
	o->_vl=vll/3;
	o->_sz=!!vll+!!uvll+!!nll;
	glGenVertexArrays(1,&(o->_va));
	glBindVertexArray(o->_va);
	glGenBuffers(o->_sz,o->_vb);
	if (vll){
		glBindBuffer(GL_ARRAY_BUFFER,o->_vb[0]);
		glBufferData(GL_ARRAY_BUFFER,vll*sizeof(GLfloat),vl,GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
	}
	if (uvll){
		glBindBuffer(GL_ARRAY_BUFFER,o->_vb[1]);
		glBufferData(GL_ARRAY_BUFFER,uvll*sizeof(float),uvl,GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);
	}
	if (nll){
		glBindBuffer(GL_ARRAY_BUFFER,o->_vb[2]);
		glBufferData(GL_ARRAY_BUFFER,nll*sizeof(float),nl,GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,NULL);
	}
}



void draw_object(const object_t* o,const camera_t* c){
	use_shader(o->s);
	if (o->tx){
		use_texture(o->tx);
	}
	float mv[16];
	float mvp[16];
	mult_matrix(c->t.m,o->t.m,mv);
	mult_matrix(c->pm,mv,mvp);
	set_shader_global(o->s,o->t.m,mvp,(o->tx?o->tx->id:0));
	glBindVertexArray(o->_va);
	glDrawArrays(GL_TRIANGLES,0,o->_vl);
}



void free_object(object_t* o){
	glDeleteBuffers(o->_sz,o->_vb);
	glDeleteVertexArrays(1,&(o->_va));
}
