#if !defined(BUFFCONTROLLER_H)
#define BUFFCONTROLLER_H

#include <vector>
using std::vector;

#include "../VitalEffect/Buff.h"

#include "VitalObjectController.h"

class BuffController : public VitalObjectController
{
private:
	//temp vars
	Buff * tempBuff;
	vector<Buff*> * buffVector;

public:
	BuffController();
	~BuffController();

	void Init(MobaState * gameStateIn);

	void Update(float deltaTime);

	void UpdateBuffs(float deltaTime);
	void UpdateDebuffs(float deltaTime);

	void UpdateBuffStructure(float deltaTime, bool buffs);
	void ApplyBuffToVitalEntity(int index, Actor * owner);
};

#endif