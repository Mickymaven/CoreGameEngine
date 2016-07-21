#if !defined(VISIONOWL_H)
#define VISIONOWL_H

#include "../../../../../EngineMoba/src/Actors/NPCController.h"

#include "../CoreNPCController.h"

#include "VisionOwlInteractionController.h"
#include "VisionOwlStandard1InteractionController.h"


enum VisionOwlAbility
{
	voBasicAttack,
	voCount
};

class VisionOwl : public CoreNPCController
{
private:
	VisionOwlInteractionController * m_voState;


	//VisionOwlStandard1InteractionController m_s1;

	vector<VisionOwlInteractionController*> * m_ic_vo_list;


	VisionOwlDialogBehavior m_visionOwlDialogBehavior;
	DialogStandbyBehavior m_dialogStandbyBehavior;
	AggressionState m_aggroState;

public:
	VisionOwl(CoreCharacter * character,
		vector<Actor * > * teamActors,
		vector<Actor * > * opponentActors,
		vector<Actor * > * neutralActors);
	~VisionOwl();

	bool SetInteractionControllersList(vector<VisionOwlInteractionController*> * ic_vo_list);

	void Update(float deltaTime);
	void Render();

	void OnRespawn(float x, float y, float z);

	void OnHit(VitalEntity * owner);

	NPCSelectAction GetSelectBehavior();


};

#endif