#if !defined(TOOLTIPEFFECT_H)
#define TOOLTIPEFFECT_H

#include <string>
using std::string;

struct TooltipEffect
{
	string descFirst;//plain language description Hero name + verb etc
	string m_number; //scale of (and if percentage) effect as c string
	// number to be colorised based on stat it scales on
	string m_type; //stat type of effect as c string
	string descSecond; //plain language description of how and when damage appears to be done in game

	//damage effects
	//allied team non damage stat effects
	//enemy team non damage stat effects
	//    } number effected
	//own stat buff effects

};

#endif