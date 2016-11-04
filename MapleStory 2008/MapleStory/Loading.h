#pragma once

class CLoading
{
private:
	INFO		m_tInfo;
	SPRITE		m_tSprite;
	DWORD		m_dwTime;
	CBitBmp*	m_bmpLoading;
	bool		m_bDestroy;

public:
	bool GetDestroy(void);
	void Progress(DWORD _delta);
	void Render(HDC hdc);
	void Release(void);

public:
	CLoading(void);
	~CLoading(void);
};
