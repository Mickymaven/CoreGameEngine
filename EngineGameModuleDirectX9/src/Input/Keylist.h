#if !defined(KEYLIST_H)
#define KEYLIST_H

//#include "../../../EngineGameModuleDirectX9/src/Input/InputModel.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputKeyDefines.h"
enum KeylistConfigs
{
	keylistEmpty,
	keylistUsable,
	keylistMouseButton12,
	keylistAcceptableChatCharacters
};
/*
#define LEFT_BUTTON     0
#define RIGHT_BUTTON    1
#define MIDDLE_BUTTON   2

#define MO_LEFT_BUTTON     238
#define MO_RIGHT_BUTTON    239
#define MO_MIDDLE_BUTTON   240
#define MO_ZDELTA		   241
#define NO_KEY			   700
*/


struct Keylist
{
	KeylistConfigs m_state;

	bool keylist[256];
	bool mouseList[3];

	const int keySize = 256;
	const int mouseSize = 3;

	void Init(KeylistConfigs config)
	{
		m_state = config;

		memset(&keylist, false, keySize);
		memset(&mouseList, false, mouseSize);

		switch (config)
		{
		case keylistEmpty://empty used for KeyLabels for mmb scroll
			//we dont want to let them change the mouse wheel zoom keybind
			//in anyway
			break;
		case keylistUsable:
			keylist[DIK_ESCAPE] = false;
			keylist[DIK_1] = true;
			keylist[DIK_2] = true;
			keylist[DIK_3] = true;
			keylist[DIK_4] = true;
			keylist[DIK_5] = true;
			keylist[DIK_6] = true;
			keylist[DIK_7] = true;
			keylist[DIK_8] = true;
			keylist[DIK_9] = true;
			keylist[DIK_0] = true;
			keylist[DIK_MINUS] = true;
			keylist[DIK_EQUALS] = true;
			keylist[DIK_BACK] = true;
			keylist[DIK_TAB] = true;
			keylist[DIK_Q] = true;
			keylist[DIK_W] = true;
			keylist[DIK_E] = true;
			keylist[DIK_R] = true;
			keylist[DIK_T] = true;
			keylist[DIK_Y] = true;
			keylist[DIK_U] = true;
			keylist[DIK_I] = true;
			keylist[DIK_O] = true;
			keylist[DIK_P] = true;
			keylist[DIK_LBRACKET] = true;
			keylist[DIK_RBRACKET] = true;
			keylist[DIK_RETURN] = true;
			keylist[DIK_LCONTROL] = true;
			keylist[DIK_A] = true;
			keylist[DIK_S] = true;
			keylist[DIK_D] = true;
			keylist[DIK_F] = true;
			keylist[DIK_G] = true;
			keylist[DIK_H] = true;
			keylist[DIK_J] = true;
			keylist[DIK_K] = true;
			keylist[DIK_L] = true;
			keylist[DIK_SEMICOLON] = true;
			keylist[DIK_APOSTROPHE] = true;
			keylist[DIK_GRAVE] = true;
			keylist[DIK_LSHIFT] = true;
			keylist[DIK_BACKSLASH] = true;
			keylist[DIK_Z] = true;
			keylist[DIK_X] = true;
			keylist[DIK_C] = true;
			keylist[DIK_V] = true;
			keylist[DIK_B] = true;
			keylist[DIK_N] = true;
			keylist[DIK_M] = true;
			keylist[DIK_COMMA] = true;
			keylist[DIK_PERIOD] = true;
			keylist[DIK_SLASH] = true;
			keylist[DIK_RSHIFT] = true;
			keylist[DIK_MULTIPLY] = true;
			keylist[DIK_LMENU] = false;
			keylist[DIK_SPACE] = false;
			keylist[DIK_CAPITAL] = false;
			keylist[DIK_F1] = true;
			keylist[DIK_F2] = true;
			keylist[DIK_F3] = true;
			keylist[DIK_F4] = true;
			keylist[DIK_F5] = true;
			keylist[DIK_F6] = true;
			keylist[DIK_F7] = true;
			keylist[DIK_F8] = true;
			keylist[DIK_F9] = true;
			keylist[DIK_F10] = true;
			keylist[DIK_NUMLOCK] = false;
			keylist[DIK_SCROLL] = false;
			keylist[DIK_NUMPAD7] = true;
			keylist[DIK_NUMPAD8] = true;
			keylist[DIK_NUMPAD9] = true;
			keylist[DIK_SUBTRACT] = true;
			keylist[DIK_NUMPAD4] = true;
			keylist[DIK_NUMPAD5] = true;
			keylist[DIK_NUMPAD6] = true;
			keylist[DIK_ADD] = true;
			keylist[DIK_NUMPAD1] = true;
			keylist[DIK_NUMPAD2] = true;
			keylist[DIK_NUMPAD3] = true;
			keylist[DIK_NUMPAD0] = true;
			keylist[DIK_DECIMAL] = true;
			keylist[DIK_OEM_102] = false;
			keylist[DIK_F11] = true;
			keylist[DIK_F12] = true;
			keylist[DIK_F13] = true;
			keylist[DIK_F14] = true;
			keylist[DIK_F15] = true;
			keylist[DIK_KANA] = false;
			keylist[DIK_ABNT_C1] = false;
			keylist[DIK_CONVERT] = false;
			keylist[DIK_NOCONVERT] = false;
			keylist[DIK_YEN] = false;
			keylist[DIK_ABNT_C2] = false;
			keylist[DIK_NUMPADEQUALS] = true;
			keylist[DIK_PREVTRACK] = false;
			keylist[DIK_AT] = false;
			keylist[DIK_COLON] = true;
			keylist[DIK_UNDERLINE] = true;
			keylist[DIK_KANJI] = false;
			keylist[DIK_STOP] = false;
			keylist[DIK_AX] = false;
			keylist[DIK_UNLABELED] = false;
			keylist[DIK_NEXTTRACK] = false;
			keylist[DIK_NUMPADENTER] = true;
			keylist[DIK_RCONTROL] = true;
			keylist[DIK_MUTE] = false;
			keylist[DIK_CALCULATOR] = false;
			keylist[DIK_PLAYPAUSE] = false;
			keylist[DIK_MEDIASTOP] = false;
			keylist[DIK_VOLUMEDOWN] = false;
			keylist[DIK_VOLUMEUP] = false;
			keylist[DIK_WEBHOME] = false;
			keylist[DIK_NUMPADCOMMA] = true;
			keylist[DIK_DIVIDE] = true;
			keylist[DIK_SYSRQ] = false;
			keylist[DIK_RMENU] = false;
			keylist[DIK_PAUSE] = true;
			keylist[DIK_HOME] = false;
			keylist[DIK_UP] = true;
			keylist[DIK_PRIOR] = false;
			keylist[DIK_LEFT] = true;
			keylist[DIK_RIGHT] = true;
			keylist[DIK_END] = false;
			keylist[DIK_DOWN] = true;
			keylist[DIK_NEXT] = false;
			keylist[DIK_INSERT] = false;
			keylist[DIK_DELETE] = false;
			keylist[DIK_LWIN] = false;
			keylist[DIK_RWIN] = false;
			keylist[DIK_APPS] = false;
			keylist[DIK_POWER] = false;
			keylist[DIK_SLEEP] = false;
			keylist[DIK_WAKE] = false;
			keylist[DIK_WEBSEARCH] = false;
			keylist[DIK_WEBFAVORITES] = false;
			keylist[DIK_WEBREFRESH] = false;
			keylist[DIK_WEBSTOP] = false;
			keylist[DIK_WEBFORWARD] = false;
			keylist[DIK_WEBBACK] = false;
			keylist[DIK_MYCOMPUTER] = false;
			keylist[DIK_MAIL] = false;
			keylist[DIK_MEDIASELECT] = false;

			mouseList[LEFT_BUTTON] = false;
			mouseList[RIGHT_BUTTON] = false;
			mouseList[MIDDLE_BUTTON] = true;
			break;
		case keylistMouseButton12:
			mouseList[LEFT_BUTTON] = true;
			mouseList[RIGHT_BUTTON] = true;
			mouseList[MIDDLE_BUTTON] = true;

			break;
		case keylistAcceptableChatCharacters:
			keylist[DIK_ESCAPE] = false;
			keylist[DIK_1] = true;
			keylist[DIK_2] = true;
			keylist[DIK_3] = true;
			keylist[DIK_4] = true;
			keylist[DIK_5] = true;
			keylist[DIK_6] = true;
			keylist[DIK_7] = true;
			keylist[DIK_8] = true;
			keylist[DIK_9] = true;
			keylist[DIK_0] = true;
			keylist[DIK_MINUS] = true;
			keylist[DIK_EQUALS] = true;
			keylist[DIK_BACK] = false;
			keylist[DIK_TAB] = false;
			keylist[DIK_Q] = true;
			keylist[DIK_W] = true;
			keylist[DIK_E] = true;
			keylist[DIK_R] = true;
			keylist[DIK_T] = true;
			keylist[DIK_Y] = true;
			keylist[DIK_U] = true;
			keylist[DIK_I] = true;
			keylist[DIK_O] = true;
			keylist[DIK_P] = true;
			keylist[DIK_LBRACKET] = true;
			keylist[DIK_RBRACKET] = true;
			keylist[DIK_RETURN] = false;
			keylist[DIK_LCONTROL] = false;
			keylist[DIK_A] = true;
			keylist[DIK_S] = true;
			keylist[DIK_D] = true;
			keylist[DIK_F] = true;
			keylist[DIK_G] = true;
			keylist[DIK_H] = true;
			keylist[DIK_J] = true;
			keylist[DIK_K] = true;
			keylist[DIK_L] = true;
			keylist[DIK_SEMICOLON] = true;
			keylist[DIK_APOSTROPHE] = true;
			keylist[DIK_GRAVE] = true;
			keylist[DIK_LSHIFT] = false;
			keylist[DIK_BACKSLASH] = true;
			keylist[DIK_Z] = true;
			keylist[DIK_X] = true;
			keylist[DIK_C] = true;
			keylist[DIK_V] = true;
			keylist[DIK_B] = true;
			keylist[DIK_N] = true;
			keylist[DIK_M] = true;
			keylist[DIK_COMMA] = true;
			keylist[DIK_PERIOD] = true;
			keylist[DIK_SLASH] = true;
			keylist[DIK_RSHIFT] = false;
			keylist[DIK_MULTIPLY] = true;
			keylist[DIK_LMENU] = false;
			keylist[DIK_SPACE] = true;
			keylist[DIK_CAPITAL] = false;
			keylist[DIK_F1] = false;
			keylist[DIK_F2] = false;
			keylist[DIK_F3] = false;
			keylist[DIK_F4] = false;
			keylist[DIK_F5] = false;
			keylist[DIK_F6] = false;
			keylist[DIK_F7] = false;
			keylist[DIK_F8] = false;
			keylist[DIK_F9] = false;
			keylist[DIK_F10] = false;
			keylist[DIK_NUMLOCK] = false;
			keylist[DIK_SCROLL] = false;
			keylist[DIK_NUMPAD7] = true;
			keylist[DIK_NUMPAD8] = true;
			keylist[DIK_NUMPAD9] = true;
			keylist[DIK_SUBTRACT] = true;
			keylist[DIK_NUMPAD4] = true;
			keylist[DIK_NUMPAD5] = true;
			keylist[DIK_NUMPAD6] = true;
			keylist[DIK_ADD] = true;
			keylist[DIK_NUMPAD1] = true;
			keylist[DIK_NUMPAD2] = true;
			keylist[DIK_NUMPAD3] = true;
			keylist[DIK_NUMPAD0] = true;
			keylist[DIK_DECIMAL] = true;
			keylist[DIK_OEM_102] = false;
			keylist[DIK_F11] = false;
			keylist[DIK_F12] = false;
			keylist[DIK_F13] = false;
			keylist[DIK_F14] = false;
			keylist[DIK_F15] = false;
			keylist[DIK_KANA] = false;
			keylist[DIK_ABNT_C1] = false;
			keylist[DIK_CONVERT] = false;
			keylist[DIK_NOCONVERT] = false;
			keylist[DIK_YEN] = false;
			keylist[DIK_ABNT_C2] = false;
			keylist[DIK_NUMPADEQUALS] = true;
			keylist[DIK_PREVTRACK] = false;
			keylist[DIK_AT] = false;
			keylist[DIK_COLON] = true;
			keylist[DIK_UNDERLINE] = true;
			keylist[DIK_KANJI] = false;
			keylist[DIK_STOP] = false;
			keylist[DIK_AX] = false;
			keylist[DIK_UNLABELED] = false;
			keylist[DIK_NEXTTRACK] = false;
			keylist[DIK_NUMPADENTER] = false;
			keylist[DIK_RCONTROL] = false;
			keylist[DIK_MUTE] = false;
			keylist[DIK_CALCULATOR] = false;
			keylist[DIK_PLAYPAUSE] = false;
			keylist[DIK_MEDIASTOP] = false;
			keylist[DIK_VOLUMEDOWN] = false;
			keylist[DIK_VOLUMEUP] = false;
			keylist[DIK_WEBHOME] = false;
			keylist[DIK_NUMPADCOMMA] = true;
			keylist[DIK_DIVIDE] = true;
			keylist[DIK_SYSRQ] = false;
			keylist[DIK_RMENU] = false;
			keylist[DIK_PAUSE] = false;
			keylist[DIK_HOME] = false;
			keylist[DIK_UP] = false;
			keylist[DIK_PRIOR] = false;
			keylist[DIK_LEFT] = false;
			keylist[DIK_RIGHT] = false;
			keylist[DIK_END] = false;
			keylist[DIK_DOWN] = false;
			keylist[DIK_NEXT] = false;
			keylist[DIK_INSERT] = false;
			keylist[DIK_DELETE] = false;
			keylist[DIK_LWIN] = false;
			keylist[DIK_RWIN] = false;
			keylist[DIK_APPS] = false;
			keylist[DIK_POWER] = false;
			keylist[DIK_SLEEP] = false;
			keylist[DIK_WAKE] = false;
			keylist[DIK_WEBSEARCH] = false;
			keylist[DIK_WEBFAVORITES] = false;
			keylist[DIK_WEBREFRESH] = false;
			keylist[DIK_WEBSTOP] = false;
			keylist[DIK_WEBFORWARD] = false;
			keylist[DIK_WEBBACK] = false;
			keylist[DIK_MYCOMPUTER] = false;
			keylist[DIK_MAIL] = false;
			keylist[DIK_MEDIASELECT] = false;

			mouseList[LEFT_BUTTON] = false;
			mouseList[RIGHT_BUTTON] = false;
			mouseList[MIDDLE_BUTTON] = false;
			break;

		}

	}



};

#endif