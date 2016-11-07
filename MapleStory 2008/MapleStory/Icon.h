#pragma once
#include "bigheader.h"

class CIcon
{
private:
	INFO		m_tInfo;
	ICONID		m_eID;
	DWORD		m_dwTime;
	CBitBmp*	m_pBit;
	string		m_strKey;
	

public:
	void	SetPos(float _fX, float _fY);
	void	Picking(void);
	RECT	GetRect(void);
	string	GetStrKey(void);

public:
	void	Initialize(void);
	void	Progress(DWORD _dwDelta);
	void	Render(HDC hdc);
	void	Release(void);
	
public:
	CIcon(void);
	CIcon(ICONID _eID, string _strName);
	CIcon(const CIcon &_Icon);
	~CIcon(void);
};
