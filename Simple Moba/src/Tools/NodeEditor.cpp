#include "NodeEditor.h"



NodeEditor::NodeEditor()
{
	m_state = nodeEditorOff;
	nodes.reserve(300);
	target = NULL;
	gameState = NULL;
}

NodeEditor::NodeEditor(SpriteView * groundView, BasicGameState * state, BasicGameViewState * view)
	:PathRendering()
{
	viewState = view;
	gameState = state;
	m_groundView = groundView;
	m_state = nodeEditorOff;
	nodes.reserve(300);
}

NodeEditor::~NodeEditor()
{

}

void NodeEditor::Render()
{
	if (m_state == nodeEditorOff) return;

	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (nodes.at(i) != NULL)
		{
			nodeSpritePosition->x = nodes.at(i)->x;
			nodeSpritePosition->y = nodes.at(i)->y;
			nodeSpritePosition->z = nodes.at(i)->z;
			PathRendering::nodeSpriteView->Render();
		}
	}
	/*
	for (unsigned int hpIndex = 0; hpIndex < m_hitPoints.size(); hpIndex++)
	{
		nodeSprite->GetPhysicsObject()->GetScale()->x = 4.0f;
		nodeSprite->GetPhysicsObject()->GetScale()->y = 16.0f;
		nodeSprite->GetPhysicsObject()->GetScale()->z = 4.0f;
		nodeSpritePosition->x = m_hitPoints.at(hpIndex).x;
		nodeSpritePosition->y = m_hitPoints.at(hpIndex).y;
		nodeSpritePosition->z = m_hitPoints.at(hpIndex).z;
		nodeSprite->Render();
	}*/

	nodeSprite->GetPhysicsObject()->GetScale()->x = 8.0f;
	nodeSprite->GetPhysicsObject()->GetScale()->y = 2.0f;
	nodeSprite->GetPhysicsObject()->GetScale()->z = 8.0f;



	LMVector3 unitDirection;

	for (unsigned int i = 0; i < m_graph.size(); i++)
	{
		if (m_graph.at(i).at(0) == NULL) continue;

		for (unsigned int iNeighbour = 0; iNeighbour < m_graph.at(i).size(); iNeighbour++)
		{
			if (iNeighbour == 0) continue;
			if (m_graph.at(i).at(iNeighbour) == NULL) continue;

			unitDirection.x = m_graph.at(i).at(iNeighbour)->x - m_graph.at(i).at(0)->x;
			unitDirection.y = m_graph.at(i).at(iNeighbour)->y - m_graph.at(i).at(0)->y;
			unitDirection.z = m_graph.at(i).at(iNeighbour)->z - m_graph.at(i).at(0)->z;

			nodePathPosition->x = m_graph.at(i).at(0)->x;
			nodePathPosition->y = 1.0f;
			nodePathPosition->z = m_graph.at(i).at(0)->z;

			unitDirection.Normalize();
			float rot = atan2(unitDirection.x, unitDirection.z);

			nodePathRotation->y = rot + 1.571f;


			nodePath->GetPhysicsObject()->GetScale()->y =
				m_graph.at(i).at(0)->DisplacementMag(*m_graph.at(i).at(iNeighbour));

			nodePathView->Render();
		}

	}
}

void NodeEditor::RenderNode(LMVector3 * vector)
{

}

void NodeEditor::RenderPath(LMVector3 * origin, LMVector3 * target)
{

}


bool NodeEditor::GenerateNeighbours()
{
	m_graph.resize(0);
	m_graph.resize(nodes.size());

	m_hitPoints.resize(0);


	for (unsigned int iParentNode = 0; iParentNode < nodes.size(); iParentNode++)
	{
		m_graph.at(iParentNode).push_back(nodes.at(iParentNode));

		if (nodes.at(iParentNode) == NULL) continue;

		for (unsigned int iTargetNode = 0; iTargetNode < nodes.size(); iTargetNode++)
		{
			if (nodes.at(iTargetNode) == NULL) continue;
			if (iParentNode == iTargetNode) continue;

			sprintf_s(buffer200, "\n begin test on %i -> %i \n", iParentNode, iTargetNode);
			OutputDebugString(buffer200);

			if (IsVisualRangeNeighbour(nodes.at(iParentNode), nodes.at(iTargetNode)))
			{
				m_graph.at(iParentNode).push_back(nodes.at(iTargetNode));
			}
			OutputDebugString("Test complete.\n");
		}
	}

	return true;
}

bool NodeEditor::IsVisualRangeNeighbour(LMVector3 * parentNode, LMVector3 * targetNode)
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

	TransformRayByMeshWorldMatrix(&point1, &dir, m_groundView->GetWorldMatrix());
	
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

void NodeEditor::GenerateCode()
{
	//open stream
	ofstream file ("pathcode.txt");
	
	if (file.is_open())
	{
		char buffer500[500];

		int nodeSize = 0;

		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			if (nodes.at(i) != NULL) nodeSize++;
		}

		sprintf_s(buffer500, "nodes.resize(%i);\n", nodeSize);
		file << buffer500;

		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			if (nodes.at(i) != NULL)
			{
				sprintf_s(buffer500,
					"nodes.push_back(LMVector3(%.2f,%.2f,%.2f));\n",
					nodes.at(i)->x,
					nodes.at(i)->y,
					nodes.at(i)->z);
				file << buffer500;
			}
		}
		
		int neighbourCount = 0;
		int graphCount = 0;
		
		sprintf_s(buffer500, "m_graph.resize(%i);\n", nodeSize);
		file << buffer500;

		for (unsigned int i = 0; i < m_graph.size(); i++)
		{
			if (m_graph.at(i).at(0) == NULL)
			{
				continue;
			}

			sprintf_s(buffer500, "m_graph.at(%i).push_back(&nodes.at(%i));\n", graphCount, graphCount);
			file << buffer500;
			

			neighbourCount = 1;

			for (unsigned int iNeighbour = 1; iNeighbour < m_graph.at(i).size(); iNeighbour++)
			{
				if (m_graph.at(i).at(iNeighbour) == NULL) continue;
				
				int nodeIndex = 0;
				
				for (unsigned int j = 0; j < nodes.size(); j++)
				{

					if (m_graph.at(i).at(iNeighbour) == nodes.at(j))
					{
						break;
					}
					else if (nodes.at(j) != NULL) nodeIndex++;

				}

				sprintf_s(buffer500, "m_graph.at(%i).push_back(&nodes.at(%i));\n", graphCount, nodeIndex);
				file << buffer500;
				neighbourCount++;
				
			}
			graphCount++;
		}

	}
	else MessageBox(NULL,"Unable to opren file.","Error.", MB_OK);
}



bool NodeEditor::ActionNodeToolClick()
{
	bool found=false;

	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (nodes.at(i) != NULL)
		{
			nodeSpritePosition->x = nodes.at(i)->x;
			nodeSpritePosition->y = nodes.at(i)->y;
			nodeSpritePosition->z = nodes.at(i)->z;

			GetRayFromLMCamera(
				viewState->GetCameraDirector()->GetPointerToCurrentCamera(),
				g_mouseClientPosition.x,
				g_mouseClientPosition.y,
				point1,
				point2);

			nodeSpriteView->WorldTransform();
			TransformRayByMeshWorldMatrix(&point1, &point2, nodeSpriteView->GetWorldMatrix());

			if (found = PickFromSprite(&Result, nodeSpriteView->GetLMMesh(), point1, point2))
			{
				delete nodes.at(i);
				nodes.at(i) = NULL;
				
				break;
			}
		}
	}

	////test ground (we will then pace node)

	if (!found) //ie. no right click on character's mesh
	{

		GetRayFromLMCamera(
			viewState->GetCameraDirector()->GetPointerToCurrentCamera(),
			g_mouseClientPosition.x,
			g_mouseClientPosition.y,
			point1,
			point2);
		
		if (PickFromSprite(&Result, m_groundView->GetLMMesh(), point1, point2))
		{
			nodes.push_back(new LMVector3(Result.x, Result.y + 0.1f, Result.z));
		}
	}

	
	return true;

}

bool NodeEditor::ActionToggleState()
{
	if (m_state == nodeEditorOff) m_state = nodeEditorOn;
	else if (m_state == nodeEditorOn) m_state = nodeEditorOff;
	return true;
}


NodeEditorState NodeEditor::GetState()
{
	return m_state;
}
