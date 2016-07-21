#if !defined(TRADEINVENTORY_H)
#define TRADEINVENTORY_H

#include <vector>
using std::vector;

#include "ShopInventory.h"
#include "ShopZone.h"

#include <functional>
using namespace std::placeholders;

enum TradeInventoryState
{
	tradeInventoryShopMode,
	tradeInventoryTradeMode,
	tradeInventoryStateCount
};

class TradeInventory
{
private:	
	vector <Item *> * m_privateInventory;
	vector <ShopInventory *> m_shopInventory;
	
	short m_selectedShopIndex;
	ShopInventory * m_selectedShopInventory;

	string m_name;

	vector<ShopZone *> m_shopZones;

	TradeInventoryState m_state;

	vector<std::function<void()>> m_onConfirmTrade;
	vector<std::function<bool(int id)>> m_onChangeShopInventory;


public:
	TradeInventory();
	TradeInventory(ShopInventory * shopInventory, string shopName);
	~TradeInventory();
	
	bool Init(ShopInventory * shopInventory, string shopName);
	bool Init(string shopName);

	void Update(float deltaTime);

	void OnEnterShopMode();
	void ShopMode(float deltaTime);
	void OnExitShopMode();

	void OnEnterTradeMode();
	void TradeMode(float deltaTime);
	void OnExitTradeMode();

	void ExitCurrentState();

	TradeInventoryState GetState();

	void ActionSetMode(TradeInventoryState state);
	void ActionOnConfirmTrade();


	string * GetName();
	
	int PrivateInventoryFreeSpace();

	vector <Item *> * GetPrivateTradeInventory();
	ShopInventory * GetShopInventory();

	vector<ShopZone*> * GetShopZones();

	bool SetShopAsActive(int index);

	void SetPrivateTradeInventory(vector <Item *> * inv);
	int PushActivateShopInventory(ShopInventory * inv, bool activate);
	//void SetShopInventory(ShopInventory * inv);


	short GetSelectedShopIndex();
	ShopInventory * GetSelectedShopInventory();
	vector<ShopInventory *> * GetShopInvVector();


	void AddCallbackOnConfirm(std::function<void()> f);

	void AddCallbackOnChangeShopInventory(std::function<bool(int id)> f);

};

#endif