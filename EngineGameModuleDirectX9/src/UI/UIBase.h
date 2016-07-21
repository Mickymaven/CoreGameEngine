#if !defined(UIBASE_H)
#define UIBASE_H

#include <Windows.h>
#include "../../../EngineGameModel/src/Maths/LMVector3.h"

class UIBase
{
protected:
	float m_width;
	float m_height;
	LMVector3 m_position;
	RECT m_bounds;

public:
	UIBase();
	~UIBase();

	virtual void Render();

	LMVector3 * GetPosition();
	RECT * GetBounds();
	float GetWidth();
	float GetHeight();


	void SetPosition(LMVector3 * position);
	virtual void SetPosition(float x, float y, float z);

	void SetBounds(long left, long top, long right, long bottom);
	void SetWidth(float width);
	void SetHeight(float height);
	
	bool IsPointInBounds(POINT * p);

	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);

};

#endif