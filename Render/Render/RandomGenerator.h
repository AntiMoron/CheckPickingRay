#pragma once

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<random>

class RandomGenerator
{
private:
	static RandomGenerator* instance;
//	std::uniform_int_distribution<int> m_generator;
	RandomGenerator();
	~RandomGenerator();
public:
	static RandomGenerator& GetInstance();

	//Get a random float number between 0.0f & val
	float GetFloat(float val) const;
	//Get a random float number between _val_1 & _val_2
	float GetFloat(float _val_1, float _val_2)const;

	int GetInt32(int val)const;
	int GetInt32(int _val_1,int _val_2)const;
};

#define RNG (RandomGenerator::GetInstance())