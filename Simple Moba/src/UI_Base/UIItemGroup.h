#if !defined(UIITEMGROUP_H)
#define UIITEMGROUP_H

#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "UILayoutGroup.h"
#include "UIBuff.h"

struct UIItemGroup : public UILayoutGroup
{
public:
	vector<UIBuff> m_buffs;
	vector<ItemView> * m_buffViews;

	UIItemGroup();
	~UIItemGroup();

	bool Init(vector<ItemView> * buffViews);

	void SetBuffs(vector<Buff *> * buffs);

	void Update(float deltaTime);
	void Render();

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

};

#endif#pragma once
