#include "KeybindData.h"

KeybindData::KeybindData()
{

}

KeybindData::~KeybindData()
{

}

bool KeybindData::WriteData(string path, vector<int> * binds)
{
	char iBuffer[10];

	ofstream file = ofstream(path, std::ios::binary);
	unsigned int size = binds->size();
	unsigned char * buffer = new unsigned char[size * 4];
	unsigned char * pBuffer = buffer;

	fill(pBuffer, pBuffer + size*4, 0);

	for (unsigned int i = 0; i < size; i++)
	{
		sprintf_s(iBuffer, "%03d\n",binds->at(i));
		strncpy((char*)pBuffer, iBuffer, sizeof(char)*4);
		pBuffer += sizeof(char)*4;
	}

	file.write((char*)buffer, size*4);
	file.close();

	return true;
}


bool KeybindData::ReadData(string path, vector<int> * binds)
{
	ifstream file(path);
	string line;

	if (file.is_open())
	{
		for (unsigned int i = 0; i < binds->size(); i++)
		{
			if (std::getline(file, line))
			{
				binds->at(i) = atoi(line.c_str());
			}
		}
	}

	file.close();

	return true;
}