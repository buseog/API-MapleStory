#pragma once
#include "UI.h"

class CRenderMgr
{
private:
	static CRenderMgr*		m_pInstance;
	multimap<float, CUI*>	m_MapRenderUI;

public:
	void	AddUI(CUI* pUI);
	void	RenderUI(HDC hdc);
	void	UIClear(void);

public:
	static CRenderMgr*		GetInstance(void)
	{
		if(m_pInstance == NULL)
			m_pInstance = new CRenderMgr;

		return m_pInstance;
	}
	void DestroyInst(void)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}

private:
	CRenderMgr(void);
	~CRenderMgr(void);
};