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



#include "Main.h"//1st
#include "App.h"//2nd


#include "../../../EngineGamePlatform/src/Application/Globals.h"//3rd


#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h"//4th

#include "../../../EngineGameModuleDirectX9/src/ControlHeader.h"

#include "../../../EngineGameModuleOpenGL46/src/Application/GlobalsOGL46.h"//4th
#include "../../../EngineGameModuleOpenGL46/src/ControlHeader.h"

#include "../GameControl/GameController.h"
#include "../GameControl/OpenGL46TestController.h"


#include "MenuController.h"
MenuController g_menuController;

#include "../../../EngineGameModuleOpenGL46/src/Device/OpenGL4Object.h"


Main::Main()
{
}

Main::~Main()
{
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	isStartFullscreen = false;
	g_initWidth = 1600;
	g_initHeight = 900;


	g_clientSizeRect->left = 0;
	g_clientSizeRect->top = 0;

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
		ApplicationHandle->MessageHandler(hwnd, message, wParam, lParam);

		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


HRESULT Main::Create(HINSTANCE hInstance)
{
	
	if (graphics_target == G_TARG_OPENGL)
	{
		OGLINIT();
		//InitWindowClass();
		//InitOpenGLExtensions();
		//InitWindow();
		/*
		if (!InitWindowClass()) return false;
		if (!InitOpenGLExtensions()) return false;
		if (!InitWindow()) return false;
		if (!InitOpenGL()) return false;
		if (!ShowMyWindow()) return false;
		
		*/

	}

	if (graphics_target == G_TARG_DIRECTX)
	{
		InitWindowClass();
		InitWindow();
		InitDirectX();
		//ShowMyWindow();
		InitDeviceController();
		InitInputController();
		InitMenuController();


		if (!InitWindowClass())		return false;
		if (!InitWindow())			return false;
		if (!InitDirectX()) return false;
		ShowMyWindow();
		if (!InitDeviceController()) return false;
		if (!InitInputController())	return false;
		if (!InitMenuController())	return false;

	}


	//HRESULT x;
	/*
	if (!InitWindowClass())		return false;
	if (graphics_target == G_TARG_OPENGL) { if (!InitOpenGLExtensions()) return false; }
	if (!InitWindow())			return false;

	if (graphics_target == G_TARG_DIRECTX) { if (!InitDirectX()) return false; }
	else if (graphics_target == G_TARG_OPENGL) { if (!InitOpenGL()) return false; }

	if (!ShowMyWindow()) return false;
	if (graphics_target == G_TARG_OPENGL) return S_OK;
	
	if (!InitDeviceController()) return false;
	if (!InitInputController())	return false;
	if (!InitMenuController())	return false;*/

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



	if (graphics_target == G_TARG_OPENGL)
	{
		OGLRUN();

		/*
		while (!done)
		{
		

			
			if (!m_Graphics->Run())//todo int used as bool here(enum for codes maybe)
			{
				done = true;
				OutputDebugString("game controller returned false\n");
			}
			
		}*/

		return (INT)g_msg.wParam;
	}

	else {
		while (!done)
		{
			if (g_menuController.Run() == menuTargetGame)
			{
				GameController gameController; //default constructor on stack, destruct within this scope.
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
	else {
		g_windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	}
	g_windowClass.lpszMenuName = NULL;                   // Menu.
	g_windowClass.lpszClassName = "MyClass";            // Name of the window class.
	g_windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);// Minimized window icon.

	if (!RegisterClassEx(&g_windowClass)) return false;

	if (graphics_target == G_TARG_DIRECTX) AdjustWindowRect(g_clientSizeRect, WS_OVERLAPPEDWINDOW, FALSE);

	return true;
}



bool Main::InitOpenGLExtensions()
{

	/*
	InitWindowClass()       DONE
	InitOpenGLExtensions()	
	InitWindow()
	InitOpenGL()
	InitDeviceController()
	InitInputController()
	*/


	/*
	A  WINCLASS
	B  FAKEWINDOW
	C  HIDE IT
	D  INIT EXTENSION
	E  DESTROY FAKE WIN
	F  DEVMODE
	G  CHANGEDISPLAYSETTINGS
	H  WINDOW POS CALC
	I  hwnd CREATEWINDOWEX
	J  INITOPENGL
	K  SHOW WINDOW
	*/

	/*
	====	INIT OPEN GL	===
	DEV CONTEXT
	PIXEL FORMAT
	ATTRS
	CONTEXT
	GLSTUFFS
	WGLSWAPINTERVALEXT
	
	*/

	g_myScreenHeight =0;
	g_myScreenWidth =0;

	//B FAKE WINDOW

	bool result;
	HWND h;
	h = 

		CreateWindowEx(NULL,                       // The extended style.
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
		NULL);

	if (h == NULL) return false;

	//C HIDE IT Don't show the window.
	ShowWindow(h, SW_HIDE);


	// D INIT EXTENTIONS
	// Initialize a temporary OpenGL window and load the OpenGL extensions.
	result = g_OpenGL4Object.InitializeExtensions(h);
	if (!result)
	{
		MessageBox(h, "Could not initialize the OpenGL extensions.", "Error", MB_OK);
		return false;
	}

	// Release the temporary window now that the extensions have been initialized.
	DestroyWindow(h);
	h = NULL;

	//FIX THE QUEUED MESSAGES EXIT THE WINDOW BUG
	bool messages=true;
	while (messages)
	{
		if (PeekMessage(&g_msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);

			messages = true;
		}
		else messages = false;
	}


	DEVMODE dmScreenSettings;
	int posX, posY;

	// Determine the resolution of the clients desktop screen.


	g_myScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	g_myScreenWidth = GetSystemMetrics(SM_CXSCREEN);

	g_initWidth = GetSystemMetrics(SM_CXSCREEN);
	g_initHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (isStartFullscreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)g_myScreenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)g_myScreenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.

		g_myScreenWidth = 800;
		g_myScreenHeight = 600;

		g_initWidth = g_myScreenWidth;
		g_initHeight = g_myScreenHeight;


		// Place the window in the middle of the screen.
		g_windowPositionX = (GetSystemMetrics(SM_CXSCREEN) - g_myScreenWidth) / 2;
		g_windowPositionY = (GetSystemMetrics(SM_CYSCREEN) - g_myScreenHeight) / 2;
	}



	return true;

}

bool Main::InitWindow()
{
	// Create the window.
	

	if (isStartFullscreen && graphics_target == G_TARG_DIRECTX)
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

	else if (graphics_target==G_TARG_DIRECTX)
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



		if (!g_hwnd) return false;

		ShowWindow(g_hwnd, SW_SHOW);    // Show the window.
		SetForegroundWindow(g_hwnd);
		UpdateWindow(g_hwnd);           // Update its display.

										//GetWindowRect(g_hwnd, &)
										//GetClientRect(g_hwnd, &)
		SetFocus(g_hwnd);

	}
	else
	{
		g_hwnd = CreateWindowEx(WS_EX_APPWINDOW,                       // The extended style.
			"MyClass",										// Window class.
			"Simple Moba on twitch.tv/mickymaven",			// Window name.
			WS_POPUP,
			g_windowPositionX,
			g_windowPositionY,
			g_myScreenWidth,   // Window size X.
			g_myScreenHeight,   // Window size Y.
			NULL,											// Handle to parent window.
			NULL,											// Menu.
			g_hInstance,									// Handle to app instance.
			NULL);
	}

	// If there was an error with creating the window, then close the program.
	if (g_hwnd==NULL) return false;


	



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
	bool result = g_OpenGL4Object.InitialiseOpenGL4Object(
		g_hwnd,
		g_clientSizeRect->right - g_clientSizeRect->left, //width
		g_clientSizeRect->bottom - g_clientSizeRect->top, //height
		g_SCREEN_DEPTH,//view depth
		g_SCREEN_NEAR,//view min
		g_VSYNC_ENABLED //vsync
	);


	if (!result)
	{
		MessageBox(g_hwnd, "Could not initialize OpenGL, check if video card supports OpenGL 4.0.", "Error", MB_OK);
		return false;
	}

	return true;
}

bool Main::ShowMyWindow()
{
	if (g_hwnd == NULL) return false;
	
	ShowWindow(g_hwnd, SW_SHOW);
	SetForegroundWindow(g_hwnd);
	SetFocus(g_hwnd);

	// Hide the mouse cursor.
	if (graphics_target == G_TARG_DIRECTX) ShowCursor(true);
	else if (graphics_target == G_TARG_OPENGL) ShowCursor(false);
	ShowCursor(false);

	return true;
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

bool Main::OGLINIT()
{
	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero.
	screenWidth = 0;
	screenHeight = 0;

	// Create the OpenGL object.
	g_OpenGL4Object = OpenGL4Object();

	m_OpenGL = &g_OpenGL4Object;
	if (!m_OpenGL)
	{
		return false;
	}

	// Create the window the application will be using and also initialize OpenGL.
	result = OGLINITWINDOWS(m_OpenGL, screenWidth, screenHeight);
	if (!result)
	{
		MessageBoxW(m_hwnd, L"Could not initialize the window.", L"Error", MB_OK);
		return false;
	}

	// Create the input object.  This object will be used to handle reading the input from the user.
	m_Input = new OpenGL4Input;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	m_Input->Initialize();

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new OpenGL46TestController;
	if (!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(m_OpenGL, m_hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}

void Main::OGLRUN()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	done = false;
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = OGLFRAME();
			if (!result)
			{
				done = true;
			}
		}

	}

	return;
}

void Main::OGLSHUT()
{
	// Release the graphics object.
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// Release the OpenGL object.
	if (m_OpenGL)
	{
		m_OpenGL->Shutdown(m_hwnd);
		delete m_OpenGL;
		m_OpenGL = 0;
	}

	// Shutdown the window.
	OGLSHUTDOWNWINDOWS();

	return;
}

bool Main::OGLFRAME()
{
	bool result;


	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// Do the frame processing for the graphics object.

	result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}

bool Main::OGLINITWINDOWS(OpenGL4Object *OpenGL, int & screenWidth, int & screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
	bool result;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = "Engine";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Create a temporary window for the OpenGL extension setup.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_POPUP,
		0, 0, 640, 480, NULL, NULL, m_hinstance, NULL);
	if (m_hwnd == NULL)
	{
		return false;
	}

	// Don't show the window.
	ShowWindow(m_hwnd, SW_HIDE);

	// Initialize a temporary OpenGL window and load the OpenGL extensions.
	result = OpenGL->InitializeExtensions(m_hwnd);
	if (!result)
	{
		MessageBoxW(m_hwnd, L"Could not initialize the OpenGL extensions.", L"Error", MB_OK);
		return false;
	}

	// Release the temporary window now that the extensions have been initialized.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;


	//FIX THE QUEUED MESSAGES EXIT THE WINDOW BUG
	bool messages = true;
	while (messages)
	{
		if (PeekMessage(&g_msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);

			messages = true;
		}
		else messages = false;
	}


	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);
	if (m_hwnd == NULL)
	{
		return false;
	}

	// Initialize OpenGL now that the window has been created.
	result = m_OpenGL->InitialiseOpenGL4Object(m_hwnd, screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);
	if (!result)
	{
		MessageBoxW(m_hwnd, L"Could not initialize OpenGL, check if video card supports OpenGL 4.0.", L"Error", MB_OK);
		return false;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return true;
}

void Main::OGLSHUTDOWNWINDOWS()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK Main::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:
	{
		// If a key is pressed send it to the input object so it can record that state.
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
	}

	// Check if a key has been released on the keyboard.
	case WM_KEYUP:
	{
		// If a key is released then send it to the input object so it can unset the state for that key.
		m_Input->KeyUp((unsigned int)wparam);
		return 0;
	}

	// Any other messages send to the default message handler as our application won't make use of them.
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}
