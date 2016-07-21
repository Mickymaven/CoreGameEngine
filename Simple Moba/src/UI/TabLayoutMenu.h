#if !defined(TABLAYOUTMENU_H)
#define TABLAYOUTMENU_H

#include <functional>
using namespace std::placeholders;

#include "../../../EngineGameModuleDirectX9/src/UI/UIMenu.h"
#include "../../../EngineGameModuleDirectX9/src/UI/TabGroup.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIContentArea.h"

class TabLayoutMenu : public UIMenu
{
private:
protected:
	TabGroup m_tabgroup;
	vector<UIContentArea*> m_content;
	UIContentArea * m_page;

	LMVector4 m_pageOrigin;

public:
	TabLayoutMenu();
	~TabLayoutMenu();

	bool Init();
	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);

	bool SetPage(UIContentArea * contentArea);

	LMVector4 * GetPageOrigin();
};

#endif