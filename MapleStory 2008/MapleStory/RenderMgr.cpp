#include "StdAfx.h"
#include "RenderMgr.h"

CRenderMgr* CRenderMgr::m_pInstance = NULL; 

CRenderMgr::CRenderMgr(void)
{
}

CRenderMgr::~CRenderMgr(void)
{
}

void CRenderMgr::AddUI(CUI* pUI)
{
	m_MapRenderUI.insert(make_pair(float(pUI->GetRect().bottom), pUI));
}

void CRenderMgr::RenderUI(HDC hdc)
{
	for(multimap<float, CUI*>::iterator iter = m_MapRenderUI.begin();
		iter != m_MapRenderUI.end(); ++iter)
	{
		iter->second->Render(hdc);
	}
}

void CRenderMgr::UIClear(void)
{
	m_MapRenderUI.clear();
}
