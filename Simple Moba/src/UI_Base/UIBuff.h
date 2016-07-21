#if!defined(UIBUFF_H)
#define UIBUFF_H

#include <functional>
using namespace std::placeholders;

#include "../../../EngineGameModel/src/Maths/LMVector4.h"
#include "../../../EngineMoba/src/VitalEffect/Buff.h"

#include "UILayoutBase.h"


#include "../UI/Tooltips/TooltipInfo.h"
#include "../GameplayView/BuffView.h"



class UIBuff : public UILayoutBase
{
private:
	Buff * m_buff;
	BuffView * m_buffView;
	std::function<void(RECT * bounds, TooltipInfo * tooltipInfo)> m_mouseOverCallback;

public:
	UIBuff();
	//init with copy
	~UIBuff();

	void Update(float deltaTime);
	void Render();
	void RenderAtPosition(float x, float y, float z);

	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);
	virtual bool MouseOver(POINT * p);
	bool MouseOverCallBackWithBounds(RECT * bounds);

	Buff * GetBuff();
	BuffView * GetBuffView();

	void SetMouseOverCallback(std::function<void(RECT * bounds, TooltipInfo * tooltipInfo)> f);

	void SetBuff(Buff * buff);
	void SetBuffView(BuffView * buffView);
};

#endif