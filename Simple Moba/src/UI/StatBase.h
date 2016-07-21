#if !defined(STATBASE_H)
#define STATBASE_H

#include <functional>
using namespace std::placeholders;
#include <vector>
using std::vector;

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h"

#include "Tooltips/TooltipController.h"
#include "../UI_Base/UILayoutItem.h"

class StatBase : public UIArea
{
private:
protected:
	LPD3DXFONT m_textFont;
	RECT m_fontPosition;
	char m_textBuffer[200];

	vector<LMVector3> m_itemPositions;

public:
	StatBase();
	~StatBase();

	bool Init(TooltipController * tooltipController);

	void InfoPanelRenderRow(Character * character);
	void RenderScore(PlayerKDA kda);
	void RenderRow(Character * character);
	void RenderInvRow(Character * character);

};



#endif