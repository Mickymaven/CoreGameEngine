#if !defined(INTERACTIONZONE_H)
#define INTERACTIONZONE_H


#include "../../../EngineGameModel/src/Maths/LMVector3.h"

enum InteractionZoneState
{
	interactionZoneStateActive,
	interactionZoneStateInactive,
	interactionZoneStateCount
};

class InteractionZone
{
protected:
	InteractionZoneState m_interactionZoneState;
	LMVector3 m_position;
	float m_radius;

public:
	InteractionZone();
	~InteractionZone();

	bool Init(InteractionZoneState interactionZoneState);

	void Update(float deltaTime);

	void OnEnterActive();
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float deltaTime);
	void OnExitInactive();

	void ExitCurrentState();

	InteractionZoneState GetInteractionZoneState();
	LMVector3 * GetPosition();
	float GetRadius();

	void SetPosition(LMVector3 * position);
	void SetRadius(float radius);

};

#endif