#include "StdAfx.h"
#include "Store.h"
#include "Factory.h"

CStore::CStore(void)
{
}

CStore::CStore(string _strKey)
{
	m_strKey = _strKey;
}
CStore::~CStore(void)
{
	Release();
}

void	CStore::Initialize(void)
{
	m_bDrag = false;
	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 508.f, 505.f);
	m_bOnOff = false;

	m_pCloseButton = CFactory<CUI>::CreateUI(0.f, 0.f, "Close");
}

void	CStore::Progress(DWORD _dwDelta)
{
	UIPicking();

	float fCloseX = m_tInfo.fX + m_tInfo.fCX / 2.f - 17;
	float fCloseY = m_tInfo.fY - m_tInfo.fCY / 2.f + 17;

	m_pCloseButton->SetPos(fCloseX, fCloseY);
}

void	CStore::Render(HDC hdc)
{
	BitBlt(hdc, 
	m_tInfo.fX - m_tInfo.fCX / 2.f, 
	m_tInfo.fY - m_tInfo.fCY / 2.f, 
	m_tInfo.fCX, m_tInfo.fCY, 
	(*m_pBitMap)[m_strKey]->GetMemdc(), 
	0, 0, SRCCOPY);

	m_pCloseButton->Render(hdc);
}

void	CStore::Release(void)
{
	for (size_t i = 0; i < IT_END; ++i)
	{
		for(vector<CItem*>::iterator iter = m_vecItemList[i].begin(); iter != m_vecItemList[i].end(); ++iter)
		{
			::Safe_Delete(*iter);
		}
	m_vecItemList[i].clear();
	}

	::Safe_Delete(m_pCloseButton);
}

RECT CStore::GetRect(void)
{
	RECT	rc = {
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}

void CStore::UIPicking(void)
{
	float fX = float(GetMouse().x - m_prevPT.x);
	float fY = float(GetMouse().y - m_prevPT.y);

	if (PtInRect(&m_pCloseButton->GetRect(), GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			m_bOnOff = false;
	}

	if(m_bDrag)
	{
		m_tInfo.fX += fX;
		m_tInfo.fY += fY;
	}


	
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if(PtInRect(&GetRect(), GetMouse()))
		{
			m_prevPT = GetMouse();
			m_bDrag = true;
		}
	}
	else
	{
		m_bDrag = false;
	}

}