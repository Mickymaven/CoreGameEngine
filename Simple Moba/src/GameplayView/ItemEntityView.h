#if !defined(ITEMENTITYVIEW_H)
#define ITEMENTITYVIEW_H

#include "../../../EngineMoba/src/Actors/ItemEntity.h"
#include "VitalEntityView.h"

class ItemEntityView
{
protected:
	ItemEntity * m_itemEntity;
	VitalEntityView m_vitalEntityView;

public:
	ItemEntityView(LPDIRECT3DDEVICE9 device, ItemEntity * itemEntity, LMMesh * mesh);
	~ItemEntityView();

	void Render();

	ItemEntity * GetItemEntity();
	VitalEntityView * GetVitalEntityView();
};

#endif