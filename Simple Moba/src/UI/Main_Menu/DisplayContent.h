#if !defined(DISPLAYCONTENT_H)
#define DISPLAYCONTENT_H

#include "../../../../EngineGameModuleDirectX9/src/UI/UIContentArea.h"
#include "../../../../EngineGameModuleDirectX9/src/UI/UICheckBox.h"
#include "../../Input/Model/CharacterInputModel.h"
#include "../SettingsLabel.h"

#include "../../GamestateView/ViewProfile.h"
#include "../../GamestateView/ThemeResources.h"


class DisplayContent : public UIContentArea
{
private:
	//std::function<void(KeyLabel * label)> m_keyDialogActivate;

	vector <SettingsLabel *> m_keylabels;
	vector <UICheckBox *> m_checkboxes;

public:
	DisplayContent();
	DisplayContent(const DisplayContent & k);
	~DisplayContent();

	bool Init(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds);
	void PositionContent(LMVector4 * bounds);

	void Render() override;

	void Select(POINT * p);
	void AltSelect(POINT * p);

	//void SetKeyDialogCallback(std::function<void(KeyLabel*)> f);
	//void ActivateKeyDialogViaCallback(KeyLabel * label);

};

#endif