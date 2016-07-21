#if !defined (VITALEVENTCONTROLLER_H)
#define VITALEVENTCONTROLLER_H

//Logic layer called from Game Mode Controller::Update() after all sim takes place

#include "../../../EngineMoba/src/Gamestate/MobaState.h"

#include "BuffController.h"
#include "HealingController.h"
#include "DamageController.h"


class VitalEventController
{
private:
	BuffController m_buffController;
	HealingController m_healingController;
	DamageController m_damageController;

	MobaState * m_gameState;

public:
	VitalEventController();
	~VitalEventController();

	bool Init(MobaState * gameState);

	void Update(float deltaTime);

	//Accessors
	DamageController * GetDamageController();

};

#endif