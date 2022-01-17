#include <opengl.h>
#include <camera.h>
#include <engine.h>
#include <object.h>
#include <shader.h>
#include <texture.h>



#define NEG(x) ((x)>0?-(x):(x))



#define FRAME_BUFFER_COUNT 3
#define FRAME_BUFFER_SIZE 2048



typedef struct __FRAME_BUFFER_ARRAY{
	GLuint id[FRAME_BUFFER_COUNT];
	GLuint tx[FRAME_BUFFER_COUNT];
	GLuint r_bf[FRAME_BUFFER_COUNT];
} frame_buffer_array_t;



static camera_t cam;
static frame_buffer_array_t fba;
static object_t cube;
static object_t ground;
static object_t portal;
static object_t sky;
static shader_t sky_shader;
static shader_t portal_shader;
static shader_t tex_shader;
static texture_t error_texture;
static texture_t texture;



static void draw_recursive(camera_t* c,unsigned int lvl);



static void init(void){
	create_camera(&cam,1,1,1e-3f,1000);
	const char* tex_vert="#version 330 core\n\
	uniform mat4 m;\n\
	uniform mat4 mvp;\n\
	layout(location=0) in vec3 pos;\n\
	layout(location=1) in vec2 uv;\n\
	layout(location=2) in vec3 norm;\n\
	out vec2 f_uv;\n\
	out vec3 f_norm;\n\
	void main(void){\n\
		gl_Position=vec4(pos,1.0)*mvp;\n\
		f_uv=uv;\n\
		f_norm=normalize((vec4(norm,0.0)*m).xyz);\n\
	}";
	const char* tex_frag="#version 330 core\n\
	precision highp float;\n\
	#define LIGHT vec3(-0.36,0.80,-0.48)\n\
	uniform sampler2D tex;\n\
	in vec2 f_uv;\n\
	in vec3 f_norm;\n\
	out vec4 gl_FragColor;\n\
	void main(void){\n\
		gl_FragColor=vec4(texture(tex,f_uv).rgb*(dot(f_norm,LIGHT)*0.25+0.5),1.0);\n\
	}";
	create_shader(&tex_shader,tex_vert,tex_frag);
	const char* portal_vert="#version 330 core\n\
	uniform mat4 m;\n\
	uniform mat4 mvp;\n\
	layout(location=0) in vec3 pos;\n\
	layout(location=1) in vec2 uv;\n\
	out vec2 f_uv;\n\
	void main(void){\n\
		gl_Position=vec4(pos,1.0)*mvp;\n\
		f_uv=uv;\n\
	}";
	const char* portal_frag="#version 330 core\n\
	precision highp float;\n\
	uniform sampler2D tex;\n\
	in vec2 f_uv;\n\
	out vec4 gl_FragColor;\n\
	void main(void){\n\
		gl_FragColor=vec4(texture(tex,f_uv).rgb,1.0);\n\
	}";
	create_shader(&portal_shader,portal_vert,portal_frag);
	const char* sky_vert="#version 330 core\n\
	uniform mat4 m;\n\
	uniform mat4 mvp;\n\
	layout(location=0) in vec3 pos;\n\
	out vec3 f_norm;\n\
	void main(void){\n\
		gl_Position=vec4(pos.xy,0.0,1.0);\n\
		f_norm=(vec4(normalize((gl_Position*mvp).xyz),0.0)*m).xyz;\n\
	}";
	const char* sky_frag="#version 330 core\n\
	precision highp float;\n\
	#define LIGHT vec3(-0.36,0.80,-0.48)\n\
	#define SUN_SIZE 0.003\n\
	#define SKY_R 0.2\n\
	#define SKY_G 0.5\n\
	#define SKY_B 1.0\n\
	in vec3 f_norm;\n\
	out vec4 gl_FragColor;\n\
	void main(void){\n\
		vec3 n=normalize(f_norm);\n\
		float h=(1.0-n.y)*(1.0-n.y)*0.5;\n\
		gl_FragColor=vec4(max(vec3(SKY_R+h,SKY_G+h,SKY_B),min(exp((dot(n,LIGHT)+SUN_SIZE-1.0)/SUN_SIZE),1.0)),1.0);\n\
	}";
	create_shader(&sky_shader,sky_vert,sky_frag);
	const uint8_t tex_dt[14]={
		255,255,255,128,128,128,
		0,0,
		128,128,128,255,255,255
	};
	create_texture(&texture,tex_dt,2,2);
	const uint8_t err_tex_dt[4]={
		255,0,0,0
	};
	create_texture(&error_texture,err_tex_dt,1,1);
	const float c_vl[]={
		-1,-1,-1,
		-1,-1,1,
		-1,1,1,
		-1,-1,-1,
		-1,1,1,
		-1,1,-1,
		1,-1,-1,
		1,1,1,
		1,-1,1,
		1,-1,-1,
		1,1,-1,
		1,1,1,
		-1,-1,-1,
		1,-1,1,
		-1,-1,1,
		-1,-1,-1,
		1,-1,-1,
		1,-1,1,
		-1,1,-1,
		-1,1,1,
		1,1,1,
		-1,1,-1,
		1,1,1,
		1,1,-1,
		-1,-1,-1,
		-1,1,-1,
		1,1,-1,
		-1,-1,-1,
		1,1,-1,
		1,-1,-1,
		-1,-1,1,
		1,1,1,
		-1,1,1,
		-1,-1,1,
		1,-1,1,
		1,1,1,
	};
	const float c_uvl[]={
		0,1,
		0,0,
		1,0,
		0,1,
		1,0,
		1,1,
		1,1,
		0,0,
		1,0,
		1,1,
		0,1,
		0,0,
		1,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		0,0,
		0,1,
		1,1,
		0,0,
		1,1,
		1,0,
		0,1,
		0,0,
		1,0,
		0,1,
		1,0,
		1,1,
		1,1,
		0,0,
		1,0,
		1,1,
		0,1,
		0,0,
	};
	const float c_nl[]={
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0
	};
	create_object(&cube,c_vl,sizeof(c_vl)/sizeof(float),c_uvl,sizeof(c_uvl)/sizeof(float),c_nl,sizeof(c_nl)/sizeof(float),&tex_shader,&texture);
	const float g_vl[]={
		-10,0,-10,
		10,0,10,
		10,0,-10,
		-10,0,-10,
		-10,0,10,
		10,0,10
	};
	const float g_uvl[]={
		0,0,
		20,20,
		20,0,
		0,0,
		0,20,
		20,20
	};
	const float g_nl[]={
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0
	};
	create_object(&ground,g_vl,sizeof(g_vl)/sizeof(float),g_uvl,sizeof(g_uvl)/sizeof(float),g_nl,sizeof(g_nl)/sizeof(float),&tex_shader,&texture);
	const float s_vl[]={
		1,1,0,
		-1,-1,0,
		-1,1,0,
		1,1,0,
		1,-1,0,
		-1,-1,0
	};
	create_object(&sky,s_vl,sizeof(s_vl)/sizeof(float),NULL,0,NULL,0,&sky_shader,NULL);
	const float p_vl[]={
		1,1,0,
		-1,-1,0,
		-1,1,0,
		1,1,0,
		1,-1,0,
		-1,-1,0
	};
	const float p_uvl[]={
		1,1,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0
	};
	create_object(&portal,p_vl,sizeof(p_vl)/sizeof(float),p_uvl,sizeof(p_uvl)/sizeof(float),NULL,0,&portal_shader,NULL);
	GLint occ;
	glGetQueryiv(GL_SAMPLES_PASSED_ARB,GL_QUERY_COUNTER_BITS_ARB,&occ);
	if (!occ){
		return;
	}
	glGenFramebuffersEXT(FRAME_BUFFER_COUNT,fba.id);
	glGenTextures(FRAME_BUFFER_COUNT,fba.tx);
	glGenRenderbuffersEXT(FRAME_BUFFER_COUNT,fba.r_bf);
	for (unsigned int i=0;i<FRAME_BUFFER_COUNT;i++){
		glBindTexture(GL_TEXTURE_2D,fba.tx[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,FRAME_BUFFER_SIZE,FRAME_BUFFER_SIZE,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fba.id[i]);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D,fba.tx[i],0);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,fba.r_bf[i]);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,GL_DEPTH_COMPONENT16,FRAME_BUFFER_SIZE,FRAME_BUFFER_SIZE);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,GL_DEPTH_ATTACHMENT_EXT,GL_RENDERBUFFER_EXT,fba.r_bf[i]);
		if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT)!=GL_FRAMEBUFFER_COMPLETE_EXT){
			return;
		}
	}
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
}



static void update(void){
	cube.t.y=1;
	cube.t.rx+=0.02f;
	cube.t.rz+=0.03f;
	cube.t.sx=0.5f;
	cube.t.sy=0.5f;
	cube.t.sz=0.5f;
	recalculate_transform(&(cube.t));
	portal.t.y=1;
	portal.t.z=5;
	recalculate_transform(&(portal.t));
	update_camera(&cam);
}



static void resize(unsigned int w,unsigned int h){
	resize_camera(&cam,w,h);
}



static void draw_portal(object_t* o,camera_t* c,unsigned int lvl){
	if (lvl<FRAME_BUFFER_COUNT){
		float x=-c->t.m[1]*c->t.m[6]*c->t.m[11]+c->t.m[1]*c->t.m[7]*c->t.m[10]+c->t.m[5]*c->t.m[2]*c->t.m[11]-c->t.m[5]*c->t.m[3]*c->t.m[10]-c->t.m[9]*c->t.m[2]*c->t.m[7]+c->t.m[9]*c->t.m[3]*c->t.m[6];
		float z=-c->t.m[0]*c->t.m[5]*c->t.m[11]+c->t.m[0]*c->t.m[7]*c->t.m[9]+c->t.m[4]*c->t.m[1]*c->t.m[11]-c->t.m[4]*c->t.m[3]*c->t.m[9]-c->t.m[8]*c->t.m[1]*c->t.m[7]+c->t.m[8]*c->t.m[3]*c->t.m[5];
		float d=1/(c->t.m[0]*(c->t.m[5]*c->t.m[10]*c->t.m[15]-c->t.m[5]*c->t.m[11]*c->t.m[14]-c->t.m[9]*c->t.m[6]*c->t.m[15]+c->t.m[9]*c->t.m[7]*c->t.m[14]+c->t.m[13]*c->t.m[6]*c->t.m[11]-c->t.m[13]*c->t.m[7]*c->t.m[10])+c->t.m[1]*(-c->t.m[4]*c->t.m[10]*c->t.m[15]+c->t.m[4]*c->t.m[11]*c->t.m[14]+c->t.m[8]*c->t.m[6]*c->t.m[15]-c->t.m[8]*c->t.m[7]*c->t.m[14]-c->t.m[12]*c->t.m[6]*c->t.m[11]+c->t.m[12]*c->t.m[7]*c->t.m[10])+c->t.m[2]*(c->t.m[4]*c->t.m[9]*c->t.m[15]-c->t.m[4]*c->t.m[11]*c->t.m[13]-c->t.m[8]*c->t.m[5]*c->t.m[15]+c->t.m[8]*c->t.m[7]*c->t.m[13]+c->t.m[12]*c->t.m[5]*c->t.m[11]-c->t.m[12]*c->t.m[7]*c->t.m[9])+c->t.m[3]*(-c->t.m[4]*c->t.m[9]*c->t.m[14]+c->t.m[4]*c->t.m[10]*c->t.m[13]+c->t.m[8]*c->t.m[5]*c->t.m[14]-c->t.m[8]*c->t.m[6]*c->t.m[13]-c->t.m[12]*c->t.m[5]*c->t.m[10]+c->t.m[12]*c->t.m[6]*c->t.m[9]));
		float nx=sinf(o->t.ry);
		float nz=cosf(o->t.ry);
		if ((x*d-o->t.x)*nx+(z*d-o->t.z)*nz>0){
			return;
		}
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fba.id[lvl]);
		glViewport(0,0,FRAME_BUFFER_SIZE,FRAME_BUFFER_SIZE);
		float dd=0.1f;
		float tmp[4]={o->t.x-nx*dd,o->t.y,o->t.z-nz*dd,1};
		float c_pos[4];
		mult_vector(c->t.m,tmp,c_pos);
		tmp[0]=-nx;
		tmp[1]=0;
		tmp[2]=-nz;
		tmp[3]=0;
		float c_norm[4];
		mult_vector(c->t.m,tmp,c_norm);
		c_norm[3]=-c_pos[0]*c_norm[0]-c_pos[1]*c_norm[1]-c_pos[2]*c_norm[2];
		float pm_inv[16];
		inv_matrix(c->pm,pm_inv);
		tmp[0]=(c_norm[0]>0?-1.0f:1);
		tmp[1]=(c_norm[1]>0?-1.0f:1);
		tmp[2]=1;
		tmp[3]=1;
		float tmp2[4];
		mult_vector(pm_inv,tmp,tmp2);
		d=2/(tmp2[0]*c_norm[0]+tmp2[1]*c_norm[1]+tmp2[2]*c_norm[2]+tmp2[3]*c_norm[3]);
		camera_t nc=*c;
		nc.pm[8]=c_norm[0]*d-c->pm[12];
		nc.pm[9]=c_norm[1]*d-c->pm[13];
		nc.pm[10]=c_norm[2]*d-c->pm[14];
		nc.pm[11]=c_norm[3]*d-c->pm[15];
		resize_camera(&nc,FRAME_BUFFER_SIZE,FRAME_BUFFER_SIZE);
		recalculate_transform(&(nc.t));
		draw_recursive(&nc,lvl+1);
		use_camera(c);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,(!lvl?0:fba.id[lvl-1]));
		glBindTexture(GL_TEXTURE_2D,fba.tx[lvl]);
	}
	else{
		use_texture(&error_texture);
	}
	draw_object(&portal,c);
}



static void draw_recursive(camera_t* c,unsigned int lvl){
	use_camera(c);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthMask(GL_FALSE);
	use_shader(&sky_shader);
	float mv_i[16];
	inv_matrix(c->t.m,mv_i);
	float mvp_i[16];
	inv_matrix(c->pm,mvp_i);
	set_shader_global(&sky_shader,mv_i,mvp_i,0);
	glBindVertexArray(sky._va);
	glDrawArrays(GL_TRIANGLES,0,sky._vl);
	glDepthMask(GL_TRUE);
	draw_object(&cube,c);
	draw_object(&ground,c);
	draw_portal(&portal,c,lvl);
}



static void draw(void){
	draw_recursive(&cam,0);
}



static void deinit(void){
	glDeleteFramebuffersEXT(FRAME_BUFFER_COUNT,fba.id);
	glDeleteTextures(FRAME_BUFFER_COUNT,fba.tx);
	glDeleteRenderbuffersEXT(FRAME_BUFFER_COUNT,fba.r_bf);
	free_object(&cube);
	free_object(&ground);
	free_object(&portal);
	free_object(&sky);
	free_shader(&tex_shader);
	free_shader(&portal_shader);
	free_shader(&sky_shader);
	free_texture(&error_texture);
	free_texture(&texture);
}



int main(int argc,const char** argv){
	run(init,update,resize,draw,deinit);
	return 0;
}
