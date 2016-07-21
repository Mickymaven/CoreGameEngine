#include "SpriteView.h"

LPDIRECT3DDEVICE9 SpriteView::m_D3D_Device;

SpriteView::SpriteView()
{

}

SpriteView::SpriteView(LPDIRECT3DDEVICE9 device, Sprite * sprite, LMMesh * mesh)
{
	m_D3D_Device = device;
	m_sprite = sprite;//model
	m_mesh = mesh;


	// read vector pointers
	m_pPosition = m_sprite->GetPhysicsObject()->GetPosition();
	m_pRotation = m_sprite->GetPhysicsObject()->GetRotation();
	m_pScale = m_sprite->GetPhysicsObject()->GetScale();
}

SpriteView::~SpriteView()
{

}

void SpriteView::WorldTransform()
{
	// Set the rotation value to the matrix.
	D3DXMatrixScaling(&m_scaleMatrix, m_pScale->x, m_pScale->y, m_pScale->z);
	D3DXMatrixRotationYawPitchRoll(&m_rotationMatrix, m_pRotation->y, m_pRotation->x, m_pRotation->z);
	D3DXMatrixTranslation(&m_translationMatrix, m_pPosition->x, m_pPosition->y, m_pPosition->z);

	m_worldMatrix = m_scaleMatrix * m_rotationMatrix * m_translationMatrix;

}

void SpriteView::Render()
{
	WorldTransform();

	// Set the matrix.
	m_D3D_Device->SetTransform(D3DTS_WORLD, &m_worldMatrix);

	// Loop through all materials and draw each part of the model.

	for (DWORD i = 0; i < m_mesh->GetMaterialCount(); i++)
	{
		m_D3D_Device->SetMaterial(m_mesh->GetMaterial(i));

		if (m_mesh->GetTexture(i) != NULL)
			m_D3D_Device->SetTexture(0, m_mesh->GetTexture(i));
		else m_D3D_Device->SetTexture(0, NULL);

		m_mesh->GetMesh()->DrawSubset(i);
	}
}

bool SpriteView::IntersectPoints(vector<LMVector3> * pPointsOut, LMVector3 * point1In, LMVector3 * point2In)
{

	D3DXVECTOR3 point1;
	point1.x = point1In->x;
	point1.y = 1.0f;
	point1.z = point1In->z;

	D3DXVECTOR3 point2;
	point1.x = point2In->x;
	point1.y = 1.0f;
	point1.z = point2In->z;


	//Point 2 will be our direction
	D3DXVECTOR3 dir = D3DXVECTOR3(
		point2.x - point1.x,
		point2.y - point1.y,
		point2.z - point1.z);

	//was point2.x -= point1.x; point2.y -= point1.y; point2.z -= point1.z;

	TransformRayByMeshWorldMatrix(&point1, &dir, &m_worldMatrix);

	vector<LMVector3> tempPoints;
	//Result = NULL;

	bool found = false;

	if (IsIntersectSprite(&tempPoints, point1, dir))
	{
		for (unsigned int i = 0; i < tempPoints.size(); i++)
		{
			if (tempPoints.at(i).IsInRegion((LMVector3*)&point1, (LMVector3*)&point2))
			{
				if (pPointsOut != NULL) pPointsOut->push_back(LMVector3(tempPoints.at(i)));
				found = true;
				OutputDebugString("Is in region\n");
			}
		}
	}

	//if (Result != NULL) OutputDebugString("Wall is in way.\n");
	//else  OutputDebugString("No walls in way.\n");

	return found;

	//return (Result == NULL);
}

bool SpriteView::IsIntersectSprite(vector<LMVector3> *hitPoints, D3DXVECTOR3 point1, D3DXVECTOR3 point2)
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

	D3DXIntersect(m_mesh->GetMesh(), &point1, &point2,
		&isIntersect, &faceIndex, &u, &v, &dist, &AllHits,
		&CountOfHits);


	float resultX = point2.x - point1.x;
	float resultY = point2.y - point1.y;
	float resultZ = point2.z - point1.z;
	float result = sqrt(abs(resultX*resultX + resultY*resultY + resultZ*resultZ));
	/*
	char gbuffer100[100];

	sprintf_s(gbuffer100, "Length of ray: %f..", result);
	OutputDebugString(gbuffer100);

	sprintf_s(gbuffer100, "CountOfHits: %i \n", CountOfHits);
	OutputDebugString(gbuffer100);

	*/

	if (isIntersect)
	{

		WORD * pI = m_mesh->GetIndiceBuffer();
		D3D9Vertex_UnlitTextured * pV = m_mesh->GetVertexBuffer();

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

Sprite * SpriteView::GetSprite()
{
	return m_sprite;
}

LMMesh * SpriteView::GetLMMesh()
{
	return m_mesh;
}

D3DXMATRIX * SpriteView::GetWorldMatrix()
{
	return &m_worldMatrix;
}