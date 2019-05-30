#if !defined (UICHARACTERPANELMINI_H)
#define UICHARACTERPANELMINI_H

#include "UICharacterPanel.h"

class UICharacterPanelMini : public UICharacterPanel
{
private:



public:
	UICharacterPanelMini();
	~UICharacterPanelMini();


	bool Init(
		ViewProfile * viewProfile,
		ThemeResources * themeResources,
		MobaState * gameState,
		vector<InputModel*> * inputModels,
		PlayerCharacterController * initCharControl);



	void Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView);
	void Render();

};


#endif