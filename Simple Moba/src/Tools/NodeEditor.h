#if !defined(NODEEDITOR_H)
#define NODEEDITOR_H

// perform action for left clicks on ground
// perform action for left click on node sprite
//generate neighbours with raycasts
//render node and vector paths in game

//store temp node
//generate hardcoded node and graph data

#include <vector>
using std::vector;

#include <iostream>
using std::iostream;

#include <fstream>
using std::fstream;

#include <string>
using namespace std;

#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../EngineGameModel/src/Gamestate/BasicGameState.h"
#include "../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../EngineGameModuleDirectX9/src/Graphics/LMMesh.h"

#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h" //todo bad?
#include "../GamestateView/BasicGameViewState.h"
#include "../Graphics/GraphicsAlgorithms.h"

#include "PathRendering.h"

enum NodeEditorState
{
	nodeEditorOff,
	nodeEditorOn,
	nodeEditorCount
};

class NodeEditor : public PathRendering
{

private:

	BasicGameState * gameState;
	BasicGameViewState * viewState;

	NodeEditorState m_state;


	vector<LMVector3*> nodes;
	vector<vector<LMVector3*>> m_graph;

	vector<LMVector3> m_hitPoints;

	Sprite * m_ground;
	SpriteView * m_groundView;

	//hit test
	Sprite * target;
	D3DXVECTOR4 Result;

	D3DXVECTOR3 point1;
	D3DXVECTOR3 point2;

	char buffer200[200];

public:
	NodeEditor();
	NodeEditor(SpriteView * groundView, BasicGameState * state, BasicGameViewState * viewState);
	~NodeEditor();

	void Render();
	void RenderNode(LMVector3 * vector);
	void RenderPath(LMVector3 * origin, LMVector3 * target);

	bool GenerateNeighbours();
	bool IsVisualRangeNeighbour(LMVector3 * parentNode, LMVector3 * targetNode);

	void GenerateCode();

	bool ActionNodeToolClick();
	bool ActionToggleState();

	NodeEditorState GetState();


};

#endif