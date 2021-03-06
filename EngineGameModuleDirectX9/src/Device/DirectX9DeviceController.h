#if !defined(DIRECTX9DEVICECONTROLLER_H)
#define DIRECTX9DEVICECONTROLLER_H


#include<d3d9.h>

#include "../Application/GlobalsDX9.h"

enum CustomRenderSettings
{
	customRenderSettingsUniversal,
	customRenderSettingsMenuUI,
	customRenderSettingsGameUI,
	customRenderSettingsGame3d,
	customRenderSettingsGameFX,
	customRenderSettingsCount
};


class DirectX9DeviceController
{

public:
	DirectX9DeviceController();
	virtual ~DirectX9DeviceController();

	void SetRenderSettings(CustomRenderSettings settings);
};

#endif
