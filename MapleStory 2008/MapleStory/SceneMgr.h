#pragma once
#include "Bigheader.h"

class CScene;
class CParent;

class CSceneMgr
{
private:
	static	CSceneMgr*	m_pInstance;
	CScene*				m_pScene;
	CScene*				m_pSaveScene[SC_END];

public:
	void		SetScene(SCENEID	eScene);

	void		Progress(DWORD _delta);
	void		Render(HDC hdc);
	void		Release(void);

public:
	static CSceneMgr*	GetInstance(void)
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	void	DestroyInstance(void)
	{
		delete	m_pInstance;
		m_pInstance = NULL;
	}

private:
	CSceneMgr(void);
	~CSceneMgr(void);
};
