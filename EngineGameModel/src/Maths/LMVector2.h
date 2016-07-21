#if !defined(LMVECTOR2_H)

#define LMVECTOR2_H


class LMVector2
{

public:

	float x;
	float y;

	LMVector2();
	LMVector2(float fx, float fy);
	LMVector2(LMVector2 & v);
	~LMVector2();

	void operator += (const LMVector2& v);
	void operator -= (const LMVector2& v);
	void operator *= (const LMVector2& v);
	void operator /= (const LMVector2& v);

	bool operator == (const LMVector2 & v);
	bool operator != (const LMVector2 & v);


};


#endif