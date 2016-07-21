#if !defined (BOID_H)
#define BOID_H


#include "../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../EngineGameModuleDirectX9/src/Graphics/LMMesh.h"
#include "../../../EngineGameModel/src/Base/PhysicsObject.h"

#include <ctime>

class Boid: public Sprite
{
private:
	static float sm_xmax;
	static float sm_zmax;

	LMVector3 m_origin;


	LMVector3 m_compositeVector;

	LMVector3 m_seperation;
	LMVector3 m_cohesion;
	LMVector3 m_alignment;
	
	LMVector3 m_random;
	LMVector3 m_inBounds;
	LMVector3 m_attractOrigin;

	LMVector3 * m_pPos;

	float m_minVelocity;
	float m_maxVelocity;

	float m_fAngleRads;

	float m_cohesionfactor;
	float m_originfactor;
	float m_inBoundsFactor;
	float m_alignmentFactor;

	float m_rotateSpeed;
	bool m_isRotateOn;

	LMVector3 m_tempDisplacement;

public:
	Boid();
	Boid(float xmax, float zmax,
					LMVector3 position,
					LMVector3 rotation,
					LMVector3 scale,
					LMVector3 velocity,
					LMVector3 spin,
					LMVector3 resize,
					float acceleration, 
					LMVector3 * origin); //Where ability was cast
	virtual ~Boid();

	void Update(const float fDeltaTime);

	void FreeWill(float deltaTime);

	void AttractionToOrigin(float deltaTime);
	void StayInBounds(float deltaTime);

	LMVector3 * GetCompositeVector();

	LMVector3 * GetSeperationVector();
	LMVector3 * GetCohesionVector();
	LMVector3 * GetAlignmentVector();

	void SetOrigin(LMVector3 * origin);

	void SetSeperationVector(const LMVector3 & seperation);
	void SetCohesionVector(const LMVector3 & cohesion);
	void SetAlignmentVector(const LMVector3 & alignment);
};

#endif