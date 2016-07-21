#if !defined(VIEWPROFILE_H)
#define VIEWPROFILE_H

#include "AspectProfile.h"
#include "ThemeResourceProfile.h"

#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UILabel.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UILabelCstr.h"

#include "../UI_Base/UILayoutAvatar.h"

#include "MobaGameElementsEnum.h"

struct ViewProfile
{
public:
	ThemeResourceProfile * m_themeResourceProfile;
	AspectProfile * m_aspectProfile;

	bool InitElement(int elementID, UIElement * uiElement);
	bool InitElementWithPath(int elementID, UIElement * uiElement, string path);
	bool InitLabel(int elementID, UILabel * label, FontGroup * fontGroup, string * string);
	bool InitLabelCstr(int elementID, UILabelCstr * label, FontGroup * fontGroup);
	bool InitKeybindLbl(int elementID, UILabelCstr * label, FontGroup * fontGroup);

	bool InitRelativeLabel(int elementID, UILabelCstr * label, FontGroup * fontGroup, float w, float h, float top, float left);

	bool InitLayoutAvatar(int elementID, UILayoutAvatar * uiLayout, UIElement * uiElement);

	bool InitUIBase(int elementID, UIBase * uibase);


};

#endif