#if !defined (PHYSICSOBJECT_H)
#define PHYSICSOBJECT_H

#include "../Maths/LMVector3.h"

class PhysicsObject
{
	private:
		LMVector3 m_position;
		LMVector3 m_rotation;
		LMVector3 m_scale;

		LMVector3 m_velocity;		
		LMVector3 m_spin; 		//to use //spin vector (rotation momentum)
		LMVector3 m_resize;		//to use //resize vector (scale momentium)

		float m_radius;

	public:


		PhysicsObject();
		PhysicsObject(LMVector3 position, LMVector3 rotation, LMVector3 scale, LMVector3 velocity, LMVector3 spin, LMVector3 resize, float initialRadius);
		~PhysicsObject();

		LMVector3 * GetPosition();
		LMVector3 * GetRotation();
		LMVector3 * GetScale();

		LMVector3 * GetVelocity();
		LMVector3 * GetSpin();
		LMVector3 * GetResize();

		float GetRadius();

		void SetPosition(LMVector3&);
		void SetRotation(LMVector3&);
		void SetScale(LMVector3&);

		void SetVelocity(LMVector3&);
		void SetSpin(LMVector3&);
		void SetResize(LMVector3&);
		
		void SetRadius(float);

		//void Strafe(float units);
		void Update(const float timeStep);
};

#endif
