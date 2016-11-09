#pragma once
#include "bigheader.h"

class CUI;

class CNPC
{
private:
	INFO		m_tInfo;
	SPRITE		m_tSprite;
	DWORD		m_dwTime;
	string		m_strKey;
	CBitBmp*	m_pBit;
	CUI*		m_pUI;
	bool		m_bDrag;
	POINT		m_prevPT;

public:
	RECT	GetRect(void);
	void	SetInventory(CUI* _pInventory);
	void	UIPicking(void);

public:
	void Initialize(void);
	void Progress(DWORD _delta);
	void Render(HDC hdc);
	void Release(void);
public:
	CNPC(void);
	CNPC(string _strKey);
	~CNPC(void);
};
