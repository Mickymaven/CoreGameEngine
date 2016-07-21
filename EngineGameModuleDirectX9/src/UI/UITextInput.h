#if !defined(UITEXTINPUT_H)
#define UITEXTINPUT_H

#include "../../../EngineGameModel/src/Maths/LMVector4.h"

#include "../../../EngineGameModuleDirectX9/src/Input/Keylist.h"
#include "../../../EngineGameModuleDirectX9/src/Input/GameInputController.h"
#include "../../../EngineGameModuleDirectX9/src/UI/FontGroup.h"

#include "../../../EngineGameModuleDirectX9/src/Input/InputKeyDefines.h"



#include "UIArea.h"

#include <cstring>

enum TextInputState
{
	textInputActive,
	textInputInactive,
	textInputStateCount

};

class UITextInput : public UIArea
{
	TextInputState m_state;

	UIElement * m_background;
	vector<int> * m_acceptedKeys;

	int m_end;
	int caratIndex;

	char m_text[64];

	LPD3DXFONT m_font;
	D3DCOLOR * m_color;
	DWORD * m_format;

	DWORD m_leftDWORD;

	GameInputController * m_gameInputController;

	Keylist m_validInput;

public:
	UITextInput();
	~UITextInput();
	
	bool Init(FontGroup * fontGroup, LMVector4 * bounds, char * initText, int cstrSize, TextInputState activeState);

	void Update(float deltaTime, float gameTime);

	void Render();

	bool Char(char key);

	bool Backspace();


	void OnEnterActive();
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float deltaTime);
	void OnExitInactive();

	void ExitCurrentState();
	TextInputState GetState();

	void ActionUseDeactivate();
	void ActionActivate();
	void ActionDeactivate();

	char * GetText();

	void SetInputController(GameInputController * gameInputController);

};

#endif