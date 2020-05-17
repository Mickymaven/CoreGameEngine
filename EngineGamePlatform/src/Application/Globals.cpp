#include "Globals.h"

//G_TARG_OPENGL
//G_TARG_DIRECTX

//GRAPHICSTARGET graphics_target = G_TARG_OPENGL;
GRAPHICSTARGET graphics_target = G_TARG_DIRECTX;


bool isStartFullscreen = false;
bool g_isFocus = true;

int g_windowPositionX = 0;//1680
int g_windowPositionY = 0;

int g_windowWidth = 0;
int g_windowHeight = 0;

//desired clientsize
int g_initWidth = 0;
int g_initHeight = 0;

int g_myScreenHeight = 0;
int g_myScreenWidth = 0;

LPRECT g_windowSizeRect = new RECT{ 0, 0, 0, 0 };
LPRECT g_clientSizeRect = new RECT{ 0, 0, g_initWidth, g_initHeight };

WNDCLASSEX g_windowClass;
MSG g_msg; // Message object.
HWND g_hwnd; // Handle to the window.

POINT g_mouseClientPosition;

unsigned long g_playerID = 0;

void UpdateMouseClientPosition()
{
	if (g_hwnd != NULL)
	{
		GetCursorPos(&g_mouseClientPosition);
		ScreenToClient(g_hwnd, &g_mouseClientPosition);
		//char buffer[100];
		//sprintf_s(buffer, "x %ld, y %d \n", g_mouseClientPosition.x, g_mouseClientPosition.y);
		//OutputDebugString(buffer);
	}
}

POINT * GetMouseClientPosition()
{
	return &g_mouseClientPosition;
}
