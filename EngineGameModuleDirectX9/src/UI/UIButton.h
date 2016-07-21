#if !defined(UIBUTTON_H)
#define UIBUTTON_H

#include <functional>
using namespace std;

#include "UIElement.h"

class UIButton : public UIElement
{
private:
	std::function<void()> m_callback;

public:
	UIButton();
	UIButton(float width, float height, string path);
	~UIButton();

	void SetCallbackSTDFunction(std::function<void()> f);
	void OnClick();
	
	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);

	void SetPosition(LMVector3 * position);
	void SetPosition(float x, float y, float z);


};

#endif