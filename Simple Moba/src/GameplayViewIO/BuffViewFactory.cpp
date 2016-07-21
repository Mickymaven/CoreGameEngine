#include "BuffViewFactory.h"

//vector<BuffView> m_buffViews;
///ViewProfile * m_viewProfile;

BuffViewFactory::BuffViewFactory()
{

}

BuffViewFactory::~BuffViewFactory()
{

}

bool BuffViewFactory::Init(ViewProfile * viewProfile)
{
	if (!viewProfile->InitElement(gameElementBuffTooltipBackground, &TooltipInfoBuff::m_background)) return false;

	m_buffViews.resize(buffNameCount);

	for (unsigned int i = 0; i < buffNameCount; i++)
	{
		string path;
		string name;

		vector < TooltipEffect > * effects = new vector<TooltipEffect>;

		TooltipEffect buffEffect1;
		//TooltipEffect buffEffect2;

		switch (i)
		{
		case buffSleeping:
			name = "Sleeping";
			path = "Resources/UI/Buffs/Sleeping.png";

			buffEffect1.descFirst = "You are gaining";
			buffEffect1.m_number = "100";
			buffEffect1.m_type = "Health points";
			buffEffect1.descSecond = "over 10 seconds.";
			effects->push_back(buffEffect1);
			
			break;


		case buffCoveredInSpam:
			name = "Covered in Flaming Spam";
			path = "Resources/UI/Buffs/MotoCrash.png";

			buffEffect1.descFirst = "chunks of goey flaming wretched spam will wither";
			buffEffect1.m_number = "10";
			buffEffect1.m_type = "Armor";
			buffEffect1.descSecond = " from the target for 9 seconds.";
			effects->push_back(buffEffect1);

			break;

		case buffIncapacitedBySauce:
			name = "Incapacited by Sauce";
			path = "Resources/UI/Buffs/MotoCrash.png";
			
			buffEffect1.descFirst = "You are recieving";
			buffEffect1.m_number = "100";
			buffEffect1.m_type = "Health points";
			buffEffect1.descSecond = "over 10 seconds.";
			effects->push_back(buffEffect1);
			
			break;
		
		case buffPowerOfTheBoost:
			name = "Power of the Boost";
			path = "Resources/UI/Buffs/SugarOverload.png";
			
			buffEffect1.descFirst = "Recieving";
			buffEffect1.m_number = "6";
			buffEffect1.m_type = "Movespeed";
			buffEffect1.descSecond = "for 5 seconds.";
			effects->push_back(buffEffect1);

			break;
		case buffMotoSmash:

			name = "MotoSmash";
			path = "Resources/UI/Buffs/MotoCrash.png";

			buffEffect1.descFirst = "You smashed em! Nice! But now you get";
			buffEffect1.m_number = "-9";
			buffEffect1.m_type = "Movespeed";
			buffEffect1.descSecond = "for 2 seconds.";
			effects->push_back(buffEffect1);
			break;

		case buffOmNomNom:
			name = "Om NomNom";
			path = "Resources/UI/Buffs/SugarOverload.png";

			buffEffect1.descFirst = "You are recieving";
			buffEffect1.m_number = "100";
			buffEffect1.m_type = "Health points";
			buffEffect1.descSecond = "over 10 seconds.";
			effects->push_back(buffEffect1);

			break;

		case buffBikeActivated:
			name = "Bike Activated";
			path = "Resources/UI/Buffs/SugarOverload.png";

			buffEffect1.descFirst = "You have activated the bike. ";
			buffEffect1.m_number = "";
			buffEffect1.m_type = "";
			buffEffect1.descSecond = "";
			effects->push_back(buffEffect1);

			break;

		case buffSugarOverload:
			name = "Sugar Overload";
			path = "Resources/UI/Buffs/MotoCrash.png";

			buffEffect1.descFirst = "You are suffering a";
			buffEffect1.m_number = "67%";
			buffEffect1.m_type = "move-speed";
			buffEffect1.descSecond = "slow.";

			effects->push_back(buffEffect1);

			break;

		case buffSugarPower:
			name = "Sugar Power";
			path = "Resources/UI/Buffs/SugarOverload.png";

			buffEffect1.descFirst = "You are recieving an extra";
			buffEffect1.m_number = "100";
			buffEffect1.m_type = "Cat Voodoo power";
			buffEffect1.descSecond = "for 10 seconds.";

			effects->push_back(buffEffect1);

		default:case buffNameCount:
			DEBUG_IF(true) MessageBox(NULL, "Bad index in BuffViewFactory::Init switch","Simple Moba Error",MB_OK);
			break;

		}

		m_buffViews.at(i).GetIcon()->Init(43.0f, 43.0f, path);
		m_buffViews.at(i).GetTooltip()->SetEffects(effects);
		m_buffViews.at(i).GetTooltip()->SetName(new string(name));

	}

	return true;

}

bool BuffViewFactory::ConstructBuffView(BuffName name, BuffView ** buffViewOut)
{
	return true;
}

vector<BuffView> * BuffViewFactory::GetLightweightBuffViews()
{
	return &m_buffViews;
}
