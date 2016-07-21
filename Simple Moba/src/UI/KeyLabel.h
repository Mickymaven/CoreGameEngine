#if !defined(KEYLABEL_H)
#define KEYLABEL_H

#include "../../../EngineGameModuleDirectX9/src/Input/Keylist.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UILabel.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputKeyDefines.h"

class KeyLabel : public UILabel
{
private:
	int * m_key;
	Keylist * m_keylist;

public:
	KeyLabel();
	KeyLabel(Keylist * keylist);
	~KeyLabel();
	bool Init(const RECT & rect, FontGroup * fontGroup, int * key);
	void Render();

	int * GetKey();


	void SetKeyValue(int * key);

	Keylist * GetKeylist();
	void SetKeylist(Keylist * keylist);

	void Select(POINT * p);
	void AltSelect(POINT * p);

};

#endif