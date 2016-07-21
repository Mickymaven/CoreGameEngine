#if !defined(UICONTENTAREA_H)
#define UICONTENTAREA_H

#include <string>
using std::string;

#include "UIArea.h"

#include "../../../EngineGameModel/src/Maths/LMVector4.h"

//has things like labels text
//buttons text input
//can scroll it around



struct ContentCat
{
public:
	ContentCat(){}

	LMVector4 bounds;
	vector<vector<UIBase*>> allRows;

};

class UIContentArea : public UIArea
{
protected:
	string m_name;
	LMVector4 m_bounds;
	vector<ContentCat> m_categories;

public:
	UIContentArea();
	UIContentArea(const UIContentArea & c);
	~UIContentArea();

	virtual bool Init();
	virtual void Render();

	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);
	virtual bool MouseOver(POINT * p);

	void PositionCategoryLayout(LMVector4 * bounds);
	void CategoryLayoutRender();
};

#endif