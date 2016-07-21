#if !defined(QUESTVIEW_H)
#define QUESTVIEW_H

#include <vector>
using std::vector;

#include "../../../../EngineMoba/src/Quests/Quest.h"
#include "../ItemEntityView.h"
#include "../ShopInventoryView.h"


class QuestView
{
private:
	Quest * m_quest;
	vector<ItemEntityView> m_itemViews;
	vector<ShopInventoryView> m_shopInventoryViews;

public:
	QuestView();
	~QuestView();

	bool Init(Quest * quest, ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds);
	bool InitShopViews(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds);

	void Render();

	void AddItemView(LPDIRECT3DDEVICE9 device, ItemEntity * itemEntity, LMMesh * mesh);

	vector<ItemEntityView> * GetItemViews();

	Quest * GetQuest();

};

#endif