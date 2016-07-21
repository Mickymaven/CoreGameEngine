#include "ShopInventoryView.h"

PlayerCharacterController * ShopInventoryView::m_selectedPlayerController = NULL;
ItemFactory * ShopInventoryView::m_itemFactory = NULL;
TooltipController * ShopInventoryView::m_tooltipController = NULL;
vector<ItemView> * ShopInventoryView::m_lightweightItemViews = NULL;

ShopInventoryView::ShopInventoryView()
{
	m_shopInventory = NULL;
}

ShopInventoryView::ShopInventoryView(const ShopInventoryView & s)
{
}

ShopInventoryView::~ShopInventoryView()
{

}

bool ShopInventoryView::Init(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds, ShopInventory * shopInventory)
{
	m_shopInventory = shopInventory;
	
	m_name = "Game Shop View";

	m_bounds.values[0] = bounds->x();
	m_bounds.values[1] = bounds->y();
	m_bounds.values[2] = bounds->z();
	m_bounds.values[3] = bounds->w();

	m_categories.resize(1);
	ContentCat * cat = &m_categories.at(0);
	cat->bounds = LMVector4();
	vector<UIBase*> * m_row = m_row = new vector < UIBase * >;

	RECT rect = { 0, 0, 0, 0 };

		
	//CAT VIEW (view with labels)

	//vector<Item *> * shopInvItems = gameShop->GetShopInventory()->GetItemsPointer();

	//some npcs will have empty shop invs
	//if ((vector<ItemName> *)gameShop->GetShopInventory() == nullptr) return true;


	vector<ItemName> * shopInvItemName = (vector<ItemName> *)shopInventory->GetInventory();


	UILabel * label = NULL;
	UILayoutItem * layoutItem = NULL;
	ItemView * itemView = NULL;
	Item * item = NULL;

	char m_tempbuffer[50];
	char * arg = NULL;

	int columnCount = 1;
	if (shopInvItemName !=NULL)
	{
		for (unsigned int i = 0; i < shopInvItemName->size(); i++)
		{
			itemView = &m_lightweightItemViews->at(shopInvItemName->at(i));
			item = itemView->GetItem();
			layoutItem = new UILayoutItem( item, itemView ); //todo leaky

			layoutItem->SetMouseOverCallback(std::bind(&TooltipController::ActivateTooltipItem, m_tooltipController, _1, _2, _3));
			m_layoutItems.push_back(layoutItem);
			m_row->push_back(layoutItem);

			sprintf_s(m_tempbuffer, "%i: %s", item->GetValue(), itemView->GetTooltip()->GetName()->c_str() );

			
			label = new UILabel();
			
			//ThemeResourceProfile * m_themeResourceProfile;
			//AspectProfile * m_aspectProfile;

			//if (!viewProfile->InitElement(gameElementTradeInventoryLabel, label)) false;
			

			if (!label->Init(rect, &theme->m_shopItemLabel, new string(m_tempbuffer))) return false;

			

			label->SetWidth(viewProfile->m_aspectProfile->GetWidthForElement(gameElementTradeInventoryLabel));
			label->SetHeight(viewProfile->m_aspectProfile->GetHeightForElement(gameElementTradeInventoryLabel));

			m_row->push_back(label);

			if (i == shopInvItemName->size() - 1) cat->allRows.push_back(*m_row);
			else if (columnCount == 3)
			{
				cat->allRows.push_back(*m_row);
				m_row = new vector < UIBase * >;

				columnCount=1;
			}
			else
			{
				columnCount++;
			}
		}
	}

	/////////////////////////////////////////////////////////////

	m_maxInvSize = 10;

	// SHOP SELECTED
	m_shopBuyCount = 0;
	m_shopSelectionCount.resize(m_maxInvSize);
	std::fill(m_shopSelectionCount.begin(), m_shopSelectionCount.end(), 0);






	/// TODo move to trade inventory view






	///////////////////////////////

	// INV VIEW ///////////////////




	m_playerInventory.resize(m_maxInvSize);

	for (unsigned int i = 0; i < m_maxInvSize; i++)
		m_playerInventory.at(i).SetMouseOverCallback(
			std::bind(&TooltipController::ActivateTooltipItem, m_tooltipController, _1, _2, _3));

	m_playerInventoryUnselected.resize(m_maxInvSize);
	m_playerInventorySelected.resize(m_maxInvSize);
	m_shopSelected.resize(m_maxInvSize);

	m_shopBounds.left() = bounds->left() + 100.0f;
	m_shopBounds.top() = bounds->top() + 260.0f;
	m_shopBounds.right() = bounds->right() - 200.0f;
	m_shopBounds.bottom() = bounds->bottom();

	PositionContent(&m_shopBounds);

	m_invBounds.left() = bounds->right() -200.0f;
	m_invBounds.right() = bounds->right() - 20.0f;
	m_invBounds.top() = bounds->top() + 260.0f;
	m_invBounds.bottom() = bounds->bottom();
	
	SetInvItems();
	PositionInvItems(&m_invBounds);
	
	return true;
}

void ShopInventoryView::PositionContent(LMVector4 * bounds)
{
	PositionCategoryLayout(&m_shopBounds);
}

void ShopInventoryView::PositionInvItems(LMVector4 * bounds)
{
	float rowTop = 0.0f;
	float elementLeft = 0.0f;
	LMVector3 * pos = NULL;
	RECT * eleBounds = NULL;
	float eleWidth = 0.0f;
	float eleHeight = 0.0f;
	vector<UILayoutItemClone> * itemVector = NULL;

	for (unsigned int n = 0; n < 3; n++)
	{
		if (n == 0) itemVector = &m_playerInventoryUnselected;
		if (n == 1) itemVector = &m_playerInventorySelected;
		if (n == 2) itemVector = &m_shopSelected;
		
		rowTop = bounds->top() + 10.0f;
		elementLeft = bounds->right() - 60.0f  - (n * 85.0f);

		for (unsigned int i = 0; i < m_playerInventorySelected.size(); i++)
		{
			itemVector->at(i).SetWidth(43.0f);
			itemVector->at(i).SetHeight(43.0f);

			eleWidth = itemVector->at(i).GetWidth();
			eleHeight = itemVector->at(i).GetHeight();
			pos = itemVector->at(i).GetPosition();
			eleBounds = itemVector->at(i).GetBounds();

			pos->x = elementLeft;
			pos->z = rowTop;

			eleBounds->left = elementLeft;
			eleBounds->top = rowTop;
			eleBounds->bottom = rowTop + eleHeight;
			eleBounds->right = elementLeft + eleWidth;

			rowTop += eleHeight + 2.0f;
		}
	}
}

void ShopInventoryView::SetInvItems()
{
	vector <Item *> * inventory = ShopInventoryView::m_selectedPlayerController->GetCharacter()->GetInventory();

	//TODO find place to update selected Player Controller;

	for (unsigned int i = 0; i < inventory->size(); i++)
	{
		if (inventory->at(i) != NULL)
		{
			m_playerInventory.at(i).SetWithItemView(&m_lightweightItemViews->at(inventory->at(i)->GetItemClass()));
			//m_playerInventory.at(i).SetItem(inventory->at(i));
			//m_playerInventory.at(i).SetItemView();
			//m_playerInventory.at(i).SetIcon(m_lightweightItemViews->at(i).GetIcon());

			if (m_playerInventory.at(i).GetIsSelected())
			{
				m_playerInventorySelected.at(i).SetUILayoutItem(&m_playerInventory.at(i));
				m_playerInventoryUnselected.at(i).SetUILayoutItem(NULL);
			}
			else
			{
				m_playerInventorySelected.at(i).SetUILayoutItem(NULL);
				m_playerInventoryUnselected.at(i).SetUILayoutItem(&m_playerInventory.at(i));
			}
		}
		else
		{
			m_playerInventory.at(i).SetItem(NULL);
			m_playerInventory.at(i).SetItemView(NULL);
			m_playerInventory.at(i).SetIcon(NULL);

			m_playerInventorySelected.at(i).SetUILayoutItem(NULL);
			m_playerInventoryUnselected.at(i).SetUILayoutItem(NULL);
		}
		
	}
}

void ShopInventoryView::SetShopSelected()
{
	unsigned int cloneIndex = 0;
	
	for (unsigned int h = 0; h < m_shopSelected.size(); h++)
	{
		m_shopSelected.at(h).SetUILayoutItem(NULL);
	}

	for (unsigned int i = 0; i < m_shopSelectionCount.size(); i++)
	{
		if (m_shopSelectionCount.at(i) > 0)
		{
			for (unsigned int j = 0; j < m_shopSelectionCount.at(i); j++)
			{
				if (cloneIndex < m_maxInvSize)
				{
					m_shopSelected.at(cloneIndex).SetUILayoutItem(m_layoutItems.at(i));
					cloneIndex++;
				}
				else return;
			}
		}
	}
}

void ShopInventoryView::Render()
{
	for (unsigned int i = 0; i < m_maxInvSize; i++)
	{
		m_playerInventorySelected.at(i).Render();
		m_playerInventoryUnselected.at(i).Render();
		m_shopSelected.at(i).Render();
	}

	CategoryLayoutRender();
}

void ShopInventoryView::Select(POINT * p)
{
	// SHOP SELECT
	bool test = false;

	for (unsigned int j = 0; j < m_layoutItems.size(); j++)
	{
		if (m_shopBuyCount < m_maxInvSize)
		{
			if (m_layoutItems.at(j)->IsPointInBounds(p))
			{
				test = true;
				m_shopSelectionCount.at(j)++;
				m_shopBuyCount++;
			}
		}
		else break;
	}

	if (test)
	{
		SetShopSelected();
		return;
	}

	//Player Select
	test = false;

	vector<UILayoutItemClone> * itemVector = NULL;
	
	for (unsigned int n = 0; n < 2; n++)
	{
		if (n == 0) itemVector = &m_playerInventorySelected;
		if (n == 1) itemVector = &m_playerInventoryUnselected;
		//if (n == 2) itemVector = &m_shopSelected;
		
		for (unsigned int i = 0; i < itemVector->size(); i++)
		{
			if (itemVector->at(i).IsPointInBounds(p))
			{
				if (itemVector->at(i).GetUILayoutItem() != NULL)
				{
					itemVector->at(i).Select(p);

					test = true;
				}

				n = 2;
				break;
			}
		}
	}

	if (test)
	{
		SetInvItems();
		return;
	}


	//buy summary selection
	test = false;

	int countOfTradeSelection = 0;

	for (unsigned int s = 0; s < m_shopSelected.size(); s++)
	{
		if (m_shopSelected.at(s).IsPointInBounds(p))
		{
			OutputDebugString("Hit selected \n");

			for (int currentArrayIndex = 0; currentArrayIndex < m_maxInvSize; currentArrayIndex++)
			{
				for (int numberSelectedThisIndex = m_shopSelectionCount.at(currentArrayIndex);
					numberSelectedThisIndex > 0; numberSelectedThisIndex--)
				{
					countOfTradeSelection += 1;

					if (countOfTradeSelection == s + 1) break;
				}

				if (countOfTradeSelection == s+1)
				{
					m_shopSelectionCount.at(currentArrayIndex) -= 1;
					test = true;
					m_shopBuyCount--;

					s = m_shopSelected.size();
					break;
				}
			}
		}
	}

	if (test)
	{
		SetShopSelected();
		return;
	}
}

void ShopInventoryView::AltSelect(POINT * p)
{
	// SHOP SELECT
	bool test = false;

	for (unsigned int j = 0; j < m_layoutItems.size(); j++)
	{
		if (m_shopSelectionCount.at(j) > 0)
		{
			if (m_layoutItems.at(j)->IsPointInBounds(p))
			{
				test = true;
				m_shopSelectionCount.at(j)--;
				m_shopBuyCount--;
			}
		}
		else break;
	}

	if (test)
	{
		SetShopSelected();
		return;
	}
}

bool ShopInventoryView::MouseOver(POINT * p)//is virtual;
{
	for (unsigned i = 0; i < m_layoutItems.size(); i++)
		if (m_layoutItems.at(i)->MouseOver(p)) return true;

	for (unsigned i = 0; i < m_playerInventoryUnselected.size(); i++)
		if (m_playerInventoryUnselected.at(i).MouseOver(p)) return true;
	
	for (unsigned i = 0; i < m_playerInventorySelected.size(); i++)
		if (m_playerInventorySelected.at(i).MouseOver(p)) return true;
	
	for (unsigned i = 0; i < m_shopSelected.size(); i++)
		if (m_shopSelected.at(i).MouseOver(p)) return true;

	return false;
}

ShopInventory * ShopInventoryView::GetShopInventory()
{
	return m_shopInventory;
}

void ShopInventoryView::ClearSelection()
{
	for (unsigned int i = 0; i < m_maxInvSize; i++)
	{
		if (m_shopSelected.at(i).GetUILayoutItem() != NULL) m_shopSelected.at(i).SetUILayoutItem(NULL);
		m_playerInventory.at(i).SetIsSelected(false);
	}

	for (unsigned int i = 0; i < m_shopSelectionCount.size(); i++)
	{
		m_shopSelectionCount.at(i) = 0;
	}

	m_shopBuyCount = 0;
}


int ShopInventoryView::UnselectCount()
{
	int unselectCount = 0;

	for (unsigned int index = 0; index < m_playerInventory.size(); index++)
	{
		if (m_playerInventory.at(index).GetIsSelected() == false)
		{
			if (m_playerInventory.at(index).GetItem() != NULL)
				unselectCount++;
		}
	}

	return unselectCount;
}

int ShopInventoryView::BuyCount()
{
	int buyCount = 0;

	for (unsigned int index = 0; index < m_shopSelectionCount.size(); index++)
	{
		buyCount += m_shopSelectionCount.at(index);
	}

	return buyCount;
}

bool ShopInventoryView::TradeWillFit()
{
	if (UnselectCount() + BuyCount() <= m_maxInvSize) return true;
	
	return false;
}

void ShopInventoryView::RemoveOld()
{
	for (unsigned int index = 0; index < m_playerInventory.size(); index++)
	{
		if (m_playerInventory.at(index).GetIsSelected() == true)
		{
			m_playerInventory.at(index).SetIsSelected(false);

			if (m_playerInventory.at(index).GetItem() != NULL)
			{

				if (m_selectedPlayerController->GetCharacter()->GetInventory()->at(index) == NULL)
				{
					OutputDebugString("inv UI mis matched");
				}



				if (m_playerInventory.at(index).GetItem()->GetAbility() != NULL)
				{


					if (m_selectedPlayerController->GetCharacter()->GetInventory()->at(index)->GetAbility() == NULL)
					{
						OutputDebugString("inv UI mis matched");
					}


					delete m_selectedPlayerController->GetCharacter()->GetInventory()->at(index);
					
					//TODO: something here goes wrong brings up that health error thing.
				}

				m_selectedPlayerController->GetCharacter()->GetInventory()->at(index) = NULL;

				m_playerInventory.at(index).SetItem(NULL);
				m_playerInventory.at(index).SetItemView(NULL);
				m_playerInventory.at(index).SetIcon(NULL);

			}
			else
			{
				MessageBox(NULL, "Selected an inv slot that was empty, go and stop program from doing that", "SimMob Err", MB_OK);
			}
		}
	}
}

void ShopInventoryView::AddNew()
{
	for (unsigned int shopSelectedIndex = 0; shopSelectedIndex < m_shopSelectionCount.size(); shopSelectedIndex++)
	{
		if (m_shopSelectionCount.at(shopSelectedIndex) > 0)
		{
			for (unsigned int index = 0; index < m_selectedPlayerController->GetCharacter()->GetInventory()->size(); index++)
			{
				for (int numberPurchased = m_shopSelectionCount.at(shopSelectedIndex);
					numberPurchased > 0; numberPurchased--)
				{
					if (m_selectedPlayerController->GetCharacter()->GetInventory()->at(index) == NULL)
					{
						ItemName itemToBuy =(ItemName) m_shopInventory->GetInventory()->at(shopSelectedIndex);

						// this needs you to take control of deleting objects
						m_selectedPlayerController->GetCharacter()->GetInventory()->at(index) = m_itemFactory->GetItemSharedOrCopyByEnum(itemToBuy);

						//new
						//m_playerInventory.at(index).SetItem(m_selectedPlayerController->GetInventory()->at(index));

						m_playerInventory.at(index).SetWithItemView(
							&m_lightweightItemViews->at(m_selectedPlayerController->GetCharacter()->GetInventory()->at(index)->GetItemClass()) );

						m_shopSelectionCount.at(shopSelectedIndex) -= 1;
						break;
					}
				}
			}
		}
	}
}