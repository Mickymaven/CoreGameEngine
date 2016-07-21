#if !defined(FONTGROUP_H)
#define FONTGROUP_H

#include <d3dx9core.h>

struct FontGroup
{
public:
	LPD3DXFONT m_font;
	D3DCOLOR m_color;
	DWORD m_format;
};

#endif