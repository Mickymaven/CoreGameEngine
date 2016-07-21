#if !defined(UIAREA_H)
#define UIAREA_H

#include <vector>
using std::vector;

#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineMoba/src/VitalEffect/Buff.h"

#include "../Application/Globals.h"
#include "UIButton.h"
#include "UIElement.h"
#include "UICheckBox.h"

class UIArea
{
protected:
	LMVector3 * m_positions;
	int m_arraySize;
	LMVector2 m_size;
	RECT m_bounds;

public:
	UIArea();
	~UIArea();

	bool IsCursorPointInBounds();
	bool IsPointInBounds(POINT * p);

	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);
	virtual bool MouseOver(POINT * p);

	void SetBounds(long left, long top, long right, long bottom);
	
	void BehaviorOnFirstHit(float width, float height, vector<UICheckBox *> * vec, int enumIndex);
	bool Test(float x, float y, float width, float height, unsigned int index, int enumIndex);
	void BehaviorOnFirstHit(float width, float height, vector<LMVector3 *> * vec, int enumIndex);
	void BehaviorOnFirstHit(vector<Buff*> * vec, int enumIndex);	
	void BehaviorOnFirstHit(float width, float height, LMVector3 * posArray, int arraySize, int enumIndex);
	void BehaviorOnFirstHit(UIElement * posArray, int arraySize, int enumIndex);
	virtual void ImplementBehavior(int index, int enumIndex);
};

#endif