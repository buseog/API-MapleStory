#pragma once
#include "bigheader.h"

class CUI;

class CNPC
{
private:
	INFO		m_tInfo;
	SPRITE		m_tSprite;
	DWORD		m_dwTime;
	CBitBmp*	m_pBit;
	CUI*		m_pStore;

public:
	RECT	GetRect(void);
	void	SetInventory(CUI* _pInventory);

public:
	void Initialize(void);
	void Progress(DWORD _delta);
	void Render(HDC hdc);
	void Release(void);
public:
	CNPC(void);
	~CNPC(void);
};
