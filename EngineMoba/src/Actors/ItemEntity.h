#if !defined (ITEMENTITY_H)
#define ITEMENTITY_H

#include  "VitalEntity.h"
#include "PlayerCharacterController.h"

enum ItemConditionScheme
{
	itemConditionAny,
	itemConditionTeam,
	itemConditionPlayerList,
	itemConditionNone,
	itemConditionSchemeCount
};

enum ItemRecieveReturn
{
	itemRecieveOK,
	itemRecieveWrongTeam,
	itemRecieveNotInQuest,
	itemRecieveNo,
	itemRecieveError,
	itemRecieveReturnCount
};

class ItemEntity
{
private:
	int m_itemClass;
	VitalEntity m_vitalEntity;

	bool m_isActive;
	ItemConditionScheme m_condition;
	TeamName m_teamName;
	vector<PlayerCharacterController*> * m_individualPlayers;//who can take items

	vector<PlayerCharacterController*> * m_team; //who can give vision to items

public:
	ItemEntity();
	ItemEntity(ItemEntity & i);
	~ItemEntity();

	bool Init(int itemClass,
		bool isActive, //bool m_isActive;
		ItemConditionScheme condition //ItemConditionScheme m_condition;
		);

	int GetitemClass();
	VitalEntity * GetVitalEntity();

	ItemRecieveReturn IsRecievable(Character * character);

	//SetTeamName = teamName;
	//SetTeam = team;
	//SetIndividualPlayers = individualPlayers;

	bool GetIsActive();


	void SetIsActive(bool activeState);

};

#endif