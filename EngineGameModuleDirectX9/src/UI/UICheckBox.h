#if !defined(UICHECKBOX_H)
#define UICHECKBOX_H

#include "UIElement.h"

class UICheckBox : public UIElement
{
private:

	static float m_width;
	static float m_height;

	bool m_state;

	static LPDIRECT3DTEXTURE9 m_checked;
	static LPDIRECT3DTEXTURE9 m_unchecked;

public:
	UICheckBox();
	UICheckBox(bool checked, float width, float height);
	~UICheckBox();

	bool Init();

	void Render();

	bool GetIsChecked();

	bool Cycle();

	void SetChecked();
	void SetUnchecked();


	static float GetWidth();
	static float GetHeight();

	void Select(POINT * p);
	void AltSelect(POINT * p);

};


#endif