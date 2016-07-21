#if!defined(UILAYOUTITEMCLONE_H)
#define UILAYOUTITEMCLONE_H

#include "../../../EngineGameModel/src/Maths/LMVector4.h"
#include "../../../EngineMoba/src/Item/Item.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIBase.h"

#include "UILayoutItem.h"

class UILayoutItemClone : public UIBase
{
protected:
	UILayoutItem * m_item;

public:
	UILayoutItemClone();
	~UILayoutItemClone();

	void Render();

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	UILayoutItem * GetUILayoutItem();

	void SetUILayoutItem(UILayoutItem * item);
};

#endif