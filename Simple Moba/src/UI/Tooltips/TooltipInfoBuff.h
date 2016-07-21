#if !defined(TOOLTIPINFOBUFF_H)
#define TOOLTIPINFOBUFF_H

#include <vector>
using std::vector;
#include <string>
using std::string;

#include "../../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../../EngineGameModuleDirectX9/src/Application/Globals.h"
#include "TooltipInfo.h"

class TooltipInfoBuff : public TooltipInfo
{
private:
	vector < TooltipEffect > * m_effects;

public:
	static UIElement m_background;

	TooltipInfoBuff();
	~TooltipInfoBuff();

	void Render();

	//accessors
	UIElement * GetBackground();


	//mutators
	void SetEffects(vector<TooltipEffect> * effects);

};


#endif