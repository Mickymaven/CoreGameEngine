#if !defined(LIGHTCLASS_H)
#define LIGHTCLASS_H

class LightClass
{

private:
	float m_diffuseColor[4];
	float m_direction[3];
	float m_ambientLight[4];

public:
	LightClass();
	LightClass(const LightClass& other);
	~LightClass();

	void SetDiffuseColor(float red, float green, float blue, float alpha);
	void SetDirection(float x, float y, float z);
	void SetAmbientLight(float red, float green, float blue, float alpha);

	void GetDiffuseColor(float* color);
	void GetDirection(float* direction);
	void GetAmbientLight(float* ambient);

};

#endif

