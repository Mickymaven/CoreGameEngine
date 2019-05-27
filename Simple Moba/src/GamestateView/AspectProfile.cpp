#include "AspectProfile.h"


AspectProfile::AspectProfile()
{
	m_currentResolution = resolution2560x1440;
	//aspect moved below

	//4x3
	m_resolutionAspect[resolution800x600] = aspect4x3;
	m_resolutionAspect[resolution1024x768] = aspect4x3;
	m_resolutionAspect[resolution1152x864] = aspect4x3;
	m_resolutionAspect[resolution1600x1200] = aspect4x3;
	
	//5x4
	m_resolutionAspect[resolution1265x985] = aspect5x4;
	m_resolutionAspect[resolution1280x1024] = aspect5x4;
	m_resolutionAspect[resolution1800x1440] = aspect5x4;

	//16x9
	m_resolutionAspect[resolution1280x720] = aspect16x9;
	m_resolutionAspect[resolution1536x864] = aspect16x9;
	m_resolutionAspect[resolution1600x900] = aspect16x9;
	m_resolutionAspect[resolution1920x1080] = aspect16x9;
	m_resolutionAspect[resolution2560x1440] = aspect16x9;

	//16x10
	m_resolutionAspect[resolution1280x800] = aspect16x10;
	m_resolutionAspect[resolution1440x900] = aspect16x10;
	m_resolutionAspect[resolution1680x1050] = aspect16x10;
	m_resolutionAspect[resolution1920x1200] = aspect16x10;

	//VALUES

	//4x3
	m_resolutionValues[resolution800x600][WidthValue] = 800;
	m_resolutionValues[resolution800x600][HeightValue] = 600;

	m_resolutionValues[resolution1024x768][WidthValue] = 1024;
	m_resolutionValues[resolution1024x768][HeightValue] = 768;

	m_resolutionValues[resolution1152x864][WidthValue] = 1152;
	m_resolutionValues[resolution1152x864][HeightValue] = 864;

	m_resolutionValues[resolution1600x1200][WidthValue] = 1600;
	m_resolutionValues[resolution1600x1200][HeightValue] = 1200;

	//5x4
	m_resolutionValues[resolution1265x985][WidthValue] = 1265;
	m_resolutionValues[resolution1265x985][HeightValue] = 985;

	m_resolutionValues[resolution1280x1024][WidthValue] = 1280;
	m_resolutionValues[resolution1280x1024][HeightValue] = 1024;

	m_resolutionValues[resolution1800x1440][WidthValue] = 1800;
	m_resolutionValues[resolution1800x1440][HeightValue] = 1440;

	//16x9
	m_resolutionValues[resolution1280x720][WidthValue] = 1280;
	m_resolutionValues[resolution1280x720][HeightValue] = 720;


	m_resolutionValues[resolution1536x864][WidthValue] = 1536;
	m_resolutionValues[resolution1536x864][HeightValue] = 864;

	m_resolutionValues[resolution1600x900][WidthValue] = 1600;
	m_resolutionValues[resolution1600x900][HeightValue] = 900;

	m_resolutionValues[resolution1920x1080][WidthValue] = 1920;
	m_resolutionValues[resolution1920x1080][HeightValue] = 1080;

	m_resolutionValues[resolution2560x1440][WidthValue] = 2560;
	m_resolutionValues[resolution2560x1440][HeightValue] = 1440;

	//16x10
	m_resolutionValues[resolution1280x800][WidthValue] = 1280;
	m_resolutionValues[resolution1280x800][HeightValue] = 800;

	m_resolutionValues[resolution1440x900][WidthValue] = 1440;
	m_resolutionValues[resolution1440x900][HeightValue] = 900;

	m_resolutionValues[resolution1680x1050][WidthValue] = 1680;
	m_resolutionValues[resolution1680x1050][HeightValue] = 1050;

	m_resolutionValues[resolution1920x1200][WidthValue] = 1920;
	m_resolutionValues[resolution1920x1200][HeightValue] = 1200;


	
	m_currentAspect = m_resolutionAspect[m_currentResolution];

	/*

	m_resolutionAspect[resolutionCount];

	int m_resolutionValues[resolutionCount][2];


	m_aspectRatios[enum640x480] = aspect5_4;

	m_resolution[enum640x480][WidthValue]
	m_resolution[enum640x480][HeightValue]

	m_positions[aspect5_4][gameElementHUD][enumWidthPercent]
	m_positions[aspect5_4][gameElementHUD][enumHeightPercent]

	*/

	//m_positions[aspect5x4][gameElementHUD][WidthValue] = 0.0f;
	//m_positions[aspect5x4][gameElementHUD][HeightValue] = 0.0f;

	//m_size[aspect5x4][gameElementHUD][WidthValue] = 1.0f;
	//m_size[aspect5x4][gameElementHUD][HeightValue] = 1.0f;


	//TODO
	/*


	m_data [aspectCount][elementCount][settingsCount]

	m_data[aspect5x4][gameElementHUD][positionXPercent] = 0.0f;
	m_data[aspect5x4][gameElementHUD][positionYPercent] = 0.0f;

	m_data[aspect5x4][gameElementHUD][ElementWidthPercent] = 1.0f;
	m_data[aspect5x4][gameElementHUD][ElementHeightPercent] = 1.0f;
	
	*/
}

AspectProfile::~AspectProfile()
{

}

int AspectProfile::ResolutionWidth()
{
	return m_resolutionValues[m_currentResolution][WidthValue];
}

int AspectProfile::ResolutionHeight()
{
	return m_resolutionValues[m_currentResolution][HeightValue];
}

float AspectProfile::GetAlignX(int element)
{
	return m_data[m_currentAspect][element][boundsHorizontalAlign] * (float)m_resolutionValues[m_currentResolution][WidthValue];
}

float AspectProfile::GetAlignY(int element)
{
	return m_data[m_currentAspect][element][boundsVerticalAlign] * (float)m_resolutionValues[m_currentResolution][HeightValue];
}

float AspectProfile::GetXForElement(int element)
{
	return m_data[m_currentAspect][element][boundsPartPositionX] * (float)m_resolutionValues[m_currentResolution][WidthValue];
}

float AspectProfile::GetYForElement(int element)
{
	return m_data[m_currentAspect][element][boundsPartPositionY] * (float)m_resolutionValues[m_currentResolution][HeightValue];
}

float AspectProfile::GetWidthForElement(int element)
{
	//m_data[m_currentAspect][element][boundsHorizontalAlign] +  
	return (m_data[m_currentAspect][element][boundsScale] * 
		m_data[m_currentAspect][element][boundsImageWidth] / m_data[m_currentAspect][element][boundsResWidth] ) *
		(float)m_resolutionValues[m_currentResolution][WidthValue];
}

float AspectProfile::GetHeightForElement(int element)
{
	// m_data[m_currentAspect][element][boundsVerticalAlign] +
	return (m_data[m_currentAspect][element][boundsScale] *
		m_data[m_currentAspect][element][boundsImageHeight] / m_data[m_currentAspect][element][boundsResHeight]) *
		(float)m_resolutionValues[m_currentResolution][HeightValue];
}

vector<vector<vector<float>>> * AspectProfile::GetData()
{
	return &m_data;
}

ResolutionState * AspectProfile::GetCurrentResolution()
{
	return &m_currentResolution;
}

AspectRatioState * AspectProfile::GetCurrentAspect()
{
	return &m_currentAspect;
}