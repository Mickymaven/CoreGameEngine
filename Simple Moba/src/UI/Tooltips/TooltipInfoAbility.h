#if !defined(TOOLTIPINFOABILITY_H)
#define TOOLTIPINFOABILITY_H

#include <vector>
using std::vector;
#include <string>
using std::string;

#include "../../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../../EngineMoba/src/Actors/Actor.h"
#include "../../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../../EngineGameModuleDirectX9/src/Application/Globals.h"
#include "TooltipInfo.h"

class TooltipInfoAbility : public TooltipInfo
{
private:
	static UIElement m_background;
	vector < TooltipEffect > * m_effects;

public:
	TooltipInfoAbility();
	~TooltipInfoAbility();

	void Render();

	//accessors
	UIElement * GetBackground();
	

	//mutators
	void SetEffects(vector<TooltipEffect> * effects);

};

#endif