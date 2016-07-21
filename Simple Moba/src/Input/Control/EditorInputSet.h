#if !defined(EDITORINPUTSET_H)
#define EDITORINPUTSET_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputSet.h"
#include "../../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../GamestateView/MobaViewState.h"
#include "../../Tools/NodeEditor.h"
#include "../Model/EditorInputModel.h"

class EditorInputSet : public InputSet
{

private:
	StandardMatch5v5State * gameState;
	MobaViewState * gameView;
	NodeEditor * nodeEditor;
	
public:
	EditorInputSet();
	EditorInputSet(StandardMatch5v5State * state, MobaViewState * view, NodeEditor * nodeEditorIn);
	~EditorInputSet();

	void Update(float deltaTime);
	void AttemptAction(int action, float deltaTime);
	void SpamAction(int action, float deltaTime);
};

#endif