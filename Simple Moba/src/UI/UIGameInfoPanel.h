#if !defined(UIGAMEINFOPANEL_H)
#define UIGAMENFOPANEL_H

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "../GameplayView/PlayerCharacterView.h"
#include "../UI_Base/UILayoutAvatar.h"
#include "InfoPanel.h"
#include "UIPanelBase.h"
#include "../Input/Model/CameraInputModel.h"


class UIGameInfoPanel : public UIPanelBase
{
protected:


	UIElement m_tempAv;

	
	static const int elementIDs[];

	InfoPanel m_infoPanel;

	vector<UILayoutAvatar> m_LayoutAvatars;


	vector<vector<PlayerCharacterController*>*> * m_controllers;
	int m_teamCount;

	vector<vector<UILayoutAvatar*>> m_LayoutAvatarsByTeam;
	//vector<vector<PlayerCharacterController*>> * m_controllers;

	//clock vars
	char m_clockBuff[10];
	RECT m_fontPos;
	float MyMinutes;
	float MySeconds;


public:
	UIGameInfoPanel();
	~UIGameInfoPanel();

	bool Init(ViewProfile * viewProfile, ThemeResources * themeResources,
		MobaState * gameState, TooltipController * tooltipController,
		PlayerCharacterController * initCharControl, vector<InputModel*> * inputModels, vector<ItemView> * itemViews);

	void SetControllers();


	void Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView);
	void Render();


	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	InfoPanel * GetInfoPanel();

};


#endif