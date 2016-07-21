#if !defined (VERTEX_H)
#define VERTEX_H

#include <minwindef.h>

struct Vertex // Vertex stucture.
{
	FLOAT x, y, z;
	DWORD color;
	FLOAT tu, tv;
};

#endif
