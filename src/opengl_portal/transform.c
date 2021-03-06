#include <transform.h>
#include <math.h>
#include <string.h>



void inv_matrix(const float* m,float* o){
	o[0]=m[5]*m[10]*m[15]-m[5]*m[11]*m[14]-m[9]*m[6]*m[15]+m[9]*m[7]*m[14]+m[13]*m[6]*m[11]-m[13]*m[7]*m[10];
	o[1]=-m[1]*m[10]*m[15]+m[1]*m[11]*m[14]+m[9]*m[2]*m[15]-m[9]*m[3]*m[14]-m[13]*m[2]*m[11]+m[13]*m[3]*m[10];
	o[2]=m[1]*m[6]*m[15]-m[1]*m[7]*m[14]-m[5]*m[2]*m[15]+m[5]*m[3]*m[14]+m[13]*m[2]*m[7]-m[13]*m[3]*m[6];
	o[3]=-m[1]*m[6]*m[11]+m[1]*m[7]*m[10]+m[5]*m[2]*m[11]-m[5]*m[3]*m[10]-m[9]*m[2]*m[7]+m[9]*m[3]*m[6];
	o[4]=-m[4]*m[10]*m[15]+m[4]*m[11]*m[14]+m[8]*m[6]*m[15]-m[8]*m[7]*m[14]-m[12]*m[6]*m[11]+m[12]*m[7]*m[10];
	o[5]=m[0]*m[10]*m[15]-m[0]*m[11]*m[14]-m[8]*m[2]*m[15]+m[8]*m[3]*m[14]+m[12]*m[2]*m[11]-m[12]*m[3]*m[10];
	o[6]=-m[0]*m[6]*m[15]+m[0]*m[7]*m[14]+m[4]*m[2]*m[15]-m[4]*m[3]*m[14]-m[12]*m[2]*m[7]+m[12]*m[3]*m[6];
	o[7]=m[0]*m[6]*m[11]-m[0]*m[7]*m[10]-m[4]*m[2]*m[11]+m[4]*m[3]*m[10]+m[8]*m[2]*m[7]-m[8]*m[3]*m[6];
	o[8]=m[4]*m[9]*m[15]-m[4]*m[11]*m[13]-m[8]*m[5]*m[15]+m[8]*m[7]*m[13]+m[12]*m[5]*m[11]-m[12]*m[7]*m[9];
	o[9]=-m[0]*m[9]*m[15]+m[0]*m[11]*m[13]+m[8]*m[1]*m[15]-m[8]*m[3]*m[13]-m[12]*m[1]*m[11]+m[12]*m[3]*m[9];
	o[10]=m[0]*m[5]*m[15]-m[0]*m[7]*m[13]-m[4]*m[1]*m[15]+m[4]*m[3]*m[13]+m[12]*m[1]*m[7]-m[12]*m[3]*m[5];
	o[11]=-m[0]*m[5]*m[11]+m[0]*m[7]*m[9]+m[4]*m[1]*m[11]-m[4]*m[3]*m[9]-m[8]*m[1]*m[7]+m[8]*m[3]*m[5];
	o[12]=-m[4]*m[9]*m[14]+m[4]*m[10]*m[13]+m[8]*m[5]*m[14]-m[8]*m[6]*m[13]-m[12]*m[5]*m[10]+m[12]*m[6]*m[9];
	o[13]=m[0]*m[9]*m[14]-m[0]*m[10]*m[13]-m[8]*m[1]*m[14]+m[8]*m[2]*m[13]+m[12]*m[1]*m[10]-m[12]*m[2]*m[9];
	o[14]=-m[0]*m[5]*m[14]+m[0]*m[6]*m[13]+m[4]*m[1]*m[14]-m[4]*m[2]*m[13]-m[12]*m[1]*m[6]+m[12]*m[2]*m[5];
	o[15]=m[0]*m[5]*m[10]-m[0]*m[6]*m[9]-m[4]*m[1]*m[10]+m[4]*m[2]*m[9]+m[8]*m[1]*m[6]-m[8]*m[2]*m[5];
	float d=1/(m[0]*o[0]+m[1]*o[4]+m[2]*o[8]+m[3]*o[12]);
	o[0]*=d;
	o[1]*=d;
	o[2]*=d;
	o[3]*=d;
	o[4]*=d;
	o[5]*=d;
	o[6]*=d;
	o[7]*=d;
	o[8]*=d;
	o[9]*=d;
	o[10]*=d;
	o[11]*=d;
	o[12]*=d;
	o[13]*=d;
	o[14]*=d;
	o[15]*=d;
}



void mult_matrix(const float* a,const float* b,float* o){
	o[0]=a[0]*b[0]+a[1]*b[4]+a[2]*b[8]+a[3]*b[12];
	o[1]=a[0]*b[1]+a[1]*b[5]+a[2]*b[9]+a[3]*b[13];
	o[2]=a[0]*b[2]+a[1]*b[6]+a[2]*b[10]+a[3]*b[14];
	o[3]=a[0]*b[3]+a[1]*b[7]+a[2]*b[11]+a[3]*b[15];
	o[4]=a[4]*b[0]+a[5]*b[4]+a[6]*b[8]+a[7]*b[12];
	o[5]=a[4]*b[1]+a[5]*b[5]+a[6]*b[9]+a[7]*b[13];
	o[6]=a[4]*b[2]+a[5]*b[6]+a[6]*b[10]+a[7]*b[14];
	o[7]=a[4]*b[3]+a[5]*b[7]+a[6]*b[11]+a[7]*b[15];
	o[8]=a[8]*b[0]+a[9]*b[4]+a[10]*b[8]+a[11]*b[12];
	o[9]=a[8]*b[1]+a[9]*b[5]+a[10]*b[9]+a[11]*b[13];
	o[10]=a[8]*b[2]+a[9]*b[6]+a[10]*b[10]+a[11]*b[14];
	o[11]=a[8]*b[3]+a[9]*b[7]+a[10]*b[11]+a[11]*b[15];
	o[12]=a[12]*b[0]+a[13]*b[4]+a[14]*b[8]+a[15]*b[12];
	o[13]=a[12]*b[1]+a[13]*b[5]+a[14]*b[9]+a[15]*b[13];
	o[14]=a[12]*b[2]+a[13]*b[6]+a[14]*b[10]+a[15]*b[14];
	o[15]=a[12]*b[3]+a[13]*b[7]+a[14]*b[11]+a[15]*b[15];
}



void mult_vector(const float* m,const float* v,float* o){
	o[0]=v[0]*m[0]+v[1]*m[1]+v[2]*m[2]+v[3]*m[3];
	o[1]=v[0]*m[4]+v[1]*m[5]+v[2]*m[6]+v[3]*m[7];
	o[2]=v[0]*m[8]+v[1]*m[9]+v[2]*m[10]+v[3]*m[11];
	o[3]=v[0]*m[12]+v[1]*m[13]+v[2]*m[14]+v[3]*m[15];
}



void recalculate_transform(transform_t* t){
	if (!t->sx&&!t->sy&&!t->sz){
		float sa=sinf(t->rx);
		float ca=cosf(t->rx);
		float sb=sinf(t->ry);
		float cb=cosf(t->ry);
		float rm_x[16]={1,0,0,0,0,ca,-sa,0,0,sa,ca,0,0,0,0,1};
		float rm_y[16]={cb,0,sb,0,0,1,0,0,-sb,0,cb,0,0,0,0,1};
		float tm[16]={1,0,0,-t->x,0,1,0,-t->y,0,0,1,-t->z,0,0,0,1};
		float tmp[16];
		mult_matrix(rm_x,rm_y,tmp);
		mult_matrix(tmp,tm,t->m);
	}
	else{
		float sm[16]={t->sx,0,0,0,0,t->sy,0,0,0,0,t->sz,0,0,0,0,1};
		float sa=sinf(t->rx);
		float ca=cosf(t->rx);
		float sb=sinf(t->ry);
		float cb=cosf(t->ry);
		float sc=sinf(t->rz);
		float cc=cosf(t->rz);
		float rm[16]={cb*cc,sa*sb*cc-ca*sc,ca*sb*cc+sa*sc,0,cb*sc,sa*sb*sc+ca*cc,ca*sb*sc-sa*cc,0,-sb,sa*cb,ca*cb,0,0,0,0,1};
		float tm[16]={1,0,0,t->x,0,1,0,t->y,0,0,1,t->z,0,0,0,1};
		float tmp[16];
		mult_matrix(rm,sm,tmp);
		mult_matrix(tm,tmp,t->m);
	}
}



void zero_transform(transform_t* t){
	memset(t,0,sizeof(transform_t));
	t->sx=1;
	t->sy=1;
	t->sz=1;
	t->m[0]=1;
	t->m[5]=1;
	t->m[10]=1;
	t->m[15]=1;
}
