#include <opengl.h>
#include <camera.h>
#include <engine.h>
#include <object.h>
#include <shader.h>
#include <texture.h>



static camera_t cam;
static object_t cube;
static object_t ground;
static object_t sky;
static shader_t tex_shader;
static shader_t sky_shader;
static texture_t texture;



static void init(void){
	glClearColor(0.65f,0.8f,0.95f,1.0f);
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
	const char* sky_vert="#version 330 core\n\
	uniform mat4 m;\n\
	uniform mat4 mvp;\n\
	layout(location=0) in vec3 pos;\n\
	out vec3 f_norm;\n\
	void main(void){\n\
		gl_Position=vec4(pos.xy,0.0,1.0);\n\
		f_norm=normalize((vec4(normalize((gl_Position*mvp).xyz),0.0)*m).xyz);\n\
	}";
	const char* sky_frag="#version 330 core\n\
	precision highp float;\n\
	#define LIGHT vec3(-0.36,0.80,-0.48)\n\
	#define SUN_SIZE 0.002\n\
	#define SUN_SHARPNESS 1.0\n\
	in vec3 f_norm;\n\
	out vec4 gl_FragColor;\n\
	void main(void){\n\
		vec3 n=normalize(f_norm);\n\
		float h=(1.0-n.y)*(1.0-n.y)*0.5;\n\
		vec3 sky=vec3(0.2+h,0.5+h,1.0);\n\
		float s=dot(n,LIGHT)-1.0+SUN_SIZE;\n\
		float sun=min(exp(s*SUN_SHARPNESS/SUN_SIZE),1.0);\n\
		gl_FragColor=vec4(max(sky,sun),1.0);\n\
	}";
	create_shader(&sky_shader,sky_vert,sky_frag);
	const uint8_t tex_dt[14]={
		255,255,255,128,128,128,
		0,0,
		128,128,128,255,255,255
	};
	create_texture(&texture,tex_dt,2,2);
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
}



static void update(void){
	cube.t.y=1;
	cube.t.rx+=0.02f;
	cube.t.rz+=0.03f;
	cube.t.sx=0.5f;
	cube.t.sy=0.5f;
	cube.t.sz=0.5f;
	recalculate_transform(&(cube.t));
	update_camera(&cam);
}



static void resize(unsigned int w,unsigned int h){
	resize_camera(&cam,w,h);
}



static void draw(void){
	use_camera(&cam);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthMask(GL_FALSE);
	use_shader(&sky_shader);
	float mv_i[16];
	inv_matrix(cam.t.m,mv_i);
	float mvp_i[16];
	inv_matrix(cam.pm,mvp_i);
	set_shader_global(&sky_shader,mv_i,mvp_i,0);
	glBindVertexArray(sky._va);
	glDrawArrays(GL_TRIANGLES,0,sky._vl);
	glDepthMask(GL_TRUE);
	draw_object(&cube,&cam);
	draw_object(&ground,&cam);
}



static void deinit(void){
	free_object(&cube);
	free_object(&ground);
	free_object(&sky);
	free_shader(&tex_shader);
	free_shader(&sky_shader);
	free_texture(&texture);
}



int main(int argc,const char** argv){
	run(init,update,resize,draw,deinit);
	return 0;
}
