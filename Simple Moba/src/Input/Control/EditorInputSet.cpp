#include "EditorInputSet.h"

EditorInputSet::EditorInputSet()
{
	

}

EditorInputSet::EditorInputSet(StandardMatch5v5State * state, MobaViewState * view, NodeEditor * nodeEditorIn)
{
	gameState = state;
	gameView = view;
	nodeEditor = nodeEditorIn;
}

EditorInputSet::~EditorInputSet()
{

}

void EditorInputSet::Update(float deltaTime)
{
	m_model->SetState(nodeEditor->GetState());
}

void EditorInputSet::AttemptAction(int action, float deltaTime)
{
	switch (action)
	{
	case editorActionNodeToolClick: nodeEditor->ActionNodeToolClick(); break;
	case editorActionToogleOn: nodeEditor->ActionToggleState(); break;
	case editorActionGenerateNeighbours: nodeEditor->GenerateNeighbours(); break;
	case editorActionGenerateFile: nodeEditor->GenerateCode();
	}
}

void EditorInputSet::SpamAction(int action, float deltaTime)
{

}