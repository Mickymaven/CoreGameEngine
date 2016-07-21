
#include "Boidstorm.h"


Boidstorm::Boidstorm()
{
	

}

Boidstorm::~Boidstorm()
{

}

bool Boidstorm::Cast(float width, float height, LMVector3 * castPosition)
{
	//recieves a parameter cast location
	
	boidCount = 40;

	m_vecTotal = nullptr;

	m_boids.resize(boidCount);

	acceptableDistance = 12.0f;

	sweetbandWidth = 60.0f;

	visionRange = 70.0f;
	


	float randX = 0;
	float randZ = 0;


	float granularity = 100.0f;
	float radius = 180.0f;
	int modVal = (int)(2*radius)*granularity;

	for (int i = 0 ; i < boidCount; i++)
	{
		randX = castPosition->x + (rand() % modVal / granularity) - radius +0.5f;
		randZ = castPosition->z + (rand() % modVal / granularity) - radius +0.5f;

		m_boids[i] = new Boid (
			width, height,
			LMVector3(randX, castPosition->y + 9.0f, randZ),	//Position
			LMVector3(0.0f, 0.0f, 0.0f),		//Rotation
			LMVector3(0.25f, 0.25f, 0.25f),		//Scale
			LMVector3(0.1f, 0.0f, 0.1f),		//Velocity
			LMVector3(0.0f, 0.0f, 0.0f),		//Spin
			LMVector3(0.0f, 0.0f, 0.0f),		//Resize
			0.0f, 
			castPosition);

	}

	return true;
}

void Boidstorm::Update(float deltaTime)
{
	for (int i = 0; i < boidCount; i++)
	{
		//seperation
		//for each boid; for each other boid; if boid is too close; apply a weak force away from that boid
		GetActionVector(boidSeperation, m_boids[i], 0.0f, acceptableDistance);

		//cohesion
		//1. calculate flock center (or calculate flock centre of boids in a visual range radius)
		//2. Call boid update with flock centre parameeter
		//	to boid which then applies a weak force (addition) to the Velocity vector in direction
		GetActionVector(boidCohesion, m_boids[i], acceptableDistance + sweetbandWidth, visionRange);

		//alignment
		//calculate the average rotation of all boids (or a random sample)
		//apply a weak force to the rotation vector in the direction of the other boids
		GetAlignmentVector(m_boids[i], 2.0f, acceptableDistance + sweetbandWidth + 1.0f);
	}

	for (int i = 0; i < boidCount; i++) m_boids[i]->Update(deltaTime);
}

void Boidstorm::GetAlignmentVector(Boid * boid, float min, float max)
{
	m_vecTotal = boid->GetAlignmentVector();
	*m_vecTotal *= 0.0f;

	float length;
	for (int i = 0; i < boidCount; i++)
	{

		m_vec = boid->GetPhysicsObject()->GetPosition() - m_boids[i]->GetPhysicsObject()->GetPosition();
		distance = sqrt(abs(m_vec.x*m_vec.x + m_vec.y*m_vec.y + m_vec.z*m_vec.z));

		if (distance > min - 0.3f && distance + 0.3f < max)
		{
			m_vec = *m_boids[i]->GetCompositeVector();

			length = sqrt(abs(m_vec.x*m_vec.x + m_vec.y*m_vec.y + m_vec.z*m_vec.z));
			
			if (length > 0)
			{
				m_vec.x /= length;
				m_vec.y /= length;
				m_vec.z /= length;

				*m_vecTotal += m_vec;
			}
			
		}
	}

	length = abs(sqrt(m_vecTotal->x*m_vecTotal->x + m_vecTotal->y*m_vecTotal->y + m_vecTotal->z*m_vecTotal->z));
	
	if (length > 0)
	{
		m_vecTotal->x /= length;
		m_vecTotal->y /= length;
		m_vecTotal->z /= length;
	}
}

void Boidstorm::GetActionVector(BoidVectorTypes type, Boid * boid, float min, float max)
{
	if (type == boidCohesion) m_vecTotal = boid->GetCohesionVector();
	else if (type == boidSeperation)  m_vecTotal = boid->GetSeperationVector(); //seperation vectors
	*m_vecTotal *= 0.0f;



	for (int i = 0 ; i < boidCount; i++)
	{
		m_vec = boid->GetPhysicsObject()->GetPosition() - m_boids[i]->GetPhysicsObject()->GetPosition();
		distance = sqrt(abs(m_vec.x*m_vec.x + m_vec.y*m_vec.y + m_vec.z*m_vec.z));

		if (distance > min-0.3f && distance+0.3f < max)
		{ 
			//for seperation ....   y = -x
			mag = max - min;
			x = distance / mag;

			switch (type)
			{
			case boidSeperation:
				mult = 1 - x;
				m_vec *= mult;
				break;
			case boidCohesion:
				break;
			}

			*m_vecTotal += m_vec;
			//m_vecTotal += (m_vec * (1.0f + ((maxSq - minSq) - ((distanceSquared / (maxSq - minSq) * (maxSq - minSq))))));
		}
	}

	if (type == boidCohesion)
	{
		m_vecTotal->x *= -1.0f; //cohesion vectors
		m_vecTotal->y *= -1.0f; //cohesion vectors
		m_vecTotal->z *= -1.0f; //cohesion vectors
	}
	else if (type == boidSeperation) *m_vecTotal * 1.0f; //seperation vectors
}



vector<Boid *> * Boidstorm::GetBoids() { return &m_boids; }