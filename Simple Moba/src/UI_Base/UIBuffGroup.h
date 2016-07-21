#if !defined(UIBUFFGROUP_H)
#define UIBUFFGROUP_H

#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "UILayoutGroup.h"
#include "UIBuff.h"

struct UIBuffGroup : public UILayoutGroup
{
public:
	vector<UIBuff> m_buffs;
	vector<BuffView> * m_buffViews;

	UIBuffGroup();
	~UIBuffGroup();

	bool Init(vector<BuffView> * buffViews);

	void SetBuffs(vector<Buff *> * buffs);

	void Update(float deltaTime);
	void Render();

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

};

#endif