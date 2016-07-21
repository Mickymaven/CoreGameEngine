#if !defined(VITALENTITYVIEW_H)
#define VITALENTITYVIEW_H

#include "../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../EngineMoba/src/Actors/VitalEntity.h"

class VitalEntityView : public SpriteView
{
protected:
	VitalEntity * m_vitalEntity;
public:
	VitalEntityView(LPDIRECT3DDEVICE9 device, VitalEntity * vitalEntity, LMMesh * mesh);
	~VitalEntityView();

	void Render();

	VitalEntity * GetVitalEntity();
};

#endif