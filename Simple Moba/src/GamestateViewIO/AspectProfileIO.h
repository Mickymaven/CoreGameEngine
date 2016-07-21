#if !defined(ASPECTPROFILEIO_H)
#define ASPECTPROFILEIO_H

#include "ProfileIOBase.h"

#include "../GamestateView/AspectProfile.h"


class AspectProfileIO : public ProfileIOBase
{
protected:
	AspectProfile * aspectProfile;

public:
	AspectProfileIO();
	~AspectProfileIO();

	//bool WriteData(string path, vector<int> * binds);
	bool ReadData(string path, AspectProfile * aspectProfile);
};

#endif