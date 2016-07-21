#include "EditorInputModel.h"
EditorInputModel::EditorInputModel()
{}

bool EditorInputModel::Init(string path)
{

	m_path = "Resources/Settings/EditorInput.keys";

	m_keybinds.resize(editorActionCount);

	m_keybinds[editorActionNodeToolClick] = MO_RIGHT_BUTTON;
	m_keybinds[editorActionToogleOn] = DIK_N;
	m_keybinds[editorActionGenerateNeighbours] = DIK_M;
	m_keybinds[editorActionGenerateFile] = DIK_K;

	m_spamFlags.resize(editorActionCount, 0);

	vector<int> full
	{
		editorActionNodeToolClick,
		editorActionToogleOn,
		editorActionGenerateNeighbours,
		editorActionGenerateFile
	};

	vector<int> off
	{
		editorActionToogleOn
	};

	m_actionsforState.resize(2);

	m_actionsforState.at(0) = off;
	m_actionsforState.at(1) = full;

	return true;
}
EditorInputModel::~EditorInputModel()
{

}