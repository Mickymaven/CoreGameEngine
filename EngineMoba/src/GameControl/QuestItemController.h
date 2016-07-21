#if !defined (QUESTITEMCONTROLLER_H)
#define QUESTITEMCONTROLLER_H

#include "../../../EngineMoba/src/GamestateIO/ItemFactory.h"
#include "../Quests/Quest.h"

class QuestItemController
{
private:
	ItemFactory * m_itemFactory;
public:
	QuestItemController();
	~QuestItemController();
	
	bool Init(ItemFactory * itemFactory);

	void SelectItem(Quest * quest, Character * character, int itemIndex);

};

#endif