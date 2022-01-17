#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__ 1



typedef struct __TRANSFORM{
	float x;
	float y;
	float z;
	float rx;
	float ry;
	float rz;
	float sx;
	float sy;
	float sz;
	float m[16];
} transform_t;



void inv_matrix(const float* m,float* o);



void mult_matrix(const float* a,const float* b,float* o);



void mult_vector(const float* m,const float* v,float* o);



void recalculate_transform(transform_t* t);



void zero_transform(transform_t* t);



#endif
