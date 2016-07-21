#if !defined(UILAYOUTABILITY_H)
#define UILAYOUTABILITY_H

#include <functional>
using namespace std::placeholders;

#include "../../../EngineGameModel/src/Maths/LMVector4.h"
#include "../../../EngineMoba/src/Ability/Ability.h"
#include "../UI/Tooltips/TooltipInfo.h"
#include "../GameplayView/AbilityView.h"

#include "UILayoutBase.h"

class UILayoutAbility : public UILayoutBase
{
private:
	Ability * m_ability;
	AbilityView * m_abilityView;
	std::function<void(RECT * bounds, TooltipInfo * tooltipInfo, Ability * ability)> m_mouseOverCallback;

public:
	UILayoutAbility();
	UILayoutAbility(Ability * ability);
	~UILayoutAbility();

	void Update(float deltaTime);
	void Render();
	void RenderAtPosition(float x, float y, float z);

	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);
	virtual bool MouseOver(POINT * p);
	bool MouseOverCallBackWithBounds(RECT * bounds);

	Ability * GetAbility();
	AbilityView * GetAbilityView();

	void SetMouseOverCallback(std::function<void(RECT * bounds, TooltipInfo * tooltipInf, Ability * ability)> f);

	void SetAbility(Ability * ability);
	void SetAbilityView(AbilityView * abilityView);

};

#endif