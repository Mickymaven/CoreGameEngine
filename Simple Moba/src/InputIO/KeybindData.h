#if !defined(KEYBINDDATA_H)
#define KEYBINDDATA_H

#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include <algorithm>
using std::fill;



class KeybindData
{
protected:


public:
	KeybindData();
	~KeybindData();

	bool WriteData(string path, vector<int> * binds);

	bool ReadData(string path, vector<int> * binds);
};

#endif