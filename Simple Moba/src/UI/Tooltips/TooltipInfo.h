#if !defined(TOOLTIPINFO_H)
#define TOOLTIPINFO_H

#include <string>
using std::string;

#include <d3dx9core.h>
#include <Windows.h>

//include only for debug stuff maybe

#include "../../../../EngineGameModuleDirectX9/src/Application/Globals.h"
#include "../../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "TooltipEffect.h"

class TooltipInfo //Base Class
{
protected:
	//static float m_zoneSpill;
	static LPD3DXFONT m_nameFont;
	static LPD3DXFONT m_textFont;
	static RECT m_fontPosition;
	static char m_buffer[1000];

	string * m_name; //point to ability name / item name
	
	

public:
	TooltipInfo();
	~TooltipInfo();
	virtual void Render();
	void RenderEffect(TooltipEffect * effect);

	const string * GetName();

	virtual UIElement * GetBackground();
	
	void SetName(string * name);

};





#endif