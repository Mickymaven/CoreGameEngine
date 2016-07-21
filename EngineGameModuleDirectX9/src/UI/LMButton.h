#if !defined(LMBUTTON_H)
#define LMBUTTON_H

#include <string>
using namespace std;

#include <d3dx9.h>

#include "../Application/Globals.h"
#include "../ControlHeader.h"

class LMButton
{
private:
	static LPD3DXFONT m_uxFont2;
	static D3DXCOLOR m_color;

	char * m_labelText;

	POINT m_position;
	POINT m_dimensions;
	RECT m_hitarea;


	LPD3DXLINE m_line;

	D3DXVECTOR2 m_leftVerts[2];
	D3DXVECTOR2 m_topVerts[2];
	D3DXVECTOR2 m_rightVerts[2];
	D3DXVECTOR2 m_bottomVerts[2];
	D3DXVECTOR2 * m_lines[4];

public:
	LMButton();
	~LMButton();
	bool Init(POINT * pos, POINT * dim, string text);
	void Render();

	bool IsHit(float x, float y);

};

#endif