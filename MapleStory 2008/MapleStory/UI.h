#pragma once
#include "bigheader.h"
#include "Scene.h"

class CUI
{
protected:
	INFO	m_tInfo;
	SPRITE	m_tSprite;
	int		m_iDrawID;
	DWORD	m_dwTime;

	string	m_strKey;
	static	map<string, CBitBmp*>*	m_pBitMap;

public:
	static void SetBitMap(map<string, CBitBmp*>* _pBitMap);
	void	SetPos(float _fX, float _fY);
	RECT	GetRect(void);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CUI(void);
	CUI(string _strKey);
	virtual ~CUI(void);
};
