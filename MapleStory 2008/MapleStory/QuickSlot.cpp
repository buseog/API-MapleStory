#include "StdAfx.h"
#include "QuickSlot.h"
#include "SkillPanel.h"

CQuickSlot::CQuickSlot(void)
{
}

CQuickSlot::~CQuickSlot(void)
{
	Release();
}

void CQuickSlot::Initialize(void)
{
	m_bExpress = false;
	m_pPanel = NULL;
	m_pPick = NULL;
	m_strKey = "QuickSlot";
	m_tInfo = INFO(0, 0, 140.f, 80.f);

	m_vecSlot.reserve(8);
	m_vecSlot.resize(8);

	m_vecCool.reserve(8);
	m_vecCool.resize(8);

	for (int i = 0; i < QUICKSLOT; ++i)
	{
		if (!m_vecSlot[i])
		{
			m_vecSlot[i] = new CIcon(IC_SKILL, "Empty");
			m_vecSlot[i]->Initialize();

			m_vecCool[i] = new CIcon(IC_SKILL, "Empty");
			m_vecCool[i]->Initialize();
			m_fCoolTime[i] = 0.f;
		}
	}
}

void CQuickSlot::Progress(DWORD _delta)
{
	UIPicking();
	SetSkillOff();
	IconPos();
	
	if (m_bExpress)
	{
		if (m_tInfo.fY > 490)
			m_tInfo.fY -= 5.f;
	}
	else
	{
		if (m_tInfo.fY < 580)
			m_tInfo.fY += 5.f;

		m_tInfo.fX = 730.f;
	}

	for (int i = 0; i < QUICKSLOT; ++i)
	{
		if(m_vecSlot[i]->GetStrKey() != "Empty")
		{
			m_fCoolTime[i] += _delta;
			float fPercent = m_fCoolTime[i] / 1000.f;

			if (fPercent >= 1)
				fPercent = 1.f;
			
			m_vecSlot[i]->SetCoolTime(fPercent);
		}
	}
}

void CQuickSlot::Render(HDC hdc)
{
	BitBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		0,
		0,
		SRCCOPY);

	for (int i = 0; i < QUICKSLOT; ++i)
	{
		m_vecCool[i]->Render(hdc);
	}


	for (int i = 0; i < QUICKSLOT; ++i)
	{
		m_vecSlot[i]->Render(hdc);
	}
}

void CQuickSlot::Release(void)
{
	for (int i = 0; i < QUICKSLOT; ++i)
	{
		::Safe_Delete(m_vecSlot[i]);
	}
	m_vecSlot.clear();

	for (int i = 0; i < QUICKSLOT; ++i)
	{
		::Safe_Delete(m_vecCool[i]);
	}
	m_vecCool.clear();
}

RECT CQuickSlot::GetRect(void)
{
	RECT	rc = {

		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f)
	};

	return rc;
}

void CQuickSlot::UIPicking(void)
{
	m_pPick = ((CSkillPanel*)m_pPanel)->GetPickIcon();

	for (int i = 0; i < QUICKSLOT; ++i)
	{
		if(PtInRect(&m_vecSlot[i]->GetRect(), GetMouse()))
		{
			if (GetAsyncKeyState(VK_LBUTTON))
			{
				if (m_pPick)
				{
					::Safe_Delete(m_vecSlot[i]);
					m_vecSlot[i] = new CIcon(*m_pPick);
					((CSkillPanel*)m_pPanel)->SetPickIcon();
				}
			}
		}
	}
}

void CQuickSlot::SetExpress(void)
{
	if (m_bExpress)
		m_bExpress = false;

	else
		m_bExpress = true;
}

void CQuickSlot::IconPos(void)
{
	float fItemX = m_tInfo.fX - 55;
	float fItemY = m_tInfo.fY - 20;

	int iCount = 0;

	for (int i = 0; i < 8; ++i)
	{
		int iX = iCount / 4;
		int iY = iCount - (iX * 4);

		m_vecSlot[i]->SetPos(fItemX + (35 * iY), fItemY + (40 * iX));
		m_vecCool[i]->SetPos(fItemX + (35 * iY), fItemY + (40 * iX));

		++iCount;
	}
}

void	CQuickSlot::SetPanel(CUI*	_pPanel)
{
	m_pPanel = _pPanel;
}

vector<CIcon*>*	CQuickSlot::GetSlot(void)
{
	return &m_vecSlot;
}

void CQuickSlot::SetCooltime(int _iNum, float _fCool)
{
	m_fCoolTime[_iNum] = _fCool;
}

void	CQuickSlot::SetSkillOff(void)
{
	for (int i = 0; i < QUICKSLOT; ++i)
	{
		if (m_vecSlot[i]->GetStrKey() == "Typhoon_ON")
		{
			::Safe_Delete(m_vecCool[i]);
			m_vecCool[i] = new CIcon(IC_SKILL, "Typhoon_OFF");
			m_vecCool[i]->Initialize();
		}
		else if (m_vecSlot[i]->GetStrKey() == "Bolt_ON")
		{
			::Safe_Delete(m_vecCool[i]);
			m_vecCool[i] = new CIcon(IC_SKILL, "Bolt_OFF");
			m_vecCool[i]->Initialize();
		}
		else if (m_vecSlot[i]->GetStrKey() == "Beyond_ON")
		{
			::Safe_Delete(m_vecCool[i]);
			m_vecCool[i] = new CIcon(IC_SKILL, "Beyond_OFF");
			m_vecCool[i]->Initialize();
		}
		else if (m_vecSlot[i]->GetStrKey() == "Annihilation_ON")
		{
			::Safe_Delete(m_vecCool[i]);
			m_vecCool[i] = new CIcon(IC_SKILL, "Annihilation_OFF");
			m_vecCool[i]->Initialize();
		}
		else if (m_vecSlot[i]->GetStrKey() == "Range_ON")
		{
			::Safe_Delete(m_vecCool[i]);
			m_vecCool[i] = new CIcon(IC_SKILL, "Range_OFF");
			m_vecCool[i]->Initialize();
		}
	}
}