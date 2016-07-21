#include "AspectProfileIO.h"

AspectProfileIO::AspectProfileIO()
{

}

AspectProfileIO::~AspectProfileIO()
{

}

bool AspectProfileIO::ReadData(string path, AspectProfile * aspectProfile)
{
	ifstream file(path);
	string line;

	int elementCount = 0;
	vector<vector<vector<float>>> * m_data = aspectProfile->GetData();

	if (file.is_open())
	{
		//Get Element count
		if (std::getline(file, line))
		{
			elementCount = atoi(line.c_str());
		}
		else
		{
			file.close();
			return false;
		}

		m_data->resize(aspectCount);
		for (unsigned int iAspect = 0; iAspect < aspectCount; iAspect++)
		{
			m_data->at(iAspect).resize(elementCount);

			for (unsigned int iElement = 0; iElement < elementCount; iElement++)
			{
				m_data->at(iAspect).at(iElement).resize(9);
			}
		}

		for (unsigned int iAspect = 0; iAspect < m_data->size(); iAspect++)
		{
			if (std::getline(file, line)) { OutputDebugString("===this aspect\===\n"); }
			else
			{
				MessageBox(NULL, "Expected more lines to read but there where none.", "Error", MB_OK);
				file.close();
				return false;
			}

			for (unsigned int iElement = 0; iElement < m_data->at(iAspect).size(); iElement++)
			{
				for (unsigned int recordIndex = 0; recordIndex < 10; recordIndex++)
				{
					if (std::getline(file, line))
					{
						switch (recordIndex)
						{
						case 0://OutputDebugString(line.c_str());//label
							break;
						case 1://Horizontal align %
						case 2://Vertical Align %
						case 3://position x
						case 4://position-y
						case 5://scale
						case 6://size-x
						case 7://size-y
						case 8://Res Width
						case 9://Res Height
							m_data->at(iAspect).at(iElement).at(recordIndex-1) =
								atof(line.c_str());
							break;
						};
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
	}

	file.close();

	return true;
}