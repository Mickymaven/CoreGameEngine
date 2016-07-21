#include "BuffView.h"


BuffView::BuffView() {}
BuffView::~BuffView() {}


UIElement * BuffView::GetIcon() { return &m_icon; }
TooltipInfoBuff * BuffView::GetTooltip() { return &m_tooltip; }