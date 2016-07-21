#include "PathRendering.h"

Sprite * PathRendering::nodeSprite = NULL;
SpriteView * PathRendering::nodeSpriteView = NULL;
LMVector3 * PathRendering::nodeSpritePosition = NULL;

Sprite * PathRendering::nodePath = NULL;
SpriteView * PathRendering::nodePathView = NULL;
LMVector3 * PathRendering::nodePathPosition = NULL;
LMVector3 * PathRendering::nodePathRotation = NULL;

Sprite * PathRendering::nodePathOptimised = NULL;
SpriteView * PathRendering::nodePathOptimisedView = NULL;
LMVector3 * PathRendering::nodePathOptimisedPosition = NULL;
LMVector3 * PathRendering::nodePathOptimisedRotation = NULL;

PathRendering::PathRendering()
{
	nodePhysics = NULL;

	D3DMATERIAL9 * mat = new D3DMATERIAL9();
	
	mat->Ambient.r = 0.85f;
	mat->Ambient.g = 0.4f;
	mat->Ambient.b = 1.0f;
	mat->Specular.r = 0.5f;
	mat->Specular.g = 0.5f;
	mat->Specular.b = 0.5f;
	mat->Power = 0.5f;

	m_pathMesh = LMMesh("Resources/Characters/Shared/","straw.x", g_D3D_Device, mat, false);
	
	//Optimsed
	mat = new D3DMATERIAL9();
	mat->Ambient.r = 1.0f;
	mat->Ambient.g = 1.0f;
	mat->Ambient.b = 1.0f;
	mat->Specular.r = 0.8f;
	mat->Specular.g = 0.8f;
	mat->Specular.b = 0.8f;
	mat->Power = 0.8f;
	
	m_pathMeshOptimised = LMMesh("Resources/Characters/Shared/","straw.x", g_D3D_Device, mat, false);

	if (nodeSprite == NULL)
	{
		nodeSprite = new Sprite(
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(4.0f, 16.0f, 4.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			0.0f);

		nodeSpritePosition = nodeSprite->GetPhysicsObject()->GetPosition();

		nodeSpriteView = new SpriteView(g_D3D_Device, nodeSprite, &m_pathMesh);

	}

	if (nodePath == NULL)
	{
		nodePath = new Sprite(
			LMVector3(0.0f, 0.5f, 0.0f),
			LMVector3(1.571f, 0.0f, 1.571f),
			LMVector3(4.0f, 1.0f, 4.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			0.0f);

		nodePathPosition = nodePath->GetPhysicsObject()->GetPosition();
		nodePathRotation = nodePath->GetPhysicsObject()->GetRotation();

		nodePathView = new SpriteView(g_D3D_Device, nodePath, &m_pathMesh);
	}

	nodePhysics = nodePath->GetPhysicsObject();

	if (nodePathOptimised == NULL)
	{
		nodePathOptimised = new Sprite(
			LMVector3(0.0f, 1.7f, 0.0f),
			LMVector3(1.571f, 0.0f, 1.571f),
			LMVector3(4.0f, 1.0f, 4.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			0.0f);

		nodePathOptimisedView = new SpriteView(g_D3D_Device, nodePathOptimised, &m_pathMeshOptimised);

		nodePathOptimisedPosition = nodePathOptimised->GetPhysicsObject()->GetPosition();
		nodePathOptimisedRotation = nodePathOptimised->GetPhysicsObject()->GetRotation();
	}
}

PathRendering::~PathRendering()
{


}

void PathRendering::RenderNodes(vector<LMVector3 *> * nodes)
{
	if (nodes == NULL) return;

	for (unsigned int i = 0; i < nodes->size(); i++)
	{
		if (nodes->at(i) != NULL)
		{
			nodeSpritePosition->x = nodes->at(i)->x;
			nodeSpritePosition->y = nodes->at(i)->y;
			nodeSpritePosition->z = nodes->at(i)->z;
			nodeSpriteView->Render();
		}
	}
}

void PathRendering::RenderPaths(vector<vector<LMVector3 *>*> * graphs, PathRenderOption option)
{
	if (graphs == NULL) return;
	
	LMVector3 unitDirection;
	SpriteView * selectedPathView = NULL;
	LMVector3 * pos = NULL;
	LMVector3 * rot = NULL;

	auto * a = nodePhysics;

	for (unsigned int i = 0; i < graphs->size(); i++)
	{
		if (graphs->at(i)->at(0) == NULL) continue;

		for (unsigned int iNeighbour = 0; iNeighbour < graphs->at(i)->size(); iNeighbour++)
		{
			if (iNeighbour == 0) continue;
			if (graphs->at(i)->at(iNeighbour) == NULL) continue;
			if (option == pathRenderOptionPath || option==pathRenderOptionPathOptimised)
			{
				//only rendering path to next on parameter graphs (closed list result)
				if (i+1 <= (graphs->size()-1))
				{
					if (graphs->at(i)->at(iNeighbour) != graphs->at(i + 1)->at(0)) continue;
				}
				else if (i == graphs->size() - 1) continue;
			}


			RenderPathWithPositions(graphs->at(i)->at(0), graphs->at(i)->at(iNeighbour), option);
			/*

			if (option == pathRenderOptionPath)
			{
				selectedPathView = nodePathView;
				pos = nodePathPosition;
				rot = nodePathRotation;
			}
			else if (option == pathRenderOptionPathOptimised)
			{
				selectedPathView = nodePathOptimisedView;
				pos = nodePathOptimisedPosition;
				rot = nodePathOptimisedRotation;
			}
			else return;

			unitDirection.x = graphs->at(i)->at(iNeighbour)->x - graphs->at(i)->at(0)->x;
			unitDirection.y = graphs->at(i)->at(iNeighbour)->y - graphs->at(i)->at(0)->y;
			unitDirection.z = graphs->at(i)->at(iNeighbour)->z - graphs->at(i)->at(0)->z;

			pos->x = graphs->at(i)->at(0)->x;
			//pos->y = 1.0f;
			pos->z = graphs->at(i)->at(0)->z;

			unitDirection.Normalize();

			rot->y = atan2(unitDirection.x, unitDirection.z) + 1.571f;

			selectedPathView->GetSprite()->GetPhysicsObject()->GetScale()->y =
				graphs->at(i)->at(0)->DisplacementMag(*graphs->at(i)->at(iNeighbour));

			selectedPathView->Render();
			*/
		}
	}
}

void PathRendering::RenderPathWithPositions(LMVector3 * origin, LMVector3 * target, PathRenderOption option)
{

	LMVector3 unitDirection;
	SpriteView * selectedPathView = NULL;
	LMVector3 * pos = NULL;
	LMVector3 * rot = NULL;


	if (option == pathRenderOptionPath)
	{
		selectedPathView = nodePathView;
		pos = nodePathPosition;
		rot = nodePathRotation;
	}
	else if (option == pathRenderOptionPathOptimised)
	{
		selectedPathView = nodePathOptimisedView;
		pos = nodePathOptimisedPosition;
		rot = nodePathOptimisedRotation;
	}
	else return;

	unitDirection.x = target->x - origin->x;
	unitDirection.y = target->y - origin->y;
	unitDirection.z = target->z - origin->z;

	pos->x = origin->x;
	//pos->y = 1.0f;
	pos->z = origin->z;

	unitDirection.Normalize();

	rot->y = atan2(unitDirection.x, unitDirection.z) + 1.571f;

	selectedPathView->GetSprite()->GetPhysicsObject()->GetScale()->y = origin->DisplacementMag(*target);

	selectedPathView->Render();
}