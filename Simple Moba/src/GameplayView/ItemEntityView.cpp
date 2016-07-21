#include "ItemEntityView.h"

ItemEntityView::ItemEntityView(LPDIRECT3DDEVICE9 device, ItemEntity * itemEntity, LMMesh * mesh)
	: m_itemEntity(itemEntity), m_vitalEntityView(VitalEntityView(device, itemEntity->GetVitalEntity(), mesh))
{

}

ItemEntityView::~ItemEntityView()
{
}

void ItemEntityView::Render()
{
	if (m_itemEntity->GetVitalEntity()->GetVitalEntityState() == vitalEntityStateActive)
		if (m_itemEntity->GetIsActive()==true)
			m_vitalEntityView.Render();
}

ItemEntity * ItemEntityView::GetItemEntity() { return m_itemEntity; }

VitalEntityView * ItemEntityView::GetVitalEntityView()
{
	return &m_vitalEntityView;
}
