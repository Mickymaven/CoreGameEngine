#if !defined (BOIDSTORM_H)
#define BOIDSTORM_H

#include <ctime>
#include<vector>

using namespace std;


#include "Boid.h"
#include "../../../EngineGameModuleDirectX9/src/Graphics/LMMesh.h"

enum BoidVectorTypes
{
	boidCohesion,
	boidSeperation,
	boidAlignment
};


class Boidstorm {


private:
	vector<Boid *> m_boids;
	int boidCount;

	float acceptableDistance;
	float sweetbandWidth;
	float visionRange;

	float distance;

	LMVector3 * m_vecTotal;
	LMVector3 m_vec;

	//vector<vector<D3DXVECTOR3 *>> boidTest;


	float mag;
	float x;
	float mult;

public:
	Boidstorm();
	virtual ~Boidstorm();
	bool Cast(float width, float height, LMVector3 * castPosition);
	void Update(float deltaTime);

	//ikky set stuff in a pointer to break OO principles stuff
	void GetAlignmentVector(Boid * boid, float min, float max);
	void GetActionVector(BoidVectorTypes type, Boid * boid, float min, float max);

	//Accessors
	vector<Boid *> * GetBoids();


};



#endif
