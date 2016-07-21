#if !defined(UILAYOUTINVENTORY_H)
#define UILAYOUTINVENTORY_H

#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "UILayoutItem.h"
#include "UILayoutGroup.h"

class UILayoutInventory : public UILayoutGroup
{
private:


public:
	vector<UILayoutItem> m_items;
	vector<ItemView> * m_itemViews;

	UILayoutInventory();
	~UILayoutInventory();

	bool Init();


	void Update(float deltaTime);
	void Render();

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);


	void SetItems(vector<Item *> * inventory);
	void SetItemViews(vector<ItemView> * itemViews);
	
};

#endif