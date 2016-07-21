#if !defined(PLAYERACTIONENUM_H)
#define PLAYERACTIONENUM_H


enum PlayerAction
{
	actionUNUSEDACTION,
	actionCastAbility1,
	actionCastAbility2,
	actionCastAbility3,
	actionCastAbility4,
	actionCastAbility5,
	actionCastAbility6,
	actionCastRecall,
	actionCastSleep,
	actionSelectWithMouse,//usually left click
	actionCameraPanModifier,
	actionWalkOrBasicAttack, //usually right click
	actionStop,
	actionAttackMove,
	actionDriveByMove,
	actionInventory1,
	actionInventory2,
	actionInventory3,
	actionInventory4,
	actionInventory5,
	actionInventory6,
	actionInventory7,
	actionInventory8,
	actionInventory9,
	actionInventory0,
	actionToggleCameraLock,
	actionCentreCamera,
	actionToggleFreeCamera,//not a game feature
	actionToggleGameMenu,
	actionToggleShopMenu,
	actionCameraFocusPlayer1,
	actionCameraFocusPlayer2,
	actionCameraFocusPlayer3,
	actionCameraFocusPlayer4,
	actionCameraFocusPlayer5,
	actionCameraFocusPlayer6,
	actionCameraFocusPlayer7,
	actionCameraFocusPlayer8,
	actionCameraFocusPlayer9,
	actionCameraFocusPlayer10,
	actionCameraFocusPlayer11,
	actionCameraFocusPlayer12,
	actionZoomOutLockCamera,
	actionZoomInLockCamera,
	actionKeyMoveLeft,
	actionKeyMoveRight,
	actionKeyMoveUp,
	actionKeyMoveDown,
	actionCycleDebugUI,
	actionTeleportToMouse,
	actionTogglePathEnabled,
	playerActionCount

};

#endif