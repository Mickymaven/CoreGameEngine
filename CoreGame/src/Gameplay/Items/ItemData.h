#if !defined(ITEMDATA_H)
#define ITEMDATA_H

#include <vector>
using std::vector;

#include "../Abilities/AbilityName.h"
#include "ItemName.h"

struct ItemData
{
	static vector<AbilityName> m_itemAbilities;

	ItemData();
	void InitItemData();



};

#endif