#include "StdAfx.h"
#include "RenderMgr.h"
#include "Ui.h"

CRenderMgr* CRenderMgr::m_pInstance = NULL; 

CRenderMgr::CRenderMgr(void)
{
}

CRenderMgr::~CRenderMgr(void)
{
}

void CRenderMgr::AddUI(CUI* pUI)
{
	m_MapRenderUI.insert(make_pair(pUI->GetPriority(), pUI));
}

void CRenderMgr::RenderUI(HDC hdc)
{
	for(multimap<int, CUI*>::iterator iter = m_MapRenderUI.begin();
		iter != m_MapRenderUI.end(); ++iter)
	{
		iter->second->Render(hdc);
	}
}

void CRenderMgr::UIClear(void)
{
	m_MapRenderUI.clear();
}
