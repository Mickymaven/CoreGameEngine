#include "ThemeResourceProfile.h"

ThemeResourceProfile::ThemeResourceProfile()
{
	m_currentAspect = nullptr;
}

ThemeResourceProfile::~ThemeResourceProfile()
{
}

string ThemeResourceProfile::GetPath(int element)
{
	if (m_isAspectDependent.at(element) == false)
	{
		return m_paths[0][element];
	}
	return m_paths[*m_currentAspect][element];
}

vector<bool> * ThemeResourceProfile::GetAspectDependent() { return &m_isAspectDependent; }

vector<vector<string>> * ThemeResourceProfile::GetPaths() { return &m_paths; }

vector<string> * ThemeResourceProfile::GetAvatarPaths() { return &m_avatarPaths; }

void ThemeResourceProfile::SetCurrentAspect(AspectRatioState * currentAspect) { m_currentAspect = currentAspect; }