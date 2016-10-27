#pragma once
#include "Bigheader.h"

class CBitBmp
{
private:
	HDC		m_hdc;
	HDC		m_Memdc;
	HBITMAP	m_bitmap;
	HBITMAP	m_oldmap;

public:
	CBitBmp* LoadBmp(TCHAR*	_pFileName);
	HDC GetMemdc(void);
	void Release(void);

public:
	CBitBmp(void);
	~CBitBmp(void);
};
