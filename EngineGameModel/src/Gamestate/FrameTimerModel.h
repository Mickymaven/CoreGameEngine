#if !defined (FRAMETIMERMODEL_H)
#define FRAMETIMERMODEL_H

#include <vector>
using namespace std;

class FrameTimerModel
{
protected:
	vector<float> m_frameTimes;
	unsigned int m_thisFrameIndex;
	unsigned int m_frameTimeSize;


	float m_frameTimeAverage;



public:
	FrameTimerModel();
	~FrameTimerModel();

	void Update(float deltaTime);
	
	float GetFrameTimeAverage();
	float GetFPSAverage();
};


#endif