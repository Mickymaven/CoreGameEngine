#if !defined (UILAYOUTAVATAR_H)
#define UILAYOUTAVATAR_H

#include "UILayoutBase.h"

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
//#include "../GameplayView/PlayerCharacterView.h"

class UILayoutAvatar : public UILayoutBase
{
protected:
	
	PlayerCharacterController * m_pcController;
	//PlayerCharacterView * m_pcView;
	//std::function<void(RECT * bounds, TooltipInfo * tooltipInfo, PlayerCharacterView * pcView)> m_mouseOverCallback;

public:
	UILayoutAvatar();
	~UILayoutAvatar();

	void Update(float deltaTime);
	void Render();
	void RenderAtPosition(float x, float y, float z);


	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	bool MouseOverCallBackWithBounds(RECT * bounds);

	void SetPlayerCharacter(PlayerCharacterController * pcController);
	//void SetPlayerCharacterView(PlayerCharacterView * pcView);

	PlayerCharacterController * GetPlayerCharacter();


};

#endif


