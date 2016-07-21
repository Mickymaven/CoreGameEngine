#include "ItemViewFactory.h"

string ItemViewFactory::m_iconPath[itemCount] =
{
	"Resources/UI/Items/item_basic_boot.png",
	"Resources/UI/Items/item_basic_sneakers.png",
	"Resources/UI/Items/item_tree_branch.png",
	"Resources/UI/Items/item_nom_bar.png",
	"Resources/UI/Items/item_ketchup.png",//ketchup
	"Resources/UI/Items/item_bike.png",//bike
	"Resources/UI/Items/item_drill.png",//drill
};

ItemViewFactory::ItemViewFactory()
{
	m_items = nullptr;
}

ItemViewFactory::~ItemViewFactory()
{
	for (unsigned int index = 0; index < itemCount; index++)
	{
		//delete m_itemIcons.at(index);
		//m_itemIcons.at(index) = NULL;
	}
}

bool ItemViewFactory::Init(LPDIRECT3DDEVICE9 device, ViewProfile * viewProfile, ItemFactory * itemFactory, AbilityViewFactory * abilityViewFactory)
{
	m_device = device;
	m_viewProfile = viewProfile;
	m_items = itemFactory->GetLightweightItems();

	m_abilityViewFactory = abilityViewFactory;

	m_itemData.InitItemData();


	if (!viewProfile->InitElement(gameElementItemTooltipBackground, &TooltipInfoItem::m_background)) return false;

	//TooltipInfoItem::m_background = UIElement(400.0f, 267.0f, "Resources/misc/ux_tool_tip_ability.png");
	//TooltipInfoItem::m_background.Init();

	m_itemViews.resize(itemCount);

	for (unsigned int i = 0; i < itemCount; i++)
	{
		string path;
		string name;

		//vector < TooltipEffect > * effects = new vector<TooltipEffect>;

		//TooltipEffect buffEffect1;
		
		path = m_iconPath[i];
		switch (i)
		{
		case itemBasicBoots:
			name = "Basic Boots";
			break;
		case itemBasicSneakers:
			name = "Basic Sneakers";
			break;
		case itemTreeBranch:
			name = "Tree Branch";
			break;
		case itemNomBar:
			name = "Nom Bar";
			break;
		case itemKetchup:
			name = "Ketchup";
			break;
		case itemBike:
			name = "The Bike";
			break;
		case itemOwlDrill:
			name = "Owl's Drill";
			break;
		default: case itemCount:
			break;
		}


		if (!viewProfile->InitElementWithPath(gameElementItemIcon, m_itemViews.at(i).GetIcon(), path)) false;

		//m_itemViews.at(i).GetIcon()->Init(43.0f, 43.0f, path);
		m_itemViews.at(i).SetItem(m_items->at(i));

		m_itemViews.at(i).GetTooltip()->SetName(new string(name));
		m_itemViews.at(i).PushTooltipStats();
		

		AbilityView * abv;

		if (m_itemData.m_itemAbilities.at(i) != abilityCount) //in ItemData abilityCount means 'no ability for this item'
		{
			if (!m_abilityViewFactory->ConstructAbilityView(device, &abv, m_itemData.m_itemAbilities.at(i), m_items->at(i)->GetAbility()))
			{
				OutputDebugString("didnt work / item view factory.");
			}
			m_itemViews.at(i).SetAbilityView(abv);
			m_itemViews.at(i).GetTooltip()->SetEffects(abv->GetEffects());

		}
		else
		{
			m_itemViews.at(i).SetAbilityView(NULL);
			m_itemViews.at(i).GetTooltip()->SetEffects(NULL);
		}


	}

	return true;
}

bool ItemViewFactory::ConstructItemView(ItemName name, ItemView ** buffViewOut)
{
	return true;
}

vector<ItemView> * ItemViewFactory::GetLightweightItemViews()
{
	return &m_itemViews;
}
