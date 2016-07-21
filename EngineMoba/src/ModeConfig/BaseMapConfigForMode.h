#if !defined(BASEMAPCONFIGFORMODE_H)
#define BASEMAPCONFIGFORMODE_H

//Base class for all Mode Base Classes
// ie MapXConfigForStandard < BaseMapConfigForStandard  < BaseMapConfigForMode

class BaseMapConfigForMode
{
protected:
	int m_iiiiiii;
	//anything a map could have in any mode (read: regardless of the map or mode)
	//map size vars for eg

public:
	BaseMapConfigForMode();
	~BaseMapConfigForMode();

};

#endif