#if!defined(UILAYOUTITEM_H)
#define UILAYOUTITEM_H

#include <functional>
using namespace std::placeholders;


#include "../../../EngineGameModel/src/Maths/LMVector4.h"
#include "../../../EngineMoba/src/Ability/Ability.h"
#include "../../../EngineMoba/src/Item/Item.h"
#include "../UI/Tooltips/TooltipInfo.h"
#include "../GameplayView/ItemView.h"


#include "UILayoutBase.h"

class UILayoutItem : public UILayoutBase
{
private:
	Item * m_item;
	ItemView * m_itemView;
	std::function<void(RECT * bounds, TooltipInfoItem * tooltipInfoItem, Ability * ability)> m_mouseOverCallback;

public:
	UILayoutItem();
	UILayoutItem(Item * item);
	UILayoutItem(Item * item, ItemView * itemView);
	~UILayoutItem();

	void Update(float deltaTime);
	void Render();
	void RenderAtPosition(float x, float y, float z);

	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);
	virtual bool MouseOver(POINT * p);
	bool MouseOverCallBackWithBounds(RECT * bounds);

	Item * GetItem();
	ItemView * GetItemView();

	void SetMouseOverCallback(std::function<void(RECT * bounds, TooltipInfoItem * tooltipInfoItem, Ability * ability)> f);
	
	void SetWithItemView(ItemView * itemView);

	void SetItem(Item * item);
	void SetItemView(ItemView * itemView);

};

#endif