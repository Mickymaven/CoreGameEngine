#include "DialogBehaviorIO.h"

DialogBehaviorIO::DialogBehaviorIO()
{

}

DialogBehaviorIO::~DialogBehaviorIO()
{

}

bool DialogBehaviorIO::ReadData(string path, DialogBehavior * dialogBehavior)
{
	ifstream file(path);
	string line;

	vector < DialogScreenData > * m_data = dialogBehavior->GetDialogScreens();

	if (file.is_open())
	{
		for (unsigned int screenCount = 0; screenCount < m_data->size(); screenCount++)
		{
			for (unsigned int lineCount = 0; lineCount < 2 + m_data->at(screenCount).m_options.size(); lineCount++)
			{
				if (std::getline(file, line))
				{
					if (lineCount == 0) OutputDebugString(line.c_str());
					else if (lineCount == 1)  m_data->at(screenCount).m_dialogText = line.c_str();
					else m_data->at(screenCount).m_options.at(lineCount - 2)->m_text = line.c_str();
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