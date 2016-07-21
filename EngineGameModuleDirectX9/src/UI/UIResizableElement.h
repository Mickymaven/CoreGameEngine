#if !defined (UIRESIZABLEELEMENT_H)
#define UIRESIZABLEELEMENT_H


#include "UIElement.h"
#include "../../../EngineGameModel/src/Base/PhysicsObject.h"

class UIResizableElement : public UIElement
{
private:
	PhysicsObject m_physicsObject;

public:
	UIResizableElement();
	UIResizableElement(float width, float height, PhysicsObject & physicsObject, LPDIRECT3DTEXTURE9 texture);
	~UIResizableElement();

	void Render();

	PhysicsObject * GetPhysicsObject();

};


#endif