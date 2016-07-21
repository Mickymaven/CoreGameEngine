#if !defined(LMGEOMETRY_H)
#define LMGEOMETRY_H

#include <d3dx9.h>

#include "../View/LMCamera.h"
#include "../../../EngineGameModel/src/Maths/LMVector3.h"


#include "../Graphics/D3DFVF_D3DVertex.h"
#include "../Graphics/Vertex.h"


//const DWORD D3D9Vertex_UnlitTextured::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

//Poss get a Vec3 inherit D3dxvector3 and add some functions

//extern D3DXVECTOR3 BarycentricToD3DXVECTOR3(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, float u, float v);

inline D3DXVECTOR3 BarycentricToD3DXVECTOR3(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, float u, float v)
{
	//V1 + U(V2 - V1) + V(V3 - V1).
	D3DXVECTOR3 result = v0 + u * (v1 - v0) + v * (v2 - v0);
	return result;
}


inline void LMGeometryUnitVector(D3DXVECTOR3 * out, D3DXVECTOR3 * origin, D3DXVECTOR3 * target)
{
	out->x = target->x - origin->x;
	out->y = target->y - origin->y;
	out->z = target->z - origin->z;

	D3DXVec3Normalize(out, out);

}



inline float LMHypotenuseLength2D(D3DXVECTOR3 * point1, D3DXVECTOR3 * point2)
{

	float x = abs(point2->x - point1->x);
	float z = abs(point2->z - point1->z);

	return sqrt(x*x + z*z);
}

inline bool LMRangeExceedsDisplacement(D3DXVECTOR3 * point1, D3DXVECTOR3 * point2, float range)
{
	float x = abs(point2->x - point1->x);
	float z = abs(point2->z - point1->z);

	if (range*range > (x*x + z*z)) return true;

	return false;

}



#endif