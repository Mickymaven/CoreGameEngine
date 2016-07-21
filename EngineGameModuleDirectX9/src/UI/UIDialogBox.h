#if !defined(UIDIALOGBOX_H)
#define UIDIALOGBOX_H

#include "UIMenu.h"
#include "UILabel.h"

class UIDialogBox: public UIMenu
{
protected:
	UILabel m_title;
	UILabel m_message;

public:
	UIDialogBox();
	~UIDialogBox();

	virtual bool Init();
	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);
};

#endif