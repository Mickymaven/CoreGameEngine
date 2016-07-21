#if !defined(UILAYOUTBASE_H)
#define UILAYOUTBASE_H


#include <functional>
using namespace std::placeholders;

#include "../../../EngineGameModuleDirectX9/src/UI/UIBase.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"

class UILayoutBase : public UIBase
{
protected:
	UIElement * m_icon;
	std::function<void()> m_callback;
	bool m_selected;

public:
	UILayoutBase();
	~UILayoutBase();

	virtual void Select(POINT * p) = 0;
	virtual void AltSelect(POINT * p) = 0;
	virtual bool MouseOver(POINT * p) = 0;

	UIElement * GetIcon();
	bool GetIsSelected();

	void SetPosition(float x, float y, float z);
	void SetCallback(std::function<void()> f);
	void SetIcon(UIElement * uielement);
	void SetIsSelected(bool state);
};

#endif