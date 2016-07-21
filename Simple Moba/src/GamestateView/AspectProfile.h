#if !defined(ASPECTPROFILE_H)
#define ASPECTPROFILE_H

#include <vector>
using std::vector;

#include "ProfileBase.h"

enum ElementSettingsName
{

};

class AspectProfile
{

private:

	ResolutionState m_currentResolution;
	AspectRatioState m_currentAspect;
	
	vector<vector<vector<float>>> m_data;

	//new
	AspectRatioState m_resolutionAspect[resolutionCount];
	int m_resolutionValues[resolutionCount][2];

	//float m_positions[aspectCount][gameElementCount][2];
	//float m_size[aspectCount][gameElementCount][2];

public:

	AspectProfile();
	~AspectProfile();
	
	int ResolutionWidth();
	int ResolutionHeight();

	float GetAlignX(int element);
	float GetAlignY(int element);

	float GetXForElement(int element);
	float GetYForElement(int element);

	float GetWidthForElement(int element);
	float GetHeightForElement(int element);
	
	vector<vector<vector<float>>> * GetData();

	ResolutionState * GetCurrentResolution();
	AspectRatioState * GetCurrentAspect();

};

#endif