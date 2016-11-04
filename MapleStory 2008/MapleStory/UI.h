#pragma once
#include "bigheader.h"

class CItem;

class CUI
{
protected:
	INFO	m_tInfo;
	SPRITE	m_tSprite;
	int		m_iDrawID;
	float	m_fPercent[2];
	DWORD	m_dwTime;
	CItem*	m_ReturnItem;

	string	m_strKey;
	static	map<string, CBitBmp*>*	m_pBitMap;

public:
	static void SetBitMap(map<string, CBitBmp*>* _pBitMap);
	void	SetPercent(float _fHp, float _fExp);
	void	SetPos(float _fX, float _fY);
	INFO	GetInfo(void);
	CItem*	GetReturnItem(void);
	void	SetReturnItem(void);

public:
	virtual void UIPicking(void);
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CUI(void);
	CUI(string _strKey);
	virtual ~CUI(void);
};
