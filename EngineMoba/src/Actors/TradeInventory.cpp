#include "TradeInventory.h"

TradeInventory::TradeInventory()
{
	//m_name = "";
	//m_shopInventory = NULL;
	//OnEnterTradeMode();
	m_selectedShopIndex = -1;
}

TradeInventory::TradeInventory(ShopInventory * shopInventory, string shopName)
{
	Init(shopInventory, shopName);

	OnEnterTradeMode();
}

TradeInventory::~TradeInventory()
{

}

bool TradeInventory::Init(ShopInventory * shopInventory, string shopName)
{
	m_name = shopName;
	m_shopInventory.push_back(shopInventory);



	SetShopAsActive(0);
	return true;
}

bool TradeInventory::Init(string shopName)
{
	m_name = shopName;

	return true;
}

void TradeInventory::Update(float deltaTime)
{
	switch (m_state)
	{
	case tradeInventoryShopMode: ShopMode(deltaTime); break;
	case tradeInventoryTradeMode: TradeMode(deltaTime); break;
	}
}

void TradeInventory::OnEnterShopMode()
{
	m_state = tradeInventoryShopMode;
}

void TradeInventory::ShopMode(float deltaTime)
{

}

void TradeInventory::OnExitShopMode()
{

}

void TradeInventory::OnEnterTradeMode()
{
	m_state = tradeInventoryTradeMode;
}

void TradeInventory::TradeMode(float deltaTime)
{

}

void TradeInventory::OnExitTradeMode()
{

}

void TradeInventory::ExitCurrentState()
{
	switch (m_state)
	{
	case tradeInventoryShopMode: OnExitShopMode();  break;
	case tradeInventoryTradeMode: OnExitTradeMode(); break;
	}
}

TradeInventoryState TradeInventory::GetState()
{
	return m_state;
}

void TradeInventory::ActionSetMode(TradeInventoryState state)
{
	switch (state)
	{
	case tradeInventoryShopMode: break;
	case tradeInventoryTradeMode: break;
	}
}

void TradeInventory::ActionOnConfirmTrade()
{
	for (unsigned int i = 0; i < m_onConfirmTrade.size(); i++)
	{
		m_onConfirmTrade.at(i)();
		OutputDebugString("Callback called");
	}
}


string * TradeInventory::GetName() { return &m_name; }

int TradeInventory::PrivateInventoryFreeSpace()
{
	int freeCount = 0;

	for (unsigned int index = 0; index < m_privateInventory->size(); index++)
	{
		if (m_privateInventory->at(index) == NULL) freeCount++;
	}

	return freeCount;
}



vector <Item *> * TradeInventory::GetPrivateTradeInventory() { return m_privateInventory; }

ShopInventory * TradeInventory::GetShopInventory() { 
	if (m_shopInventory.size() == 0) return nullptr;
	return m_shopInventory.at(m_selectedShopIndex); }

vector<ShopZone*> * TradeInventory::GetShopZones() { return &m_shopZones; }

bool TradeInventory::SetShopAsActive(int index)
{
	if (index < 0 || index >= m_shopInventory.size()) return false;

	m_selectedShopIndex = index;
	m_selectedShopInventory = m_shopInventory.at(index);

	for (unsigned int i = 0; i < m_onChangeShopInventory.size(); i++)
		m_onChangeShopInventory.at(i)(m_shopInventory.at(index)->GetInventoryID());

}
void TradeInventory::SetPrivateTradeInventory(vector<Item*>* inv) { m_privateInventory = inv; }

int TradeInventory::PushActivateShopInventory(ShopInventory * inv, bool activate)
{
	m_shopInventory.push_back(inv);
	
	if (activate)
	{
		SetShopAsActive(m_shopInventory.size() - 1);
	}

	return m_shopInventory.size() - 1;
}

//void TradeInventory::SetShopInventory(ShopInventory * inv){ m_shopInventory.push_back(inv); }

short TradeInventory::GetSelectedShopIndex() { return m_selectedShopIndex; }
ShopInventory * TradeInventory::GetSelectedShopInventory() { return m_selectedShopInventory; }
vector<ShopInventory*>* TradeInventory::GetShopInvVector() { return &m_shopInventory; }
void TradeInventory::AddCallbackOnConfirm(std::function<void()> f) { m_onConfirmTrade.push_back(f); }

void TradeInventory::AddCallbackOnChangeShopInventory(std::function<bool(int id)> f) { m_onChangeShopInventory.push_back(f); }
