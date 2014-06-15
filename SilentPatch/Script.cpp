#include "StdAfx.h"
#include "Script.h"

static int*		StatTypesInt = *(int**)0x55C0D8;

std::pair<int,int>* CRunningScript::GetDay_GymGlitch()
{
	static std::pair<int,int>	Out;

	if ( !strncmp(Name, "gymbike", 8) || !strncmp(Name, "gymbenc", 8) || !strncmp(Name, "gymtrea", 8) || !strncmp(Name, "gymdumb", 8) )
	{
		Out.first = 0xFFFFFFFF;
		Out.second = StatTypesInt[134-120];
	}
	else
	{
		Out.first = nGameClockMonths;
		Out.second = nGameClockDays;
	}

	return &Out;
}