#if !defined (CHARACTER_H)
#define CHARACTER_H

#include "../Item/Item.h"

#include "../Actor_Control/AttackMoveController.h"
#include "../Actor_Control/BattleStateController.h"
#include "../Actor_Control/PathController.h"
#include "../Actor_Control/WalkState.h"


#include "PlayerActionEnum.h"

#include "TradeInventory.h"
#include "Actor.h"
#include "ShopZone.h"

#include "VitalEntityController.h"

enum CastTestResult
{
	castTestError,
	castTestOK,
	//player world selection
	castTestTargetMissing,//if selection controller is not getting amouse over target

	// actor problems
	castTestNoAbilitySelected,
	//castTestActorAsleep, //cannot be in a cast state when asleep or dead so its like castTestNoAbilitySelected anyway
	//castTestActorDead,

	//ability problems
	castTestAbilityRequiredTargetMissing,
	castTestAbilityStillActive,
	castTestAbilityCooldown,
	castTestMaxCountReached,//3 basics active at any one time for eg.
	castTestNotInRange,

	//intargetable
	castTestIntargetable,

	castTestResultCount
};

//Replaces ActorController

class Character : public VitalEntityController
{
private:

protected:
	Actor * m_actor;

	AttackMoveController m_attackMoveController;
	BattleStateController m_battleStateController;
	PathController m_pathController;
	WalkState m_walkState;

	vector <Ability *> m_abilities;

	vector <Item *> m_inventory;
	TradeInventory m_tradeInventory;
	ShopZone m_zoneThatFollows;

	int m_inventoryValue;

	PlayerAction m_slotCastingIndex;//change this data type and underlying impelemtation
									//or at least share the player action enum a different way
	Ability * m_selectedAbility;


public:
	Character();
	Character(Actor * actor, Pathfinder * pathfinder);
	~Character();

	void Update(float deltaTime);
	void UpdateBuffStructure(float deltaTime, vector<Buff*> * buffVector);


	//Ability * GetSlotAbility(int slot);//delete soon
	//Ability * GetAbilitySlot(PlayerAction action); // < new function

	void ActionCastAbility(PlayerAction action, int slotIndex, float gameTime, vector<Actor * > * playerTeam, vector<Actor * > * opponentTeam, vector<Actor * > * neutralTeam);

	void SetCastStateForAbility(Ability * ability, float gameTime, PlayerAction action, vector<Actor * > * playerTeam, vector<Actor * > * opponentTeam, vector<Actor * > * neutralTeam);
	bool RemoveIfConsumableItem(PlayerAction action);

	CastTestResult SelectCastTest(float gameTime, LMVector3 * m_indicatorDirectionVector, LMVector3 * mousePositionVector, Actor * target, vector<Actor * > * playerTeam, vector<Actor * > * opponentTeam, vector<Actor * > * neutralTeam);
	void ActionSelectWithMouse(float gameTime, LMVector3 * m_indicatorDirectionVector, LMVector3 * mousePositionVector, Actor * target, vector<Actor * > * playerTeam, vector<Actor * > * opponentTeam, vector<Actor * > * neutralTeam); //usually left click

	void ActionWalkOrBasicAttack(float gameTime, VitalEntity * target); //usually right click
	void ActionWalkOrBasicAttack(float gameTime, LMVector3 * point); //usually right click	

	void ActionInventory(PlayerAction action, int vectorIndex, float gameTime, vector<Actor * > * playerTeam, vector<Actor * > * opponentTeam, vector<Actor * > * neutralTeam);

	void KeyMove(float gameTime, char dir,
		LMVector3 * cam3p, LMVector3 * cLookAtPos, LMVector3 * walkIndicatorPos);

	void ActionStop();
	void ActionAttackMove();
	void ActionDriveBy();
	void DebugTeleport(float x, float y, float z);

	void OnRespawn(float x, float y, float z);

	Ability * GetAbilityAtIndex(unsigned int i);
	int * GetInventoryValue();

	Actor * GetActor();
	vector<Ability *> * GetAbilities();
	vector<Item *> * GetInventory();
	TradeInventory * GetTradeInventory();
	AttackMoveController * GetAttackMoveController();
	BattleStateController * GetBattleStateController();
	PathController * GetPathController();
	WalkState * GetWalkState();

	void SetInvFromSet(vector<Item*> * set);

	//stat accessors
	void InitAbility(int slotToInit, Ability * ability);
	Ability * ReturnCastingAbility();
	ShopZone * GetFollowingZone();

	//stat mutators
	//moved to coreCharacter void AddAbility(Ability * ability, AbilitySlotType slot);



	//private as we only want to keep this legacy code for poss server use.
private:PlayerAction GetCastingAbility();

};


#endif