#if !defined(GLOBALS_H)
#define GLOBALS_H

//the purpose of this class is to expose client and direct x variables to controllers in the client in an easy way.

//todo move main out probs
//mainly direct x

#include <windows.h>
#include<d3d9.h>
#include<d3dx9.h>


#ifdef DEBUG
#define DEBUG_IF(cond) if(cond)
#else
#define DEBUG_IF(cond) if(false)
#endif

//Globals

extern int g_windowPositionX;
extern int g_windowPositionY;

extern int g_windowWidth;
extern int g_windowHeight;

//desired clientsize
extern int g_initWidth;
extern int g_initHeight;

extern LPRECT g_windowSizeRect;
extern LPRECT g_clientSizeRect;

extern WNDCLASSEX g_windowClass;
extern MSG g_msg;
extern HWND g_hwnd;

extern LPDIRECT3D9 g_D3D_Object; //direct x object
extern LPDIRECT3DDEVICE9 g_D3D_Device;//direct x device

extern D3DDISPLAYMODE g_DisplayMode;//allows us to set screens display mode
extern D3DPRESENT_PARAMETERS g_Present_Parameters; //parameters of screen
extern D3DCAPS9 g_D3DCaps;//hardware capabilities

extern bool isStartFullscreen;
extern bool g_isFocus;

extern POINT g_mouseClientPosition;

extern void UpdateMouseClientPosition();

extern POINT * GetMouseClientPosition();

#endif
