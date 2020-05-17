#include "ActorViewFactory.h"

ActorViewFactory::ActorViewFactory()
{
	m_characterMeshes.resize(characterNameCount, NULL);
}

ActorViewFactory::~ActorViewFactory()
{

	for (unsigned int i = 0; i < m_characterMeshes.size(); i++)
	{	
		if (m_characterMeshes.at(i) != NULL)
		{
			delete m_characterMeshes.at(i);
			m_characterMeshes.at(i) = nullptr;
		}
	}

}

bool ActorViewFactory::ConstructActorView(LPDIRECT3DDEVICE9 device, ActorView ** actorViewOut, Actor * actor, CharacterClassName name)
{
	ActorView * m_actorView = nullptr;
	
	LMMesh * m_actorMesh = nullptr;

	if (!GetActorMesh(name, &m_actorMesh)) return false;

	m_actorView = new ActorView(device, actor, m_actorMesh);

	*actorViewOut = m_actorView;
}


bool ActorViewFactory::GetActorMesh(CharacterClassName name, LMMesh ** actorMeshOut)
{
	m_actorMesh = nullptr;

	if (m_characterMeshes.at(name) == NULL)
	{
		std::string dir;
		std::string file;

		switch (name)
		{
		case characterNenian: dir = "Resources/misc/"; file = "lowpolyfigure.x"; break;
		case characterSurku: dir = "Resources/misc/"; file = "lowpolyfigure.x"; break;
		case characterCaalu: dir = "Resources/misc/"; file = "lowpolyfigure.x"; break;
		default:
		case characterGrey: dir = "Resources/misc/"; file = "lowpolyfigure.x"; break;
		//case characterLoost: dir = "Resources/misc/"; file = "Grey.x"; break;
		//case characterTypy: dir = "Resources/misc/"; file = "Grey.x"; break;
		//case characterShork: dir = "Resources/misc/"; file = "Grey.x"; break;
		//case characterNameCount: dir = "Resources/misc/"; file = "Grey.x"; break;
		}


		m_characterMeshes.at(name) = new LMMesh(dir, file, g_D3D_Device);
		
	}

	*actorMeshOut = m_characterMeshes.at(name);
	return true;
}