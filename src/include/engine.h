#ifndef __ENGINE_H__
#define __ENGINE_H__ 1



void run(void(*init)(void),void(*update)(void),void (*resize)(unsigned int,unsigned int),void(*draw)(void),void(*deinit)(void));



#endif
