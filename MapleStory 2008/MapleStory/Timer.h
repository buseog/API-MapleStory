#pragma once

class CTimer
{
public:
	DWORD dwRemainTime[10];

public:
	void TimeSetting(void);

public:
	CTimer(void);
	~CTimer(void);
};
