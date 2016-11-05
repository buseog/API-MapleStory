#pragma once
#include "bigheader.h"

class CNPC
{
private:
	INFO		m_tInfo;
	SPRITE		m_tSprite;
	DWORD		m_dwTime;
	CBitBmp*	m_pBit;

public:
	RECT GetRect(void);
public:
	void Initialize(void);
	void Progress(DWORD _delta);
	void Render(HDC hdc);
	void Release(void);
public:
	CNPC(void);
	~CNPC(void);
};
