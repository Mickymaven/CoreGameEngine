#include "GameAssetFactory.h"

GameAssetFactory::GameAssetFactory()
{
	m_characterMeshes.resize(characterNameCount); //Lightweight Assets

	m_assetMeshes.resize(assetMeshCount, nullptr);
}

GameAssetFactory::~GameAssetFactory()
{
	for (unsigned int i = 0; i < m_assetMeshes.size(); i++)
	{
		if (m_assetMeshes.at(i) != nullptr)
		{
			delete m_assetMeshes.at(i);
			m_assetMeshes.at(i) = nullptr;
		}
	}
}

void GameAssetFactory::Init(LPDIRECT3DDEVICE9 device)
{
	m_device = device;
}

UIElement * GameAssetFactory::GetCharacterIcon(CharacterClassName nameEnum)
{
	string name = "";

	switch (nameEnum)
	{
	case characterVisionOwl: name = "Resources/UI/Squares/Grey.png"; break;
	case characterAngryCat: name = "Resources/UI/Squares/Grey.png"; break;
	case characterGrey: name = "Resources/UI/Squares/Grey.png"; break;
	case characterLoost: name = "Resources/UI/Squares/Grey.png"; break;
	case characterTypy: name = "Resources/UI/Squares/Grey.png"; break;
	case characterShork: name = "Resources/UI/Squares/Grey.png"; break;
	}

	UIElement * e = new UIElement(50.0f,50.0f,name);

	if (e->Init())
	{
		return e;
	}
	
	return NULL;
}
/**/
LMMesh * GameAssetFactory::GetActorMesh(CharacterClassName nameEnum)
{
	if (m_characterMeshes.at(nameEnum) == NULL)
	{
		std::string file;
		std::string dir;

		dir = string("Resources/misc/"); file = string("Grey.x");

		/*switch (nameEnum)
		{

		default:
		case characterGrey: dir = string("Resources/misc/"); file = string("Grey.x"); break;
			
			case characterLoost		: s = string("Grey.x");  break;
			case characterTypy		: s = string("Grey.x");  break;
			case characterShork		: s = string("Grey.x");   break;
			case characterNameCount	: s = string("Grey.x");   break;
			
		}*/

		m_characterMeshes.at(nameEnum) = new LMMesh(dir, file, m_device);

	}
	return m_characterMeshes.at(nameEnum);
}

LMMesh * GameAssetFactory::GetAssetMesh(AssetMeshName nameEnum) //todo simple moba specific to refactor
{
	if (m_assetMeshes.at(nameEnum) == NULL)
	{
		std::string s;
		std::string dir;
		D3DMATERIAL9 * mat = NULL; //this could be improved. data driven materials?

		switch (nameEnum)
		{

		default:
		case assetTabulaRasaGroundStandard1:dir = string("Resources/Maps/Tabula_Rasa/"); s = string("tabula-rasa-ground.x");
			mat = new D3DMATERIAL9();
			mat->Ambient.r = 0.9f;
			mat->Ambient.g = 0.9f;
			mat->Ambient.b = 0.9f;
			mat->Specular.r = 0.1f;
			mat->Specular.g = 0.1f;
			mat->Specular.b = 0.1f;
			mat->Power = 0.1f; break;

		case assetBarebonesGroundStandard1:dir = string("Resources/misc/"); s = string("Ground.x");
			mat = new D3DMATERIAL9();
			mat->Ambient.r = 0.4f;
			mat->Ambient.g = 0.4f;
			mat->Ambient.b = 0.4f;
			mat->Specular.r = 0.1f;
			mat->Specular.g = 0.1f;
			mat->Specular.b = 0.1f;
			mat->Power = 0.1f; break; // LMMesh * groundMesh = new LMMesh("",""Ground.x", m_device, mat, false);
		
		case assetMeshChest1: dir = string("Resources/misc/");  s = string("Chest.x"); break;

		}

		//we used "mat" (give mat to LMMesh)
		if (mat != NULL) m_assetMeshes.at(nameEnum) = new LMMesh(dir, s, m_device, mat, false);
		//we didnt (LMMesh does it for us)
		else m_assetMeshes.at(nameEnum) = new LMMesh(dir, s, m_device);
	}

	return m_assetMeshes.at(nameEnum); 
}