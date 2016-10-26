#pragma once
#include "define.h"

class CScene;

class CSceneMgr
{
private:
	CScene*			m_pScene;

public:
	void		SetScene(SCENEID	eScene);
	void		Progress(void);
	void		Render(HDC hdc);
	void		Release(void);


private:
	static	CSceneMgr*		m_pInstance;

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

public:
	CSceneMgr(void);
	~CSceneMgr(void);
};
