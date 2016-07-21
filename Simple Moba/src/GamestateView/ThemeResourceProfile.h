#if !defined(THEMERESOURCEPROFILE_H)
#define THEMERESOURCEPROFILE_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "ProfileBase.h"

class ThemeResourceProfile
{
protected:
	AspectRatioState * m_currentAspect;

	vector<bool> m_isAspectDependent;
	vector<vector<string>> m_paths;

	vector<string> m_avatarPaths;

	//vector<D3DCOLOR> m_colors; todo

public:
	ThemeResourceProfile();
	~ThemeResourceProfile();

	string GetPath(int element);

	vector<bool> * GetAspectDependent();
	vector<vector<string>> * GetPaths();

	vector<string> * GetAvatarPaths();
	
	//vector<D3DCOLOR> * GetColors();

	void SetCurrentAspect(AspectRatioState * currentAspect);
};

#endif