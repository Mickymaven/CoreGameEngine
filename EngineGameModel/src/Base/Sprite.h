#if !defined (SPRITE_H)
#define SPRITE_H

#include "../Maths/LMVector3.h"
#include "../Base/PhysicsObject.h"

class Sprite
{
protected:
	PhysicsObject m_physicsObject;
	//bool m_isActive;

public:
	Sprite();
	Sprite(LMVector3 position, LMVector3 rotation, LMVector3 scale, LMVector3 velocity, LMVector3 spin, LMVector3 resize, float acceleration);
	~Sprite();

	PhysicsObject * GetPhysicsObject();
	//bool GetIsActive();

	//void SetIsActive(bool isActiveStatus);
};

#endif