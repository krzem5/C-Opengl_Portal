#ifndef _MSC_VER
#error Currently only Windows is supported
#endif
#include <windows.h>
#include <opengl.h>
#include <camera.h>
#include <input.h>
#include <object.h>
#include <texture.h>
#include <shader.h>
#include <transform.h>
#include <signal.h>
#include <stdio.h>



#define ASSERT(x) \
	do{ \
		if (!(x)){ \
			printf("%s:%i (%s): %s: Assertion Failed\n",__FILE__,__LINE__,__func__,#x); \
			raise(SIGABRT); \
		} \
	} while (0)

#define WIDTH 1920
#define HEIGHT 1080

#define HID_USAGE_PAGE_GENERIC 1
#define HID_USAGE_GENERIC_MOUSE 2



static HWND _hwnd;
static HDC _hdc;
static HGLRC _hrc;
static char _focus=0;
static void (*_resize)(unsigned int,unsigned int);



static LRESULT WINAPI _wnd_proc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp){
	switch (msg){
		case WM_PAINT:
			PAINTSTRUCT ps;
			BeginPaint(hwnd,&ps);
			EndPaint(hwnd,&ps);
			return 0;
		case WM_SIZE:
			_resize(LOWORD(lp),HIWORD(lp));
			PostMessage(hwnd,WM_PAINT,0,0);
			return 0;
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			if (wp&0x40000000){
				return 0;
			}
			inp_dt->k[(wp>>6)&3]|=1ull<<(wp&63);
		    inp_dt->kp[(wp>>6)&3]|=1ull<<(wp&63);
			if (wp==VK_ESCAPE){
				PostQuitMessage(0);
			}
			return 0;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			inp_dt->k[(wp>>6)&3]&=~(1ull<<(wp&63));
			return 0;
		case WM_INPUT:
			{
				RAWINPUT dt;
				UINT sz=sizeof(RAWINPUT);
				GetRawInputData((HRAWINPUT)lp,RID_INPUT,&dt,&sz,sizeof(RAWINPUTHEADER));
				if (dt.header.dwType==RIM_TYPEMOUSE){
					if (dt.data.mouse.usFlags==MOUSE_MOVE_RELATIVE){
						inp_dt->m_ddx+=dt.data.mouse.lLastX;
						inp_dt->m_ddy+=dt.data.mouse.lLastY;
					}
					if (dt.data.mouse.usButtonFlags&RI_MOUSE_LEFT_BUTTON_DOWN){
						inp_dt->m_btn|=BUTTON_LEFT|BUTTON_LEFT_PRESS;
					}
					if (dt.data.mouse.usButtonFlags&RI_MOUSE_MIDDLE_BUTTON_DOWN){
						inp_dt->m_btn|=BUTTON_MIDDLE|BUTTON_MIDDLE_PRESS;
					}
					if (dt.data.mouse.usButtonFlags&RI_MOUSE_RIGHT_BUTTON_DOWN){
						inp_dt->m_btn|=BUTTON_RIGHT|BUTTON_RIGHT_PRESS;
					}
					if (dt.data.mouse.usButtonFlags&RI_MOUSE_LEFT_BUTTON_UP){
						inp_dt->m_btn&=~(BUTTON_LEFT|BUTTON_LEFT_PRESS);
					}
					if (dt.data.mouse.usButtonFlags&RI_MOUSE_MIDDLE_BUTTON_UP){
						inp_dt->m_btn&=~(BUTTON_MIDDLE|BUTTON_MIDDLE_PRESS);
					}
					if (dt.data.mouse.usButtonFlags&RI_MOUSE_RIGHT_BUTTON_UP){
						inp_dt->m_btn&=~(BUTTON_RIGHT|BUTTON_RIGHT_PRESS);
					}
				}
				return 0;
			}
		case WM_SETFOCUS:
			_focus=1;
			return 0;
		case WM_KILLFOCUS:
			_focus=0;
			return 0;
	}
	return DefWindowProc(hwnd,msg,wp,lp);
}



void run(void(*init)(void),void(*update)(void),void (*resize)(unsigned int,unsigned int),void(*draw)(void),void(*deinit)(void)){
	_resize=resize;
	SetProcessDPIAware();
	WNDCLASSEXA wc={
		sizeof(WNDCLASSEXA),
		CS_OWNDC,
		_wnd_proc,
		0,
		0,
		GetModuleHandle(NULL),
		LoadIconA(NULL,IDI_APPLICATION),
		LoadCursorA(NULL,IDC_ARROW),
		NULL,
		NULL,
		"opengl-portal-class",
		NULL
	};
	ASSERT(RegisterClassExA(&wc));
	HWND _hwnd=CreateWindowExA(WS_EX_APPWINDOW|WS_EX_WINDOWEDGE,"opengl-portal-class","OpenGL Portal Example",WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,0,0,WIDTH,HEIGHT,NULL,NULL,GetModuleHandle(NULL),NULL);
	ASSERT(_hwnd);
	_hdc=GetDC(_hwnd);
	PIXELFORMATDESCRIPTOR pfd={
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,
		0,
		0
	};
	int pf=ChoosePixelFormat(_hdc,&pfd);
	ASSERT(pf);
	ASSERT(SetPixelFormat(_hdc,pf,&pfd));
	DescribePixelFormat(_hdc,pf,sizeof(PIXELFORMATDESCRIPTOR),&pfd);
	_hrc=wglCreateContext(_hdc);
	wglMakeCurrent(_hdc,_hrc);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	init_gl();
	GLint occ;
	glGetQueryiv(GL_SAMPLES_PASSED_ARB,GL_QUERY_COUNTER_BITS_ARB,&occ);
	ASSERT(occ);
	wglSwapIntervalEXT(1);
	init();
	resize(WIDTH,HEIGHT);
	RAWINPUTDEVICE r_in_dt={
		HID_USAGE_PAGE_GENERIC,
		HID_USAGE_GENERIC_MOUSE,
		RIDEV_INPUTSINK,
		_hwnd
	};
	RegisterRawInputDevices(&r_in_dt,1,sizeof(RAWINPUTDEVICE));
	ShowCursor(FALSE);
	ShowWindow(_hwnd,SW_SHOW);
	SetForegroundWindow(_hwnd);
	SetFocus(_hwnd);
	MSG msg;
	while (1){
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
			if (msg.message==WM_QUIT){
				break;
			}
			else{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else{
			if (_focus){
				RECT wr;
				GetWindowRect(_hwnd,&wr);
				SetCursorPos((wr.right+wr.left)/2,(wr.top+wr.bottom)/2);
			}
			update();
			end_input_data();
			draw();
			SwapBuffers(_hdc);
		}
	}
	deinit();
	ClipCursor(NULL);
	wglMakeCurrent(NULL,NULL);
	ReleaseDC(_hwnd,_hdc);
	wglDeleteContext(_hrc);
	DestroyWindow(_hwnd);
}
