#include "RandomGenerator.h"

RandomGenerator* RandomGenerator::instance = nullptr;
RandomGenerator::RandomGenerator()
{
}


RandomGenerator::~RandomGenerator()
{
}

RandomGenerator& RandomGenerator::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new RandomGenerator;
		srand(time(nullptr));
	}
	return *instance;
}

float RandomGenerator::GetFloat(float val)const
{
	int int_val = (int)(val * 1000000);
	int rand_num = rand();
	rand_num <<= 16;
	rand_num |= rand();
	int_val = rand_num % int_val;
	return int_val / 1000000.0;
}

float RandomGenerator::GetFloat(float _val_1, float _val_2)const
{
	if (_val_1 > _val_2)
	{
		float temp = _val_1;
		_val_1 = _val_2;
		_val_2 = temp;
	}
	float dist = _val_2 - _val_1;
	float ran = GetFloat(dist);
	return _val_1 + ran;
}

int RandomGenerator::GetInt32(int val)const
{
	int rand_num = rand();
	rand_num <<= 16;
	rand_num |= rand();
	return rand_num % val;
}

int RandomGenerator::GetInt32(int _val_1,int _val_2)const
{
	if (_val_1 > _val_2)
	{
		int temp = _val_1;
		_val_1 = _val_2;
		_val_2 = temp;
	}
	int dist = _val_2 - _val_1;
	int ran = GetInt32(dist);
	return _val_1 + ran;
}
