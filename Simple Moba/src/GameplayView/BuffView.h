#if !defined(BUFFVIEW_H)
#define BUFFVIEW_H

#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../UI/Tooltips/TooltipInfoBuff.h"

class BuffView
{
private:
	UIElement m_icon;
	TooltipInfoBuff m_tooltip;

public:
	BuffView();
	~BuffView();

	UIElement * GetIcon();
	TooltipInfoBuff * GetTooltip();

};

#endif
