#if !defined(KEYBINDCONTENT_H)
#define KEYBINDCONTENT_H

#include "../../../../EngineGameModuleDirectX9/src/UI/UIContentArea.h"
#include "../../../../EngineGameModuleDirectX9/src/UI/UICheckBox.h"
#include "../../../../EngineGameModuleDirectX9/src/Input/InputKeyDefines.h"
#include "../../../../EngineGameModuleDirectX9/src/Input/Keylist.h"
#include "../../Input/Model/CharacterInputModel.h"
#include "../SettingsLabel.h"
#include "../KeyLabel.h"

#include "../../GamestateView/ViewProfile.h"
#include "../../GamestateView/ThemeResources.h"

#include <functional>
using namespace std::placeholders;

class KeybindContent : public UIContentArea
{
private:
	std::function<void(KeyLabel * label)> m_keyDialogActivate;
	//UIElement m_img;

	Keylist m_noKeys;
	Keylist m_usableKeys;// every key inc MMB, except ESC and L/M mouse button
	Keylist m_selectOnlyKeys;//LMB, RMB

	vector <KeyLabel *> m_keylabels;
	//vector <UICheckBox *> m_checkboxes;

public:
	KeybindContent();
	KeybindContent(const KeybindContent & k);
	~KeybindContent();

	bool Init(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds, vector<InputModel*> * inputModels);
	void PositionContent(LMVector4 * bounds);

	void Render() override;

	void Select(POINT * p);
	void AltSelect(POINT * p);

	void SetKeyDialogCallback(std::function<void(KeyLabel*)> f);
	void ActivateKeyDialogViaCallback(KeyLabel * label);

};

#endif