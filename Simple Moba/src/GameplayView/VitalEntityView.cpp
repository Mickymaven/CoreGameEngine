#include "VitalEntityView.h"

VitalEntityView::VitalEntityView(LPDIRECT3DDEVICE9 device, VitalEntity * vitalEntity, LMMesh * mesh)
	:SpriteView(device, vitalEntity, mesh), m_vitalEntity(vitalEntity)
{
}

VitalEntityView::~VitalEntityView()
{
}

void VitalEntityView::Render()
{
	if (m_vitalEntity->GetVitalEntityState() == vitalEntityStateActive)
		SpriteView::Render();
}

VitalEntity * VitalEntityView::GetVitalEntity() { return m_vitalEntity; }