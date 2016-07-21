#if !defined(SHOPINVENTORY_H)
#define SHOPINVENTORY_H

#include <vector>
using std::vector;

#include "../../../EngineMoba/src/Item/Item.h"

class ShopInventory
{

private:
	int m_invId;
	vector<int> m_inventory;
	//<Item *> m_itemsToRender;
public:
	ShopInventory();
	~ShopInventory();

	int GetInventoryID();
	vector <int> * GetInventory();
	//vector <Item *> * GetItemsPointer();

	void SetInventoryID(int id);

	
};


#endif