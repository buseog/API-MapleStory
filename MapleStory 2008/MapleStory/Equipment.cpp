#include "StdAfx.h"
#include "Equipment.h"
#include "Factory.h"

CEquipment::CEquipment(void)
{
	for (int i = 0; i < EQ_END; ++i)
	{
		m_pEquipItem[i] = NULL;
	}
}

CEquipment::~CEquipment(void)
{
	Release();
}

void CEquipment::Initialize(void)
{
	m_iPriority = UI_EQUIPMENT;
	m_bOnOff = false;
	m_ReturnItem = NULL;
	m_strKey = "Equipment";
	m_tInfo = INFO(0, 0, 237.f, 332.f);

	m_pCloseButton = CFactory<CUI>::CreateUI(0.f, 0.f, "Close");
}

void CEquipment::Progress(DWORD _delta)
{
	UIPicking();
	ItemPos();

	for (int i = 0; i < EQ_END; ++i)
	{
		if (m_pEquipItem[i])
			m_pEquipItem[i]->Progress(_delta);
	}
}

void CEquipment::Render(HDC hdc)
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

	for (size_t i = 0; i < EQ_END; ++i)
	{
		if (m_pEquipItem[i])
			m_pEquipItem[i]->Render(hdc);
	}

	m_pCloseButton->Render(hdc);
}

void CEquipment::Release(void)
{
	::Safe_Delete(m_pCloseButton);

	for (int i = 0; i < EQ_END; ++i)
	{
		::Safe_Delete(m_pEquipItem[i]);
	}
}

void CEquipment::EquipItem(CItem*	_pItem)
{
	((CPlayer*)m_pPlayer)->EquipItem(_pItem);

	if (_pItem)
	{
		switch (_pItem->GetItem().iType)
		{
		case IT_WEAPON:
			if (m_pEquipItem[EQ_WEAPON] == NULL)
			{
				m_pEquipItem[EQ_WEAPON] = _pItem;
				m_pEquipItem[EQ_WEAPON]->SetPos(m_tInfo.fX - 40.f, m_tInfo.fY + 30.f);
			}
			else
			{
				m_ReturnItem = m_pEquipItem[EQ_WEAPON];
				m_pEquipItem[EQ_WEAPON] = _pItem;
				m_pEquipItem[EQ_WEAPON]->SetPos(m_tInfo.fX - 40.f, m_tInfo.fY + 30.f);
			}
			break;

		case IT_ARMOR:
			if (m_pEquipItem[EQ_ARMOR] == NULL)
			{
				m_pEquipItem[EQ_ARMOR] = _pItem;
				m_pEquipItem[EQ_ARMOR]->SetPos(m_tInfo.fX, m_tInfo.fY + 30.f);

			}
			else
			{
				m_ReturnItem = m_pEquipItem[EQ_ARMOR];
				m_pEquipItem[EQ_ARMOR] = _pItem;
				m_pEquipItem[EQ_ARMOR]->SetPos(m_tInfo.fX, m_tInfo.fY + 30.f);
			}
			break;

		case IT_GLOVE:
			if (m_pEquipItem[EQ_GLOVE] == NULL)
			{
				m_pEquipItem[EQ_GLOVE] = _pItem;
				m_pEquipItem[EQ_GLOVE]->SetPos(m_tInfo.fX + 40.f, m_tInfo.fY + 65.f);
			}
			else
			{
				m_ReturnItem = m_pEquipItem[EQ_GLOVE];
				m_pEquipItem[EQ_GLOVE] = _pItem;
				m_pEquipItem[EQ_GLOVE]->SetPos(m_tInfo.fX + 40.f, m_tInfo.fY + 65.f);
			}
			break;
		}
	}
}


void CEquipment::ItemPos(void)
{
	//WEAPON = fX - 40;, fY + 30;
	//ARMOR = fX, fY + 30;
	//GLOVE = fX + 40,fY + 65;
	
	if (m_pEquipItem[EQ_WEAPON])
		m_pEquipItem[EQ_WEAPON]->SetPos(m_tInfo.fX - 40.f, m_tInfo.fY + 30.f);

	if (m_pEquipItem[EQ_ARMOR])
		m_pEquipItem[EQ_ARMOR]->SetPos(m_tInfo.fX, m_tInfo.fY + 30.f);

	if (m_pEquipItem[EQ_GLOVE])
		m_pEquipItem[EQ_GLOVE]->SetPos(m_tInfo.fX + 40.f, m_tInfo.fY + 65.f);

	float fCloseX = m_tInfo.fX + m_tInfo.fCX / 2.f - 17.f;
	float fCloseY = m_tInfo.fY - m_tInfo.fCY / 2.f + 12.f;

	m_pCloseButton->SetPos(fCloseX, fCloseY);
}

RECT CEquipment::GetRect(void)
{
	RECT	rc = {
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}


void CEquipment::UIPicking(void)
{
	if (PtInRect(&m_pCloseButton->GetRect(), GetMouse()))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			m_bOnOff = false;
	}

	for (size_t i = 0; i < EQ_END; ++i)
	{
		if (m_pEquipItem[i])
		{
			if(PtInRect(&m_pEquipItem[i]->GetRect(), GetMouse()))
			{
				if (GetAsyncKeyState(VK_RBUTTON))
				{
					m_ReturnItem = m_pEquipItem[i];
					((CPlayer*)m_pPlayer)->UnEquipItem(m_pEquipItem[i]);
					m_pEquipItem[i] = NULL;
				}			
			}
		}
	}
}