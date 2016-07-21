#include "CharacterInputModel.h"

CharacterInputModel::CharacterInputModel()
{}

bool CharacterInputModel::Init(string path)
{

	m_path = "Resources/Settings/CharacterInput.keys";

	m_keybinds.resize(characterActionCount);

	m_keybinds[characterActionKeyMoveLeft] = DIK_LEFT;
	m_keybinds[characterActionKeyMoveRight] = DIK_RIGHT;
	m_keybinds[characterActionKeyMoveUp] = DIK_UP;
	m_keybinds[characterActionKeyMoveDown] = DIK_DOWN;

	m_keybinds[characterActionSelectWithMouse] = MO_LEFT_BUTTON;
	m_keybinds[characterActionWalkOrBasicAttack] = MO_RIGHT_BUTTON;

	m_keybinds[characterActionStop] = DIK_S;
	m_keybinds[characterActionAttackMove] = DIK_A;
	m_keybinds[characterActionDriveByMove] = DIK_D;

	m_keybinds[characterActionCastRecall] = DIK_B;
	m_keybinds[characterActionCastSleep] = DIK_Z;

	m_keybinds[characterActionCastAbility1] = DIK_Q;
	m_keybinds[characterActionCastAbility2] = DIK_W;
	m_keybinds[characterActionCastAbility3] = DIK_E;
	m_keybinds[characterActionCastAbility4] = DIK_R;
	m_keybinds[characterActionCastAbility5] = DIK_T;
	m_keybinds[characterActionCastAbility6] = DIK_F;

	m_keybinds[characterActionInventory1] = DIK_1;
	m_keybinds[characterActionInventory2] = DIK_2;
	m_keybinds[characterActionInventory3] = DIK_3;
	m_keybinds[characterActionInventory4] = DIK_4;
	m_keybinds[characterActionInventory5] = DIK_5;
	m_keybinds[characterActionInventory6] = DIK_6;
	m_keybinds[characterActionInventory7] = DIK_7;
	m_keybinds[characterActionInventory8] = DIK_8;
	m_keybinds[characterActionInventory9] = DIK_9;
	m_keybinds[characterActionInventory0] = DIK_0;


	m_name = new vector<string> {
		"Move Left",
		"Move Right",
		"Move Up",
		"Move Down",

		"Select",
		"Walk/Attack",

		"Stop",
		"Attack Move",
		"Drive By Move",

		"Recall",
		"Sleep",

		"Ability 1",
		"Ability 2",
		"Ability 3",
		"Ability 4",
		"Custom Ability 1",
		"Custom Ability 2",
		"Inventory 1",
		"Inventory 2",
		"Inventory 3",
		"Inventory 4",
		"Inventory 5",
		"Inventory 6",
		"Inventory 7",
		"Inventory 8",
		"Inventory 9",
		"Inventory 10" };

	m_keybinds.resize(characterActionCount);

	m_keybinds[characterActionKeyMoveLeft] = DIK_LEFT;
	m_keybinds[characterActionKeyMoveRight] = DIK_RIGHT;
	m_keybinds[characterActionKeyMoveUp] = DIK_UP;
	m_keybinds[characterActionKeyMoveDown] = DIK_DOWN;

	m_keybinds[characterActionSelectWithMouse] = MO_LEFT_BUTTON;
	m_keybinds[characterActionWalkOrBasicAttack] = MO_RIGHT_BUTTON;

	m_keybinds[characterActionStop] = DIK_S;
	m_keybinds[characterActionAttackMove] = DIK_A;
	m_keybinds[characterActionDriveByMove] = DIK_D;

	m_keybinds[characterActionCastRecall] = DIK_B;
	m_keybinds[characterActionCastSleep] = DIK_Z;

	m_keybinds[characterActionCastAbility1] = DIK_Q;
	m_keybinds[characterActionCastAbility2] = DIK_W;
	m_keybinds[characterActionCastAbility3] = DIK_E;
	m_keybinds[characterActionCastAbility4] = DIK_R;
	m_keybinds[characterActionCastAbility5] = DIK_T;
	m_keybinds[characterActionCastAbility6] = DIK_F;

	m_keybinds[characterActionInventory1] = DIK_1;
	m_keybinds[characterActionInventory2] = DIK_2;
	m_keybinds[characterActionInventory3] = DIK_3;
	m_keybinds[characterActionInventory4] = DIK_4;
	m_keybinds[characterActionInventory5] = DIK_5;
	m_keybinds[characterActionInventory6] = DIK_6;
	m_keybinds[characterActionInventory7] = DIK_7;
	m_keybinds[characterActionInventory8] = DIK_8;
	m_keybinds[characterActionInventory9] = DIK_9;
	m_keybinds[characterActionInventory0] = DIK_0;


	m_spamFlags.resize(characterActionCount, false);

	m_spamFlags[characterActionKeyMoveLeft] = true;
	m_spamFlags[characterActionKeyMoveRight] = true;
	m_spamFlags[characterActionKeyMoveUp] = true;
	m_spamFlags[characterActionKeyMoveDown] = true;

	m_spamFlags[characterActionSelectWithMouse] = true;
	m_spamFlags[characterActionWalkOrBasicAttack] = true;

	m_spamFlags[characterActionAttackMove] = true;
	m_spamFlags[characterActionDriveByMove] = true;


	//State inits

	//m_actionsforState.resize(actorStateCount);

	vector<int> full
	{
		characterActionKeyMoveLeft,
		characterActionKeyMoveRight,
		characterActionKeyMoveUp,
		characterActionKeyMoveDown,

		characterActionSelectWithMouse,
		characterActionWalkOrBasicAttack,

		characterActionStop,
		characterActionAttackMove,
		characterActionDriveByMove,

		characterActionCastRecall,
		characterActionCastSleep,

		characterActionCastAbility1,
		characterActionCastAbility2,
		characterActionCastAbility3,
		characterActionCastAbility4,
		characterActionCastAbility5,
		characterActionCastAbility6,

		characterActionInventory1,
		characterActionInventory2,
		characterActionInventory3,
		characterActionInventory4,
		characterActionInventory5,
		characterActionInventory6,
		characterActionInventory7,
		characterActionInventory8,
		characterActionInventory9,
		characterActionInventory0
	};

	m_actionsforState.resize(actorStateCount);
	m_actionsforState.at(actorRecall) = full;
	m_actionsforState.at(actorCasting) = full;
	m_actionsforState.at(actorBasicAttack) = full;
	m_actionsforState.at(actorStationary) = full;
	m_actionsforState.at(actorWalking) = full;
	m_actionsforState.at(actorWalkToBasicTarget) = full;
	m_actionsforState.at(actorDirectionalCast) = full;
	m_actionsforState.at(actorInstantCast) = full;
	m_actionsforState.at(actorPointCast) = full;
	m_actionsforState.at(actorSingleTargetCast) = full;
	m_actionsforState.at(actorAttackMoveCast) = full;
	m_actionsforState.at(actorDriveByCast) = full;


	vector<int> disabled
	{
		characterActionSelectWithMouse
	};

	m_actionsforState.at(actorSleeping) = disabled;
	m_actionsforState.at(actorUnspawned) = disabled;
	m_actionsforState.at(actorDead) = disabled;

	return true;
}

CharacterInputModel::~CharacterInputModel() {}