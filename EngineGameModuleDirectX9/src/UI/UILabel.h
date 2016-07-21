#if !defined(UILABEL_H)
#define UILABEL_H

#include <string>
using std::string;

#include <d3dx9.h>

#include "UIBase.h"
#include "FontGroup.h"

class UILabel : public UIBase
{
protected:
	const string * m_text;

	LPD3DXFONT m_font;
	D3DCOLOR * m_color;
	DWORD * m_format;

public:
	UILabel();
	~UILabel();

	bool Init(const RECT & rect, FontGroup * fontGroup, string * text);

	void Render();

	void SetText(string * text);

	void Select(POINT * p);
	void AltSelect(POINT * p);

};


#endif