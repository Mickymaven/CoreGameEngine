#include "HealTurretView.h"

HealTurretView::HealTurretView() {}

HealTurretView::HealTurretView(LPDIRECT3DDEVICE9 device, HealTurret * turret)
	:AbilityView(turret), m_turret(turret)
{
	m_turretView = SpriteView(device, turret->GetTurret(), new LMMesh("Resources/misc/", "Turret.x", device));
}

HealTurretView::~HealTurretView()
{
}

void HealTurretView::Render()
{
	if (!IsActive()) return;

	if (m_turret->IsPlaced())
		m_turretView.Render();
}