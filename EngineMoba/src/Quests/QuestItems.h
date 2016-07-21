#if !defined(QUESTITEMS_H)
#define QUESTITEMS_H

#include <vector>
using std::vector;

#include "../Actors/ItemEntity.h"

class QuestItems
{
protected:
	

public:
	vector<ItemEntity> m_items;

	QuestItems();
	~QuestItems();

	vector<ItemEntity> * GetItems();
};

#endif