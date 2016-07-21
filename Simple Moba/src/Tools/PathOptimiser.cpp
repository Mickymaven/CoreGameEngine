#include "PathOptimiser.h"

#define DEBUGPATHFINDING false

PathRendering * PathOptimiser::m_pathRendering = NULL;

PathOptimiser::PathOptimiser()
{

	if (m_pathRendering == NULL) m_pathRendering = new PathRendering();
}

PathOptimiser::~PathOptimiser()
{
}

void PathOptimiser::Init(Pathfinder * pathfinder, SpriteView * groundView)
{
	m_closedList = pathfinder->GetClosedList();
	m_groundView = groundView;
	
	pathfinder->SetOptimiseFunction(std::bind(&PathOptimiser::OptimisePath, this, _1, _2, _3));
}

void PathOptimiser::Render()
{

	for (unsigned int i = 0; i < m_tempGraph.size(); i++)
	{
		m_pathRendering->RenderNodes(m_tempGraph.at(i));
	}

	//m_pathRendering->RenderPaths(&m_tempGraph, pathRenderOptionPath);
	m_pathRendering->RenderPaths(&m_tempGraphOptimised, pathRenderOptionPathOptimised);


	if (m_tempGraphOptimised.size() > 0)
	{
		m_pathRendering->RenderPathWithPositions(&m_origin, m_tempGraphOptimised.at(0)->at(0), pathRenderOptionPathOptimised);
		m_pathRendering->RenderPathWithPositions(m_tempGraphOptimised.at(m_tempGraphOptimised.size()-1)->at(0), &m_target, pathRenderOptionPathOptimised);
	}


	else if (m_tempGraphOptimised.size() == 0)
	{
		m_pathRendering->RenderPathWithPositions(&m_origin, &m_target, pathRenderOptionPathOptimised);
	}
}

void PathOptimiser::OptimisePath(vector<LMVector3*>* pathOut, LMVector3 * position, LMVector3 * target)
{
	m_origin = *position;
	m_target = *target;

	m_tempGraphOptimised.resize(0);

	m_tempGraph.resize(0);
	for (unsigned int i = 0; i < m_closedList->size(); i++)
	{
		m_tempGraph.push_back(m_closedList->at(i));
	}

	unsigned int firstNodeIndex = 0, lastNodeIndex = 0;
	//so we dont do out of bounds index access on 0 sized vectors during end path optimisations.
	if (m_closedList->size() > 0) lastNodeIndex = m_closedList->size() - 1;
	
	


	//dont need to optimise two closed nodes when you know you will just walk aa strait line
	if (IsVisualRangeNeighbour(position, target))
	{
		if (DEBUGPATHFINDING) OutputDebugString("Begin Optimisation (Strait line returning no path) \n");
		firstNodeIndex++;

		pathOut->resize(0);
		return;
	}
	
	// first node
	//optimise start of path
	
	if (DEBUGPATHFINDING) OutputDebugString("-------- Begin Optimisation --------------\n");
	
	for (unsigned int i = 0; i < m_closedList->size(); i++)
	{

		if (IsVisualRangeNeighbour(position, m_closedList->at(i)->at(0))
			|| IsVisualRangeNeighbour(m_closedList->at(i)->at(0), position))
		{
			if (i != 0)
			{
				firstNodeIndex++;
				if (DEBUGPATHFINDING) OutputDebugString("PO::Start: Skip a node\n");
			}
			else
			{
				if (DEBUGPATHFINDING) OutputDebugString("PO::Start: (In range of start node)\n");
			}
		}
		else
		{
			OutputDebugString("PO::Start: Intersect found\n");
			break;
		}
	}

	//optimise end of path


	char buffer[200];

	for (int i = m_closedList->size() - 1; i >= 0; i--)
	{
		if (DEBUGPATHFINDING) { sprintf_s(buffer, "i: %u \n", i); OutputDebugString(buffer); }

		if (IsVisualRangeNeighbour(m_closedList->at(i)->at(0), target))
		{
			if (i != m_closedList->size() - 1)//not last element on closed list
			{
				if (lastNodeIndex > firstNodeIndex) //and not first node
				{
					lastNodeIndex--;
					if (DEBUGPATHFINDING) OutputDebugString("PO::End: Skip a node\n");
				}
				else
				{
					if (DEBUGPATHFINDING) OutputDebugString("PO::End: First last match\n");
				}
			}
			else //Last ele on closed list
			{
				if (DEBUGPATHFINDING) OutputDebugString("PO::End: (skip as always in range of end node)\n");
			}
		}
		else
		{
			if (DEBUGPATHFINDING) OutputDebugString("PO::End: Intersect found.\n");
			break;
		}
	}

	pathOut->resize((lastNodeIndex - firstNodeIndex) + 1);

	unsigned int pathIndex = 0;



	//closed list size

	if (DEBUGPATHFINDING) sprintf_s(buffer, "Closed: %u, First: %u, Last: %u \n", m_closedList->size(), firstNodeIndex, lastNodeIndex);
	if (DEBUGPATHFINDING) OutputDebugString(buffer);

	if (DEBUGPATHFINDING) OutputDebugString("---------- End Optimisation --------------\n");



	
	m_tempGraphOptimised.resize(0);//Render stuff


	for (unsigned int i = firstNodeIndex; i <= lastNodeIndex; ++i)
	{
		m_tempGraphOptimised.push_back(m_closedList->at(i));

		pathOut->at(pathIndex) = m_closedList->at(i)->at(0);//potentially bad access of graph node vector3's directly from player classes etc
		pathIndex++;
	}
}

bool PathOptimiser::IsVisualRangeNeighbour(LMVector3 * parentNode, LMVector3 * targetNode)
{
	point1.x = parentNode->x;
	point1.y = 1.0f;
	point1.z = parentNode->z;

	point2.x = targetNode->x;
	point2.y = 1.0f;
	point2.z = targetNode->z;

	//Point 2 will be our direction
	D3DXVECTOR3 dir = D3DXVECTOR3(
		point2.x - point1.x,
		point2.y - point1.y,
		point2.z - point1.z);

	//was point2.x -= point1.x; point2.y -= point1.y; point2.z -= point1.z;

	TransformRayByMeshWorldMatrix((D3DXVECTOR3*)&point1, &dir, m_groundView->GetWorldMatrix());

	unsigned int initSize = m_hitPoints.size();

	//Result = NULL;

	bool found = false;

	if (m_groundView->IsIntersectSprite(&m_hitPoints, point1, dir))
	{
		//We might as well not do all this stuff id there are no hits
		// but for loop would just have 0 iterations if we did

		unsigned int elements = m_hitPoints.size() - initSize;

		//LMVector3 * currentHit = NULL;

		for (unsigned int i = m_hitPoints.size() - elements; i < m_hitPoints.size(); i++)
		{
			if (m_hitPoints.at(i).IsInRegion((LMVector3*)&point1, (LMVector3*)&point2))
			{
				found = true;
			}
			else
			{
				m_hitPoints.at(i).x = 0;
				m_hitPoints.at(i).y = 0;
				m_hitPoints.at(i).z = 0;
			}
		}
	}

	//if (Result != NULL) OutputDebugString("Wall is in way.\n");
	//else  OutputDebugString("No walls in way.\n");

	return !found;

	//return (Result == NULL);
}
