#if !defined(DIALOGOPTIONLABEL_H)
#define DIALOGOPTIONLABEL_H

#include "../../../EngineGameModuleDirectX9/src/UI/UILabel.h"
#include "../../../EngineMoba/src/Actor_Control/DialogOption.h"

class DialogOptionLabel : public UILabel
{
private:
	DialogOption * m_dialogOption;

public:
	DialogOptionLabel();
	~DialogOptionLabel();
	bool Init(const RECT & rect, FontGroup * fontGroup);
	void Render();

	DialogOption * GetDialogOption();
	void SetDialogOption(DialogOption* dialogOption);

	void Select(POINT * p);
	void AltSelect(POINT * p);

};

#endif