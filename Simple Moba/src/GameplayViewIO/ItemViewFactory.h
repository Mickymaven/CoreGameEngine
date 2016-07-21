#if !defined(ITEMVIEWFACTORY_H)
#define ITEMVIEWFACTORY_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "../../../EngineMoba/src/GamestateIO/ItemFactory.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../CoreGame/src/Gameplay/Items/ItemName.h"
#include "../../../CoreGame/src/Gameplay/Items/ItemData.h"
#include "../GamestateView/MobaGameElementsEnum.h"
#include "../GamestateView/ViewProfile.h"
#include "../GameplayView/ItemView.h"


#include "AbilityViewFactory.h"

class ItemViewFactory
{
private:
	static string m_iconPath[itemCount];
	
	LPDIRECT3DDEVICE9 m_device;

	ItemData m_itemData;

	vector<Item*> * m_items;
	vector<ItemView> m_itemViews;
	ViewProfile * m_viewProfile;
	AbilityViewFactory * m_abilityViewFactory;

public:
	ItemViewFactory();
	~ItemViewFactory();

	bool Init(LPDIRECT3DDEVICE9 device, ViewProfile * viewProfile, ItemFactory * itemFactory, AbilityViewFactory * abilityViewFactory);

	bool ConstructItemView(ItemName name, ItemView ** buffViewOut);

	vector<ItemView> * GetLightweightItemViews();

};


#endif