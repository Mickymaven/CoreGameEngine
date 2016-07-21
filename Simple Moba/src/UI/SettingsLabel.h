#if !defined(SETTINGSLABEL_H)
#define SETTINGSLABEL_H

#include "../../../EngineGameModuleDirectX9/src/UI/UILabel.h"

class SettingsLabel : public UILabel
{
private:

public:
	SettingsLabel();
	~SettingsLabel();
	bool Init(const RECT & rect, FontGroup * fontGroup, string * text);
	void Render();
};

#endif