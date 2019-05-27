#if !defined(GRAPHICSALGORITHMS_H)
#define GRAPHICSALGORITHMS_H

#include <vector>
using std::vector;

#include "../../../EngineGamePlatform/src/Application/Globals.h"
#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h"

#include "../../../EngineGameModuleDirectX9/src/Graphics/LMMesh.h"
#include "../../../EngineGameModuleDirectX9/src/View/LMCamera.h"
#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineGameModuleDirectX9/src/UI/LMGeometry.h"
#include "../../../EngineGameModuleDirectX9/src/Graphics/D3D9Vertex_UnlitTextured.h"

extern D3DXVECTOR3 rayPoint1, rayPoint2;


inline void GetRayFromLMCamera(LMCamera * camera, int x, int y, D3DXVECTOR3 & point1, D3DXVECTOR3 & point2)
{
	float dx, dy;

	GetClientRect(g_hwnd, g_clientSizeRect);

	float farDist = camera->GetFarPlane();
	float nearDist = camera->GetNearPlane();
	float fov = camera->GetFOV();
	float aspect = camera->GetAspectRatio();

	dx = tanf(fov * 0.5f) * ((x / (g_clientSizeRect->right *0.5f) - 1.0f) * aspect);
	dy = tanf(fov * 0.5f) * (1.0f - y / (g_clientSizeRect->bottom*0.5f));

	//Calculating the End Points of the Ray

	point1 = D3DXVECTOR3(dx*nearDist, dy*nearDist, nearDist);
	point2 = D3DXVECTOR3(dx*farDist, dy*farDist, farDist);

	//Generating an Inverse of the View Matrix

	D3DXMATRIX tempViewMatrix;
	D3DXMATRIX tempWorldMatrix;
	D3DXMATRIX inverseMatrix;

	g_D3D_Device->GetTransform(D3DTS_VIEW, &tempViewMatrix);

	float determinantV = D3DXMatrixDeterminant(&tempViewMatrix);

	D3DXMatrixInverse(&inverseMatrix, &determinantV, &tempViewMatrix);

	D3DXVec3Normalize(&point2, &point2);
	point2 *= 1000000.0f;

	D3DXVec3TransformCoord(&point1, &point1, &inverseMatrix);
	D3DXVec3TransformCoord(&point2, &point2, &inverseMatrix);
}

inline void TransformRayByMeshWorldMatrix(D3DXVECTOR3 * point1, D3DXVECTOR3 * point2, D3DXMATRIX * meshWorldMatrix)
{
	D3DXMATRIX inverseMatrix;
	
	D3DXMatrixInverse(&inverseMatrix, NULL, meshWorldMatrix);
	D3DXVec3TransformCoord(point1, point1, &inverseMatrix);
	D3DXVec3TransformCoord(point2, point2, &inverseMatrix);
}

inline void ConvertRayToScreenCoords(LMCamera * camera, LMVector3 * hpbarposition, LMVector2 * position, int i)
{

	char ibuffer[5000];
	sprintf_s(ibuffer, "");
	//screen width x
	//screen height y

	//camera position
	//view matrix
	//projection matrix
	//look at

	//target position

	GetClientRect(g_hwnd, g_clientSizeRect);

	float farDist = camera->GetFarPlane();
	float nearDist = camera->GetNearPlane();
	float fov = camera->GetFOV();
	float aspect = camera->GetAspectRatio();


	rayPoint1 = D3DXVECTOR3(*camera->GetPosition());
	rayPoint2 = D3DXVECTOR3(hpbarposition->x, hpbarposition->y, hpbarposition->z);
	rayPoint2.y += 1.9f;
	
	//float dx, dy;
	//float x, y; //the goal


	D3DXMATRIX tempViewMatrix;
	D3DXMATRIX tempWorldMatrix;
	D3DXMATRIX inverseMatrix;

	//two points in world space
	
	//if (i == 1){ sprintf_s(ibuffer, "point 2 x:%f ,y: %f, z:%f \n", point2.x, point2.y, point2.z); OutputDebugString(ibuffer); }


	
	g_D3D_Device->GetTransform(D3DTS_VIEW, &tempViewMatrix);
	
	//float determinantV = D3DXMatrixDeterminant(&tempViewMatrix); //usually 1.0f

	//D3DXMatrixInverse(&inverseMatrix, &determinantV, &tempViewMatrix);

	//D3DXVec3Normalize(point2, point2);
	//*point2 *= 1000000.0f;


	D3DXVec3TransformCoord(&rayPoint1, &rayPoint1, &tempViewMatrix);
	D3DXVec3TransformCoord(&rayPoint2, &rayPoint2, &tempViewMatrix);

	rayPoint2 *= 1000000.0f;

	D3DXVec3Normalize(&rayPoint2, &rayPoint2);

	
		
	rayPoint2.x *= (1.0f + 0.5f* (fov / D3DX_PI)) / aspect;
	rayPoint2.y *= (1.0f + 0.5f* (fov / D3DX_PI));

	// rayPoint2.x = (((rayPoint2.x / tanf(fov * 0.5f)) * aspect) + 1.0f) * (g_clientSizeRect->right * 0.5f);
	// rayPoint2.y = ((rayPoint2.y / tanf(fov * 0.5f)) - 1.0f) / (-1.0f / (g_clientSizeRect->bottom * 0.5f));

	rayPoint2.x = (((rayPoint2.x / tanf(fov * 0.5f)) ) + 1.0f) * (g_clientSizeRect->right * 0.5f);
	rayPoint2.y = ((rayPoint2.y / tanf(fov * 0.5f)) - 1.0f) / (-1.0f / (g_clientSizeRect->bottom * 0.5f));
	
	position->x = rayPoint2.x;
	position->y = rayPoint2.y;

	//if (i == 1) { sprintf_s(ibuffer, "FINAL pos x: %f, y: %f  \n", position.x, position.y); OutputDebugString(ibuffer); }


	//part 1 solve for dx ////////////////////////////////
	
	
	//point1 = D3DXVECTOR3(dx*nearDist, dy*nearDist, nearDist);
	//point2 = D3DXVECTOR3(dx*farDist, dy*farDist, farDist);

	
	//1

	//x = dx*nearDist
	//2
	//dx = point1.x / nearDist;
	//or
	//dx = point1.x2 / farDist;


	//and also
	//dy = point1.y / nearDist;

	//if (i == 1) sprintf_s(ibuffer, "dx:%f ,dy:%f \n", dx, dy); OutputDebugString(ibuffer);

	//part 2 solve for x ////////////////////////////////////////////

	//1 (start)
	//dx = tanf(fov * 0.5f) * ((x / ( g_clientSizeRect.right * 0.5f ) - 1.0f) / aspect);

	//2
	//dx / tanf(fov * 0.5f) = (x / (g_clientSizeRect.right * 0.5f) - 1.0f) / aspect;

	//3
	//((dx / tanf(fov * 0.5f)) * aspect) = x / (g_clientSizeRect.right * 0.5f) - 1.0f;

	//4
	//( ((dx / tanf(fov * 0.5f)) * aspect) + 1.0f ) = x / (g_clientSizeRect.right * 0.5f);

	//5 FINAL
	//x = (((dx / tanf(fov * 0.5f)) * aspect) + 1.0f) * (g_clientSizeRect.right * 0.5f);


	//part 3 solve for y
	//1 start
	//dy = tanf(fov * 0.5f) * (1.0f - y / (g_clientSizeRect.bottom*0.5f));

	//2
	//(dy / tanf(fov * 0.5f)) = 1.0f - y / (g_clientSizeRect.bottom*0.5f)
	
	//3
	//(dy / tanf(fov * 0.5f)) = ( ( -1.0f / (g_clientSizeRect.bottom*0.5f) ) * y) +1.0f

	//4
	//(dy / tanf(fov * 0.5f)) - 1.0f = (-1.0f / (g_clientSizeRect.bottom*0.5f)) * y

	//5 final
	//y = ((dy / tanf(fov * 0.5f)) - 1.0f) / (-1.0f / (g_clientSizeRect.bottom*0.5f));


	//screen percentage x
	//screen percentage y

	// into

	//screen x
	//screen y
	//if (i == 1) { sprintf_s(ibuffer, "x:%f ,y:%f \n", x, y); OutputDebugString(ibuffer); }
 

	//position.x = x;
	//position.y = y;
}

/*
inline bool IsIntersectSprite(vector<LMVector3> *hitPoints, LMMesh * mesh, D3DXVECTOR3 point1, D3DXVECTOR3 point2)
{
	BOOL isIntersect = false;

	DWORD faceIndex = -1;
	float u = 0.0f;
	float v = 0.0f;
	float dist = 0.0f;

	//later
	LPD3DXBUFFER AllHits;
	DWORD CountOfHits;

	//D3DXIntersect(pMesh, pRayPos, pRayDir, pHit, pFaceIndex, pU, pV, pDist, ppAllHits, pDCountOfHits);

	D3DXIntersect(mesh->GetMesh(), &point1, &point2,
		&isIntersect, &faceIndex, &u, &v, &dist, &AllHits,
		&CountOfHits);


	float resultX = point2.x - point1.x;
	float resultY = point2.y - point1.y;
	float resultZ = point2.z - point1.z;
	float result = sqrt(abs(resultX*resultX + resultY*resultY + resultZ*resultZ));
	
	//char gbuffer100[100];

	//sprintf_s(gbuffer100, "Length of ray: %f..", result);
	//OutputDebugString(gbuffer100);

	//sprintf_s(gbuffer100, "CountOfHits: %i \n", CountOfHits);
	//OutputDebugString(gbuffer100);

	

	if (isIntersect)
	{
		
		WORD * pI = mesh->GetIndiceBuffer();
		D3D9Vertex_UnlitTextured * pV = mesh->GetVertexBuffer();

		DWORD thisfaceIndex = -1;
		float thisU = -1;
		float thisV = -1;
		unsigned long bufferSize = AllHits->GetBufferSize();
		D3DXINTERSECTINFO * intersectInfo = ((D3DXINTERSECTINFO*)AllHits->GetBufferPointer());
		
		hitPoints->reserve(hitPoints->size() + CountOfHits);

		for (unsigned long index = 0; index < CountOfHits; index++)
		{
			thisfaceIndex = intersectInfo->FaceIndex;
			thisU = intersectInfo->U;
			thisV = intersectInfo->V;
			
			D3D9Vertex_UnlitTextured * vertex0 = &pV[pI[3 * thisfaceIndex + 0]];
			D3D9Vertex_UnlitTextured * vertex1 = &pV[pI[3 * thisfaceIndex + 1]];
			D3D9Vertex_UnlitTextured * vertex2 = &pV[pI[3 * thisfaceIndex + 2]];

			D3DXVECTOR3 a = vertex0->position - vertex1->position;
			D3DXVECTOR3 b = vertex2->position - vertex1->position;

			D3DXVECTOR3 out;
			D3DXVec3Cross(&out, &a, &b);
			out /= D3DXVec3Length(&out);

			D3DXVECTOR3 actorLocation = BarycentricToD3DXVECTOR3
				(vertex0->position, vertex1->position, vertex2->position, thisU, thisV);

			D3DXMATRIX matView, matProj;

			D3DXMATRIX matWorld = D3DXMATRIX(
				1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0);
			//g_D3D_Device.GetTransform(D3DTS_VIEW, &matView);
			//g_D3D_Device.GetTransform(D3DTS_PROJECTION, &matProj);

			D3DXVECTOR4 temp = D3DXVECTOR4(actorLocation.x, actorLocation.y, actorLocation.z, 0.0f);

			D3DXVec4Transform(&temp, &temp, &matWorld);

			hitPoints->push_back(LMVector3(temp.x, temp.y, temp.z));

			//sprintf_s(gbuffer100, "Intersect dist: %f..", intersectInfo.Dist);
			//OutputDebugString(gbuffer100);
			
			intersectInfo++;
		}
		
	}

	return isIntersect;
}
*/

inline bool PickFromSprite(D3DXVECTOR4*ResultPoint, LMMesh * mesh, D3DXVECTOR3 point1, D3DXVECTOR3 point2)
{
	//PhysicsObject * p = sprite.GetPhysicsObject();
	BOOL isIntersect = false;

	DWORD faceIndex = -1;
	float u = 0.0f;
	float v = 0.0f;
	float dist = 0.0f;

	//later
	LPD3DXBUFFER AllHits;
	DWORD CountOfHits;

	//D3DXIntersect(pMesh, pRayPos, pRayDir, pHit, pFaceIndex, pU, pV, pDist, ppAllHits, pDCountOfHits);

	D3DXIntersect(mesh->GetMesh(), &point1, &point2,
		&isIntersect, &faceIndex, &u, &v, &dist, &AllHits,
		&CountOfHits);

	if (isIntersect)
	{
		WORD * pI = mesh->GetIndiceBuffer();
		D3D9Vertex_UnlitTextured * pV = mesh->GetVertexBuffer();

		//idea and source code is from
		//from https://code.google.com/p/gamecode4/source/browse/trunk/Source/GCC4/Graphics3D/Raycast.cpp

		D3D9Vertex_UnlitTextured * vertex0 = &pV[pI[3 * faceIndex + 0]];
		D3D9Vertex_UnlitTextured * vertex1 = &pV[pI[3 * faceIndex + 1]];
		D3D9Vertex_UnlitTextured * vertex2 = &pV[pI[3 * faceIndex + 2]];

		/*
		FLOAT dtu1 = vertex1.tu - vertex0.tu;
		FLOAT dtu2 = vertex2.tu - vertex0.tu;
		FLOAT dtv1 = vertex1.tv - vertex0.tv;
		FLOAT dtv2 = vertex2.tv - vertex0.tv;

		FLOAT tu = vertex0.tu + u * dtu1 + v *dtu2;
		FLOAT tv = vertex0.tv + u * dtv1 + v *dtv2;
		*/

		D3DXVECTOR3 a = vertex0->position - vertex1->position;
		D3DXVECTOR3 b = vertex2->position - vertex1->position;

		D3DXVECTOR3 out;
		D3DXVec3Cross(&out, &a, &b);
		out /= D3DXVec3Length(&out);

		D3DXVECTOR3 actorLocation = BarycentricToD3DXVECTOR3
			(vertex0->position, vertex1->position, vertex2->position, u, v);

		D3DXMATRIX matView, matProj;

		D3DXMATRIX matWorld = D3DXMATRIX(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);
		g_D3D_Device->GetTransform(D3DTS_VIEW, &matView);
		g_D3D_Device->GetTransform(D3DTS_PROJECTION, &matProj);

		//D3DXMATRIX matWorld
		//D3DXMATRIX matScale;
		//D3DXMATRIX matRotation;
		//D3DXMATRIX matTranslation;

		//D3DXMatrixScaling(&matScale, p.GetScale().x, p.GetScale().y, p.GetScale().z);
		//D3DXMatrixRotationYawPitchRoll(&matRotation, p.GetRotation().x, p.GetRotation().y, p.GetRotation().z);
		//D3DXMatrixTranslation(&matTranslation, p.GetPosition().x, p.GetPosition().y, p.GetPosition().z);

		//matWorld = matScale * matRotation * matTranslation;

		D3DXVECTOR4 temp = D3DXVECTOR4(actorLocation.x, actorLocation.y, actorLocation.z, 0.0f);

		//D3DXVECTOR4 * GoToIntersectPoint = new D3DXVECTOR4();

		*ResultPoint = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		D3DXVec4Transform(ResultPoint, &temp, &matWorld);
		//char buffer[1000];
		
		//sprintf_s(buffer, "result x: %f \n", GoToIntersectPoint.x);
		//OutputDebugString(buffer);
		//sprintf_s(buffer, "result y: %f \n", GoToIntersectPoint.y);
		//OutputDebugString(buffer);
		//sprintf_s(buffer, "result z: %f \n", GoToIntersectPoint.z);
		//OutputDebugString(buffer);

		//D3DXVECTOR3 temp3422(GoToIntersectPoint);
		
	

		return true;


	}

	return false;
}



#endif