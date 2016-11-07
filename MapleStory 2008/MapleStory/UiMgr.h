#pragma once
#include "Ui.h"

class CParent;

class CUiMgr
{
private:
	static CUiMgr*	m_pInstance;
	vector<CUI*>	m_vecUI[UI_END];
	CUI*			m_pUI;
	bool			m_bDrag;
	POINT			m_prevPT;
	DWORD			m_dwKey;

public:
	void	UIDrag(void);
	void	KeyInput(void);

public:
	void	Initialize(void);
	void	Progress(DWORD _delta);
	void	Render(HDC hdc);
	void	Release(void);

public:
	static CUiMgr*	GetInstance(void)
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new CUiMgr;
		}
		return m_pInstance;
	}

	void	DestroyInstance(void)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}

private:
	CUiMgr(void);
	~CUiMgr(void);
};
