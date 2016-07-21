#include "UIDialogBox.h"

UIDialogBox::UIDialogBox() : UIMenu()
{

}

UIDialogBox::~UIDialogBox()
{

}

bool UIDialogBox::Init()
{
	return true;
}

void UIDialogBox::Select(POINT * p)//is virtual
{

}

void UIDialogBox::AltSelect(POINT * p)//is virtual
{

}