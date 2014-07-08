#include"SystemVar.h"

SystemVars* SystemVars::instance = nullptr;

SystemVars& SystemVars::GetInstance()
{
	if (instance == nullptr)
		instance = new SystemVars;
	return *instance;
}

SystemVars::SystemVars()
{
	screenWidth = 0;
	screenHeight = 0;
}

SystemVars::~SystemVars()
{
	;
}

UINT SystemVars::GetScreenHeight()
{
	return screenHeight;
}

UINT SystemVars::GetScreenWidth()
{
	return screenWidth;
}

void SystemVars::SetScreenHeight(UINT _)
{
	screenHeight = _;
	return;
}

void SystemVars::SetScreenWidth(UINT _)
{
	screenWidth = _;
	return;
}