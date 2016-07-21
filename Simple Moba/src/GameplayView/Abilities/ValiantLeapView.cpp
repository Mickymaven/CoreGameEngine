#include "ValiantLeapView.h"

ValiantLeapView::ValiantLeapView()
{
}

ValiantLeapView::ValiantLeapView(LPDIRECT3DDEVICE9 device, ValiantLeap * valiantLeap)
	: AbilityView(valiantLeap), m_valiantLeap(valiantLeap)
{
}

ValiantLeapView::~ValiantLeapView()
{
}

void ValiantLeapView::Render()
{

}
