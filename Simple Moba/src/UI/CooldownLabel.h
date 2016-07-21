#if !defined(COOLDOWNLABEL_H)
#define COOLDOWNLABEL_H

#include "../../../EngineGameModuleDirectX9/src/UI/UILabelCstr.h"

enum CoolTextState
{
	coolTextAbove,
	coolTextBelow,
	coolTextZero
};

class CooldownLabel : public UILabelCstr
{
protected:
	static const char m_baseFormatStringAbove[];
	static const char m_baseFormatStringBelow[];
	float m_belowThreshhold;
	CoolTextState m_state;

	LPD3DXFONT m_fontBelow;
	D3DCOLOR * m_colorBelow;
	DWORD * m_formatBelow;

public:
	CooldownLabel();
	~CooldownLabel();

	bool Init(const RECT & rect, FontGroup * aboveFont, FontGroup * belowFont, int belowThreshhold);

	void Render() override;

	void SetText(float f) override;

};


#endif