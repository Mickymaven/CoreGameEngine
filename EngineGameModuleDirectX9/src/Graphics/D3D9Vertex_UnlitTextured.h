#if !defined(D3D9VERTEX_UNLITTEXTURED_H)
#define D3D9VERTEX_UNLITTEXTURED_H

#include <d3dx9.h>

struct D3D9Vertex_UnlitTextured
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	FLOAT tu, tv;

	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
};

#endif