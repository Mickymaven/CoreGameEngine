#if !defined(UILABELCSTR_H)
#define UILABELCSTR_H

#include <d3dx9.h>

#include "UIBase.h"
#include "FontGroup.h"

#include <cstdio>

class UILabelCstr : public UIBase
{
protected:
	static const int m_size=20;
	char m_cstr[m_size];

	char m_formatf[6];

	LPD3DXFONT m_font;
	D3DCOLOR * m_color;
	DWORD * m_format;

public:
	UILabelCstr();
	~UILabelCstr();

	bool Init(const RECT & rect, FontGroup * fontGroup);

	virtual void Render();

	void Select(POINT * p);
	void AltSelect(POINT * p);

	char * GetText();

	void SetText(const char * text);
	void SetText(int i);
	virtual void SetText(float f);

	void SetColor(D3DCOLOR * color);

	void SetFloatFormat(int whole, int remainder);

};

#endif