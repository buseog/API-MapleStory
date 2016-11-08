#include "StdAfx.h"
#include "Timer.h"

CTimer::CTimer(void)
{
}

CTimer::~CTimer(void)
{
}

void CTimer::TimeSetting(void)
{
	for(int i = 0; i < 10; ++i)
	{
		fRemainTime[i] = 0.f;
	}
}