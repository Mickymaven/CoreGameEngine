#include "TheSlurpeningView.h"

TheSlurpeningView::TheSlurpeningView() {}

TheSlurpeningView::TheSlurpeningView(LPDIRECT3DDEVICE9 device, TheSlurpening * theSlurpening)
	:AbilityView(theSlurpening), m_theSlurpening(theSlurpening)
{
	m_strawView = SpriteView( device, theSlurpening->GetStraw(), new LMMesh("Resources/Characters/Shared/", "straw.x", device) );


	D3DMATERIAL9 * m = m_strawView.GetLMMesh()->GetMaterial(0);
	m->Ambient.r = 1.0f;
	m->Ambient.g = 1.0f;
	m->Ambient.b = 1.0f;
	m->Specular.r = 1.0f;
	m->Specular.g = 1.0f;
	m->Specular.b = 1.0f;

}

TheSlurpeningView::~TheSlurpeningView()
{
}

void TheSlurpeningView::Render()
{
	if (!IsActive()) return;

	m_strawView.Render();
}

TheSlurpening * TheSlurpeningView::GetTheSlurpening(){ return m_theSlurpening; }
