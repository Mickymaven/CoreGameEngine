#if !defined(HEALTURRET_H)
#define HEALTURRET_H

#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../../EngineMoba/src/Ability/PointAbility.h"
#include "AbilityIncludes.h"
#include "HealLaser.h"



class HealTurret : public PointAbility
{
private:
	Sprite m_turret;
	bool m_placed;
	bool m_activated;

	vector<Actor*> m_actorsInRange;

	vector<HealLaser*> m_HealLasers;
	

	LMVector3* m_pos;

public:
	HealTurret(Actor* owner);
	~HealTurret();

	//void Update(float deltaTime);
	//void TargetEliminated();

protected:
	void OnEnterActive(float currentGameTime);
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float DeltaTime);
	void OnExitInactive();

public:
	Sprite* GetTurret();
	bool IsPlaced();
	bool IsActivated();
};

#endif