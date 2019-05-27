#if !defined(OPENGL4DEVICECONTROLLER_H)
#define OPENGL4DEVICECONTROLLER_H

#include "../Application/GlobalsOGL46.h"


enum CustomRenderSettings
{
	customRenderSettingsUniversal,
	customRenderSettingsMenuUI,
	customRenderSettingsGameUI,
	customRenderSettingsGame3d,
	customRenderSettingsCount
};


class OpenGL4DeviceController
{

public:
	OpenGL4DeviceController();
	virtual ~OpenGL4DeviceController();

	void SetRenderSettings(CustomRenderSettings settings);


private:

};

#endif
