#if !defined(TABGROUP_H)
#define TABGROUP_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "../../../EngineGameModel/src/Maths/LMVector2.h"

#include "FontGroup.h"
#include "UITab.h"

class TabGroup : public UIArea
{
private:
	vector < UITab* > m_tabs;
	bool m_isVertical;

public:
	TabGroup();
	~TabGroup();
	bool Init(LMVector2 * origin, LMVector2 * size);
	void PositionContent(RECT * bounds);
	void CalcPos();
	void Render();

	bool NewTab(float w, float h, string path, FontGroup * fontGroup, string * labelText, UIContentArea * contentArea, std::function<bool(UIContentArea*)> f);

	void Select(POINT * p);
	void AltSelect(POINT * p);

	vector < UITab* > *  GetTabs();

	//void PushTab(UITab* tab);  //i dont see me using this commented out in .cpp
};

#endif