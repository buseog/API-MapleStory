#pragma once
#include "define.h"

class CMainGame
{
private:
	HDC		m_hdc;

public:
	void Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);
public:
	CMainGame(void);
	~CMainGame(void);
};
