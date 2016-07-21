#include "SpookySpaceMeringueView.h"

SpookySpaceMeringueView::SpookySpaceMeringueView(){}

SpookySpaceMeringueView::SpookySpaceMeringueView(LPDIRECT3DDEVICE9 device, SpookySpaceMeringue * spookySpaceMeringue)
	:AbilityView(spookySpaceMeringue), m_spookySpaceMeringue(spookySpaceMeringue)
{
	m_meringueView = SpriteView(device, spookySpaceMeringue->GetMeringue(), new LMMesh("Resources/Characters/Shared/", "CosmicSpaghetti.x", device) );
}

SpookySpaceMeringueView::~SpookySpaceMeringueView()
{
}

void SpookySpaceMeringueView::Render()
{
	if (!IsActive()) return;

	if (!m_spookySpaceMeringue->IsTriggered())
		m_meringueView.Render();
}