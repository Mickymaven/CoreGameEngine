#if !defined(UILAYOUTGROUP_H)
#define UILAYOUTGROUP_H

#include <vector>
using std::vector;

#include <Windows.h>

#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "../../../EngineGameModel/src/Maths/LMVector4.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIBase.h"

struct UILayoutGroup
{
public:
	vector<UIBase*> m_pVector;

	UILayoutGroup();
	~UILayoutGroup();

	void PositionItems(
		LMVector4 * bounds,
		float width, float height,
		float xSpace, float ySpace);
};

#endif