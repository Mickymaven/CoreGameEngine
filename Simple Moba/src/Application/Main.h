#if !defined(MAIN_H)
#define MAIN_H

#include <Windows.h>

class Main
{
public:
	Main();
	virtual ~Main();
	HRESULT Create(HINSTANCE hInstance);
	INT Run();
	bool InitWindowClass();
	bool InitWindow();
	bool InitDirectX();
	bool InitDeviceController();
	bool InitInputController();
	bool InitMenuController();

private:

};

#endif