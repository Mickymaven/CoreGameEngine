#if !defined(UIKEYDIALOG_H)
#define UIKEYDIALOG_H

#include <string>
using std::string;

#include "../../../EngineGameModuleDirectX9/src/UI/FontGroup.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIDialogBox.h" 
#include "../../../EngineGameModuleDirectX9/src/Input/InputModel.h"
#include "../../../EngineGameModuleDirectX9/src/Input/GameInputController.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputKeyDefines.h"
#include "../UI/KeyLabel.h"
#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"

enum KeyDialogState
{
	keyDialogStateChecking,
	keyDialogStateNotChecking,
	keyDialogStateCount,
};

class UIKeyDialog : public UIDialogBox
{
protected:

	string m_titleStr;
	string m_messageStr;

	KeyDialogState m_state;
	KeyLabel * m_tempLabel;
	GameInputController * m_gameInputController;

	string m_selectedKeyMessage;
	UILabel m_selectedKey;

	UIButton m_apply;

	bool found;
	int iKey;
	int mKey;
	
public:
	UIKeyDialog();
	~UIKeyDialog();

	bool Init(
		string title,
		string message,
		ViewProfile * viewProfile,
		ThemeResources * theme,
		LMVector2 * origin,
		LMVector2 * size);

	void InitPosition(LMVector2 * origin, LMVector2 * size);

	void Update(float deltaTime);
	void Render();

	void OnEnterChecking();
	void Checking(float deltaTime);
	void OnExitChecking();

	void OnEnterNotChecking();
	void NotChecking(float deltaTime);
	void OnExitNotChecking();

	void ExitCurrentState();

	void Activate(KeyLabel * label);

	void Select(POINT * p);
	void AltSelect(POINT * p);

	void Apply();

	KeyDialogState GetKeyDialogState();

	void SetInputController(GameInputController * gameInputController);
};

#endif