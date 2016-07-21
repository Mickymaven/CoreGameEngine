#include "ThemeProfileIO.h"

ThemeProfileIO::ThemeProfileIO()
{

}

ThemeProfileIO::~ThemeProfileIO()
{

}

bool ThemeProfileIO::ReadData(string path, ThemeResourceProfile * themeResourceProfile)
{
	//hardcode to fix
	vector<string> * avatarPaths = themeResourceProfile->GetAvatarPaths();

	avatarPaths->reserve(characterNameCount);
	avatarPaths->push_back("Resources/UI/Icons/Grey.png");
	avatarPaths->push_back("Resources/UI/Icons/Grey.png");
	avatarPaths->push_back("Resources/UI/Icons/Grey.png");
	avatarPaths->push_back("Resources/UI/Icons/Grey.png");
	avatarPaths->push_back("Resources/UI/Icons/Grey.png");
	avatarPaths->push_back("Resources/UI/Icons/Grey.png");
	avatarPaths->push_back("Resources/UI/Icons/Grey.png");
	avatarPaths->push_back("Resources/UI/Icons/Grey.png");

	//okay the real io stuff 

	ifstream file(path);
	string line;

	int elementCount = 0;
	
	vector <bool> * isAspectDependent = themeResourceProfile->GetAspectDependent();
	vector<vector<string>> * m_data = themeResourceProfile->GetPaths();

	if (file.is_open())
	{
		//Get Element count
		if (std::getline(file, line))
		{
			OutputDebugString("Ele count: ");
			OutputDebugString(line.c_str());
			OutputDebugString("\n");

			elementCount = atoi(line.c_str());
		}
		else
		{
			file.close();
			return false;
		}

		isAspectDependent->resize(elementCount);

		m_data->resize(aspectCount);

		for (unsigned int iAspect = 0; iAspect < aspectCount; iAspect++)
		{
			m_data->at(iAspect).resize(elementCount);

			for (unsigned int iElement = 0; iElement < elementCount; iElement++)
			{
				m_data->at(iAspect).at(iElement).resize(4);
			}
		}

		int dependent = 0;

		for (unsigned int iElement = 0; iElement < elementCount; iElement++)
		{

			for (unsigned int iHeaderCount = 0; iHeaderCount < 2; iHeaderCount++)
			{
				if (std::getline(file, line))
				{
					switch (iHeaderCount)
					{
					case 0: OutputDebugString("Ele label: "); OutputDebugString(line.c_str()); OutputDebugString("\n"); break; //label
					case 1:
						OutputDebugString("Ele aspect dependence: ");
						OutputDebugString(line.c_str());
						OutputDebugString("\n");

						dependent = atof(line.c_str());

						if (dependent == 0) isAspectDependent->at(iElement) = false;
						else if (dependent == 1) isAspectDependent->at(iElement) = true;
					break;
					}
				}
				else
				{
					MessageBox(NULL, "Expected more lines to read but there where none. (Trying to read in Uniquness number).", "Error", MB_OK);
					file.close();
					return false;
				}
			}

			for (unsigned int iAspect = 0; iAspect < m_data->size(); iAspect++)
			{
				if (std::getline(file, line))
				{
					OutputDebugString("Ele path: ");
					OutputDebugString(line.c_str());
					OutputDebugString("\n");

					if (iAspect == 0 ) m_data->at(iAspect).at(iElement) = line.c_str();
					else if (dependent) m_data->at(iAspect).at(iElement) = line.c_str();
					else  m_data->at(iAspect).at(iElement) = "";
				}
				else
				{
					MessageBox(NULL, "Expected more lines to read but there where none.", "Error", MB_OK);
					file.close();
					return false;
				}
			}
		}
	}

	file.close();

	return true;
}