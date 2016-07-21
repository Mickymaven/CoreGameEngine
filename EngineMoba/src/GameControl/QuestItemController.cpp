#include "QuestItemController.h"

QuestItemController::QuestItemController()
{
	m_itemFactory = nullptr;
}

QuestItemController::~QuestItemController()
{
}

bool QuestItemController::Init(ItemFactory * itemFactory)
{
	m_itemFactory = itemFactory;

	return true;
}

void QuestItemController::SelectItem(Quest * quest, Character * character, int itemIndex)
{
	//1. will quest let us take this item
	if (!quest->IsItemAvailable(character, itemIndex)) return;

	//2. will quest let us give item to this actor controller?
	//todo

	//3. free space in actor controller inv?

	if (character->GetTradeInventory()->PrivateInventoryFreeSpace() > 0)
	{
		//a. find item from quest item, place appropiate item pointer in player inv.
		int itemToAdd = quest->SelectItem(character, itemIndex)->GetitemClass();

		//b. place found item

		for (unsigned int index = 0; index < character->GetInventory()->size(); index++)
		{
			if (character->GetInventory()->at(index) == NULL)
			{
				character->GetInventory()->at(index) = m_itemFactory->GetItemSharedOrCopyByEnum((ItemName)itemToAdd);
				quest->TakeItem(itemIndex);

				break;
			}
		}

		//c. set questitem as used
		//todo

	}
	else
	{
		//OnNoSpaceForItem;
	}


}