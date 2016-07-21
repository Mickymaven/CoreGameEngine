#include "ElixirBurstView.h"

LMMesh * ElixirBurstView::m_ballMesh = nullptr;

ElixirBurstView::ElixirBurstView()
{
}

ElixirBurstView::ElixirBurstView(LPDIRECT3DDEVICE9 device, ElixirBurst * elixirBurstAbility)
	: AbilityView(elixirBurstAbility), m_elixirBurstAbility(elixirBurstAbility)
{
	if (m_ballMesh == nullptr) m_ballMesh = new LMMesh("Resources/Characters/Shared/", "CosmicSpaghetti.x", device);

	m_ballView = SpriteView(device, elixirBurstAbility->GetBall(), m_ballMesh);

}

ElixirBurstView::~ElixirBurstView()
{
	if (m_ballMesh != nullptr)
	{
		delete m_ballMesh;
		m_ballMesh = nullptr;
	}
}

void ElixirBurstView::Render()
{
	if (IsActive()) m_ballView.Render();
}
