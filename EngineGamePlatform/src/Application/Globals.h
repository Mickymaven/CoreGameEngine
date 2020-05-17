#if !defined(GLOBALS_H)
#define GLOBALS_H

#include <windows.h>


#ifdef DEBUG
#define DEBUG_IF(cond) if(cond)
#else
#define DEBUG_IF(cond) if(false)
#endif

//Globals

enum GRAPHICSTARGET { G_TARG_OPENGL, G_TARG_DIRECTX, G_TARG_COUNT };
extern GRAPHICSTARGET graphics_target;


extern int g_windowPositionX;
extern int g_windowPositionY;

extern int g_windowWidth;
extern int g_windowHeight;

//desired clientsize
extern int g_initWidth;
extern int g_initHeight;

extern LPRECT g_windowSizeRect;
extern LPRECT g_clientSizeRect;

extern int g_myScreenHeight;
extern int g_myScreenWidth;

extern WNDCLASSEX g_windowClass;
extern MSG g_msg;
extern HWND g_hwnd;

extern bool isStartFullscreen;
extern bool g_isFocus;

extern POINT g_mouseClientPosition;

extern void UpdateMouseClientPosition();

extern POINT * GetMouseClientPosition();

#endif
