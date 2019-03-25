#define WIN32_LEAN_AND_MEAN
#define VC_LEANMEAN
//#define WIN32_EXTRA_LEAN //for mfc projects only
//#define VC_EXTRALEAN //probably for mfc projects
#include <windows.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#include <d3d9.h>
#include <d3dx9.h>

#include "Main.h"//first
#include "App.h"//2nd
#include "../../../EngineGameModuleDirectX9/src/Application/Globals.h"//3rd
#include "../../../EngineGameModuleDirectX9/src/ControlHeader.h"

#include "../../../EngineGameModuleOpenGL46/src/Application/Globals.h"//3rd
#include "../../../EngineGameModuleOpenGL46/src/ControlHeader.h"

#include "../GameControl/GameController.h"

#include "MenuController.h"
MenuController g_menuController;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	isStartFullscreen = false;
	g_initWidth = 1440;
	g_initHeight = 900;
	g_clientSizeRect->right = g_initWidth;
	g_clientSizeRect->bottom = g_initHeight;


	Main app;
	g_app = &app;
	g_hInstance = hInstance;

	if (FAILED(app.Create(hInstance))) return 0;

	return app.Run();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int width, height;


	switch (message)
	{
	case WM_KEYUP://OutputDebugString("WM_KEYUP\n");
				  /*
				  switch (wParam)
				  {

				  case VK_ESCAPE:// Close the app if the user presses escape.
				  PostQuitMessage(0);
				  break;
				  }
				  */
		break;
	case WM_SIZE://OutputDebugString("WM_SIZE\n");
				 // re-size message.
		height = HIWORD(lParam);         // This gets the height of the window.
		width = LOWORD(lParam);          // This gets the width of the window.

		if (height == 0)                    // we don't want it to be possible for a
		{                             // height of 0.  If it is 0 me make it 1.
			height = 1;
		}

		g_windowWidth = width;
		g_windowHeight = height;

		return 0;
		break;

	case WM_CLOSE://OutputDebugString("WM_CLOSE\n");
		PostQuitMessage(0);
		break;
	case WM_DESTROY://OutputDebugString("WM_DESTROY\n");
		PostQuitMessage(0);
		break;
	case WM_ACTIVATE:
		//if (g_D3D_Device!=NULL) g_D3D_Device->Reset(&g_Present_Parameters);
		g_isFocus = true;

		/*
		SetCapture(g_hwnd);

		GetWindowRect(g_hwnd, g_windowSizeRect);


		ClipCursor(g_windowSizeRect);
		SetCursorPos(((g_windowSizeRect->left + g_windowSizeRect->right) / 2),
		((g_windowSizeRect->top + g_windowSizeRect->bottom) / 2));

		*/

		break;


		/*
		case WM_NULL:OutputDebugString("WM_NULL\n"); break;
		case WM_CREATE:OutputDebugString("WM_CREATE\n"); break;

		case WM_MOVE:OutputDebugString(" WM_MOVE\n"); break;



		case WM_SETFOCUS:OutputDebugString(" WM_SETFOCUS\n"); break;
		*/
	case WM_KILLFOCUS:OutputDebugString("WM_KILLFOCUS \n");
		g_isFocus = false;

		break;
		/*
		case WM_ENABLE:OutputDebugString(" WM_ENABLE\n"); break;
		case WM_SETREDRAW:OutputDebugString(" WM_SETREDRAW\n"); break;
		case WM_SETTEXT:OutputDebugString(" WM_SETTEXT\n"); break;
		case WM_GETTEXT:OutputDebugString(" WM_GETTEXT\n"); break;
		case WM_GETTEXTLENGTH:OutputDebugString("WM_GETTEXTLENGTH \n"); break;
		case WM_PAINT:OutputDebugString(" WM_PAINT\n"); break;


		case WM_QUERYENDSESSION:OutputDebugString("WM_QUERYENDSESSION \n"); break;
		case WM_QUERYOPEN:OutputDebugString("WM_QUERYOPEN \n"); break;
		case WM_ENDSESSION:OutputDebugString(" WM_ENDSESSION\n"); break;


		case WM_QUIT:OutputDebugString("WM_QUIT \n"); break;
		case WM_ERASEBKGND:OutputDebugString(" WM_ERASEBKGND\n"); break;
		case WM_SYSCOLORCHANGE:OutputDebugString("WM_SYSCOLORCHANGE \n"); break;
		case WM_SHOWWINDOW:OutputDebugString(" WM_SHOWWINDOW\n"); break;

		case WM_WININICHANGE:OutputDebugString(" WM_WININICHANGE\n"); break;


		case WM_DEVMODECHANGE:OutputDebugString("WM_DEVMODECHANGE \n"); break;
		case WM_ACTIVATEAPP:OutputDebugString(" WM_ACTIVATEAPP\n"); break;
		case WM_FONTCHANGE:OutputDebugString("WM_FONTCHANGE \n"); break;
		case WM_TIMECHANGE:OutputDebugString("WM_TIMECHANGE \n"); break;
		case WM_CANCELMODE:OutputDebugString("WM_CANCELMODE \n"); break;
		//case WM_SETCURSOR:OutputDebugString("WM_SETCURSOR \n"); break;
		case WM_MOUSEACTIVATE:OutputDebugString("WM_MOUSEACTIVATE \n"); break;
		case WM_CHILDACTIVATE:OutputDebugString(" WM_CHILDACTIVATE\n"); break;
		case WM_QUEUESYNC:OutputDebugString("WM_QUEUESYNC \n"); break;
		case WM_GETMINMAXINFO:OutputDebugString("WM_GETMINMAXINFO \n"); break;
		*/
	default:
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


HRESULT Main::Create(HINSTANCE hInstance)
{
	//HRESULT x;

	if (!InitWindowClass())		return false;
	if (!InitWindow())			return false;
	if (!InitDirectX())			return false;
	if (!InitDeviceController()) return false;
	if (!InitInputController())	return false;
	if (!InitMenuController())	return false;

	return S_OK;
}

INT Main::Run()
{
	bool done = false;
	g_msg.wParam = NULL;

	if (PeekMessage(&g_msg, NULL, NULL, NULL, PM_REMOVE))
	{
		if (g_msg.message == WM_QUIT)
		{
			done = true;
		}
		TranslateMessage(&g_msg);
		DispatchMessage(&g_msg);
	}

	//if (!g_isFocus) Sleep(1000.0f);

	//SetWindowPos(g_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	while (!done)
	{
		if (g_menuController.Run() == menuTargetGame)
		{
			GameController gameController;// = GameController();//rinse and repeat scope
			GameConfiguration * pGameConfig = g_menuController.GetGameConfig();

			if (pGameConfig != NULL)
			{
				if (!gameController.Run(pGameConfig))//todo int used as bool here(enum for codes maybe)
				{
					done = true;
					OutputDebugString("game controller returned false\n");
				}
				gameController.Shutdown();
			}

			g_menuController.Reset();
		}
		else { done = true; break; }//maybe menus (however many we implement in this app) targets end up in credit screen etc or others.
	}

	return (INT)g_msg.wParam;
}

bool Main::InitWindowClass()
{
	g_windowClass.cbSize = sizeof(WNDCLASSEX);           // size of the WNDCLASSEX structure.
	g_windowClass.style = CS_HREDRAW | CS_VREDRAW;       // style of the window.
	g_windowClass.lpfnWndProc = WndProc;                 // Address to the windows procedure.
	g_windowClass.cbClsExtra = 0;                        // Extra class information.
	g_windowClass.cbWndExtra = 0;                        // Extra window information.
	g_windowClass.hInstance = g_hInstance;                 // Handle of application Instance.
	g_windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);// Window Icon.
	g_windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Load mouse cursor.
	if (!isStartFullscreen) g_windowClass.hbrBackground = NULL;                  // Background color.
	g_windowClass.lpszMenuName = NULL;                   // Menu.
	g_windowClass.lpszClassName = "MyClass";            // Name of the window class.
	g_windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);// Minimized window icon.

	if (!RegisterClassEx(&g_windowClass)) return false;

	AdjustWindowRect(g_clientSizeRect, WS_OVERLAPPEDWINDOW, FALSE);

	return true;
}

Main::Main()
{
}

Main::~Main()
{
}

bool Main::InitWindow()
{
	// Create the window.
	

	if (isStartFullscreen)
	{
		g_hwnd = CreateWindowEx(NULL,                       // The extended style.
			"MyClass",										// Window class.
			"Simple Moba on twitch.tv/mickymaven",			// Window name.
			WS_EX_TOPMOST | WS_POPUP,
			0, 0,			// X, Y coords.
			g_clientSizeRect->right - g_clientSizeRect->left,   // Window size X.
			g_clientSizeRect->bottom - g_clientSizeRect->top,   // Window size Y.
			NULL,											// Handle to parent window.
			NULL,											// Menu.
			g_hInstance,									// Handle to app instance.
			NULL);											// Pointer to window.
	}

	else
	{
		g_hwnd = CreateWindowEx(NULL,                       // The extended style.
			"MyClass",										// Window class.
			"Simple Moba on twitch.tv/mickymaven",			// Window name.
			WS_OVERLAPPED | WS_MINIMIZEBOX | WS_VISIBLE |   // Window style.
			WS_SYSMENU | WS_CLIPCHILDREN |
			WS_CLIPSIBLINGS,
			g_windowPositionX, g_windowPositionY,
			g_clientSizeRect->right - g_clientSizeRect->left,   // Window size X.
			g_clientSizeRect->bottom - g_clientSizeRect->top,   // Window size Y.
			NULL,											// Handle to parent window.
			NULL,											// Menu.
			g_hInstance,									// Handle to app instance.
			NULL);											// Pointer to window.
	}





	// If there was an error with creating the window, then close the program.
	if (!g_hwnd) return false;

	ShowWindow(g_hwnd, SW_SHOW);    // Show the window.
	UpdateWindow(g_hwnd);           // Update its display.

									//GetWindowRect(g_hwnd, &)
									//GetClientRect(g_hwnd, &)




	char m_buffer[500];

	sprintf_s(m_buffer, "---------------\n ClientSizeRect AFTER AdjustWIndowRect: w%i h%i, \n--------------\n", g_clientSizeRect->right, g_clientSizeRect->bottom);
	OutputDebugString(m_buffer);

	GetClientRect(g_hwnd, g_clientSizeRect);

	sprintf_s(m_buffer, "---------------\n GetClientRect : w%i , h%i (back onto clientSizeRect) \n--------\n", g_clientSizeRect->right, g_clientSizeRect->bottom);
	OutputDebugString(m_buffer);



	return true;
}

bool Main::InitDirectX()
{



	g_D3D_Object = Direct3DCreate9(D3D_SDK_VERSION);//d3d9.h

	if (g_D3D_Object == NULL)
	{
		MessageBox(NULL, "Error, couldn't initialize DirectX!?!", "Error!", MB_OK);
		return false;
	}


	if (FAILED(g_D3D_Object->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &g_DisplayMode)))
	{
		MessageBox(NULL, "Error setting the display mode.", "Error!", MB_OK);
		return false;
	}

	if (FAILED(g_D3D_Object->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &g_D3DCaps)))
	{
		MessageBox(NULL, "Failed to get device capabilities.", "Error!", MB_OK);
		return false;
	}

	//If device can handle hardware vertex processing or not.
	DWORD VertexProcessing = 0;
	if (g_D3DCaps.VertexProcessingCaps != 0)
	{
		VertexProcessing |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else { VertexProcessing |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; }

	if (isStartFullscreen)
	{
		g_Present_Parameters.Windowed = FALSE;
		g_Present_Parameters.BackBufferWidth = 1280;//1680
		g_Present_Parameters.BackBufferHeight = 1024;//1050
	}
	else
	{
		g_Present_Parameters.Windowed = TRUE;
	}

	g_Present_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_Present_Parameters.BackBufferFormat = g_DisplayMode.Format;// Render to the area of the screen.
	g_Present_Parameters.BackBufferCount = 1; //Num of back buffers


											  //Detect What Depth Stencil Formats are supported.

	g_Present_Parameters.EnableAutoDepthStencil = TRUE;
	//g_Present_Parameters.AutoDepthStencilFormat = D3DFMT_D16;


	if (SUCCEEDED(g_D3D_Object->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_DisplayMode.Format,
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8))) {
		g_Present_Parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	}
	else if (SUCCEEDED(g_D3D_Object->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_DisplayMode.Format,
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8))) {
		g_Present_Parameters.AutoDepthStencilFormat = D3DFMT_D24X8;
	}
	else if (SUCCEEDED(g_D3D_Object->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_DisplayMode.Format,
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16))) {
		g_Present_Parameters.AutoDepthStencilFormat = D3DFMT_D16;
	}
	else {
		return false;
	}


	//g_D3DCaps.RasterCaps


	DWORD pQualityLevels;


	g_D3D_Object->CheckDeviceMultiSampleType(
		g_D3DCaps.AdapterOrdinal,
		g_D3DCaps.DeviceType,
		D3DFMT_X8R8G8B8,
		!isStartFullscreen,
		D3DMULTISAMPLE_4_SAMPLES,
		&pQualityLevels);




	char bufferX[1000];
	sprintf_s(bufferX, "\n\n\npQualityLevels: %i \n\n\n", pQualityLevels);
	OutputDebugString(bufferX);

	if (pQualityLevels >= 5)
	{
		g_Present_Parameters.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
		g_Present_Parameters.MultiSampleQuality = 0;
		OutputDebugString("We got a 4x Multisample");
	}

	g_Present_Parameters.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	g_Present_Parameters.MultiSampleQuality = 0;

	//D3DPRASTERCAPS_MULTISAMPLE_TOGGLE



	int adapterNo = D3DADAPTER_DEFAULT;
	if (isStartFullscreen) adapterNo = 0;

	if (FAILED(g_D3D_Object->CreateDevice(adapterNo, D3DDEVTYPE_HAL, g_hwnd,
		VertexProcessing, &g_Present_Parameters, &g_D3D_Device)))
	{
		MessageBox(NULL, "CreateDevice() failed!  Make sure you have DirectX 9", "Error!", MB_OK);
		return false;
	}


	return true;
}

bool Main::InitOpenGL()
{



	return false;
}

bool Main::InitDeviceController()
{
	return true;
}

bool Main::InitInputController()
{
	//g_inputControl = DirectInput8Controller();

	if (!g_inputControl.Init(g_hwnd, g_hInstance, false)) return false;

	return true;
}

bool Main::InitMenuController()
{
	//g_menuController = MenuController();
	if (!g_menuController.Init()) return false;
	g_menuController.SetMenu(menuIntro);

	return true;
}
