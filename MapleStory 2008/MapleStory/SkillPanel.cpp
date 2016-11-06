#include "StdAfx.h"
#include "SkillPanel.h"
#include "Factory.h"

CSkillPanel::CSkillPanel(void)
{
}

CSkillPanel::~CSkillPanel(void)
{
	Release();
}

void CSkillPanel::Initialize(void)
{
	m_pPick = NULL;
	m_bOnOff = false;
	m_strKey = "SkillPanel";
	m_tInfo = INFO(0, 0, 174.f, 300.f);

	m_pIcon[0] = new CIcon(IC_SKILL, "Typhoon_ON");
	m_pIcon[1] = new CIcon(IC_SKILL, "Bolt_ON");
	m_pIcon[2] = new CIcon(IC_SKILL, "Beyond_ON");
	m_pIcon[3] = new CIcon(IC_SKILL, "Annihilation_ON");

	m_pCloseButton = CFactory<CUI>::CreateUI(0.f, 0.f, "Close");

	for (int i = 0; i < SKILLPANELSLOT; ++i)
	{
		if (m_pIcon[i])
		{
			m_pIcon[i]->Initialize();
		}
	}
}

void CSkillPanel::Progress(DWORD _delta)
{
	UIPicking();

	float fCloseX = m_tInfo.fX + m_tInfo.fCX / 2.f - 17.f;
	float fCloseY = m_tInfo.fY - m_tInfo.fCY / 2.f + 12.f;

	m_pCloseButton->SetPos(fCloseX, fCloseY);

	for (int i = 0; i < SKILLPANELSLOT; ++i)
	{
		if (m_pIcon[i])
		{
			m_pIcon[i]->SetPos(m_tInfo.fX - 60.f, m_tInfo.fY - 40.f + (35 * i));
			m_pIcon[i]->Progress(_delta);
		}
	}

	if (m_pPick)
		m_pPick->SetPos((float)GetMouse().x, (float)GetMouse().y);
}

void CSkillPanel::Render(HDC hdc)
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

	for (int i = 0; i < SKILLPANELSLOT; ++i)
	{
		if (m_pIcon[i])
		{
			m_pIcon[i]->Render(hdc);
		}
	}

	if (m_pPick)
		m_pPick->Render(hdc);


	m_pCloseButton->Render(hdc);
}

void CSkillPanel::Release(void)
{
	
	for (int i = 0; i < SKILLPANELSLOT; ++i)
	{
		if (m_pIcon[i])
		{
			::Safe_Delete(m_pIcon[i]);
		}
	}

	::Safe_Delete(m_pCloseButton);
}

RECT CSkillPanel::GetRect(void)
{
	RECT	rc = {
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}

void CSkillPanel::UIPicking(void)
{
	if (PtInRect(&m_pCloseButton->GetRect(), GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			m_bOnOff = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON) && m_pPick)
	{
		::Safe_Delete(m_pPick);
	}

	for (int i = 0; i < SKILLPANELSLOT; ++i)
	{
		if (m_pIcon[i])
		{
			if(PtInRect(&m_pIcon[i]->GetRect(), GetMouse()))
			{
				if (GetAsyncKeyState(VK_LBUTTON))
				{
					if (m_pPick == NULL)
					{
						m_pPick = new CIcon(*m_pIcon[i]);
					}
				}
			}
		}
	}
}