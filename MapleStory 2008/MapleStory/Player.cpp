#include "StdAfx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Factory.h"
#include "Skill.h"
#include "QuickSlot.h"
#include "Item.h"


CPlayer::CPlayer(void)
:m_pSkill(NULL)
,m_iBeyond(0)
,m_pSlot(NULL)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_cTimer.TimeSetting();
	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 70.f, 90.f);
	m_tStat = STAT(1000.f, 1000.f, 450.f, 0.f, 1, 0.f, 4.f, 1000);
	m_tSprite = SPRITE(0, 5, 0, 80);
	m_fOriginAttack = m_tStat.fAttack;
	m_fOriginDefense = m_tStat.fDefense;

	m_dwTime = GetTickCount();
	m_strKey = "Player_LEFT";
	m_dwKey = 0;

	m_ptOffset.x = WINCX / 2;
	m_ptOffset.y = WINCY / 2;
}

void CPlayer::Progress(DWORD _delta)
{
	KeyInput(_delta);
	Rotation();
	Gravity();
	ScrollX();
	ScrollY();

	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
 		if ((m_dwState != ST_STAND) && (m_dwState != ST_PROSTRATE) && (m_dwState != ST_JUMP) && (m_dwState != ST_UP) &&  (m_dwState != ST_HIT))
			m_dwState = ST_STAND;

		m_tSprite.iStart = 0;
	}

	if(m_bUnbeatable)
		if ((m_cTimer.fRemainTime[9] += _delta) >= 1100)
		{
			m_bUnbeatable = false;
			m_dwState = ST_STAND;
			m_cTimer.fRemainTime[9] = 0;

		}


	SetState(ST_STAND, 5, 0, 80);
	SetState(ST_WALK, 3, 1, 100);
	SetState(ST_JUMP, 1, 6, 100);
	SetState(ST_ATTACK, 3, 2, 100);
	SetState(ST_ATTACK2, 4, 3, 100);
	SetState(ST_UP, 1, 8, 100);
	SetState(ST_PROSTRATE, 1, 5, 100);
	SetState(ST_HIT, 3, 7, 30);
}

void CPlayer::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_ptScroll.x),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + m_ptScroll.y),
		int(m_tInfo.fCX), 
		int(m_tInfo.fCY), 
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		int(m_tInfo.fCX * m_tSprite.iStart), 
		int(m_tInfo.fCY * m_tSprite.iMotion),
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY, 
		RGB(255, 255, 250));

	
		TCHAR szName[128] = L"";
		wsprintf(szName, L"%d",(int) m_tInfo.fX);
					TextOut(hdc,
						0,0,
						szName, lstrlen(szName));

		wsprintf(szName, L"%d", (int)m_tInfo.fY);
					TextOut(hdc,
						0, 20,
						szName, lstrlen(szName));
}

void CPlayer::Release(void)
{
}

void CPlayer::KeyInput(DWORD _delta)
{
	m_dwKey = CKeyMgr::GetInstance()->GetKey();

	if (!m_dwKey && (m_dwState != ST_ATTACK) && (m_dwState != ST_ATTACK2) && (m_dwState != ST_UP) && (m_bLand == true) && (m_dwState != ST_HIT))
	{
   		m_dwState = ST_STAND;
	}

	if (m_dwKey && (m_dwKey != KEY_UP) && (m_dwState != ST_ATTACK) && (m_dwState != ST_ATTACK2) && (m_dwState != ST_PROSTRATE) && (m_dwState != ST_UP) && (m_bLand == true))
	{
		m_dwState = ST_WALK;
	}

	if (m_dwKey & KEY_LEFT && (m_dwState != ST_UP) && (m_dwState != ST_ATTACK) && (m_dwState != ST_ATTACK2) && (m_dwState != ST_PROSTRATE))
	{
		m_tInfo.fX -= m_tStat.fSpeed;
	}

	if (m_dwKey & KEY_RIGHT && (m_dwState != ST_UP) && (m_dwState != ST_ATTACK) && (m_dwState != ST_ATTACK2) && (m_dwState != ST_PROSTRATE))
	{
		m_tInfo.fX += m_tStat.fSpeed;
	}

	if ((m_dwKey & KEY_UP) && (m_dwState & ST_UP))
	{
		m_tInfo.fY -= m_tStat.fSpeed;
	}

	if (m_dwKey & KEY_DOWN)
	{
		if (m_dwState & ST_UP)
		{
			m_tInfo.fY += m_tStat.fSpeed;
		}

		else if (m_dwKey & KEY_ALT && m_dwState != ST_JUMP)
		{
			m_dwState = ST_JUMP;
			m_tInfo.fY += 25.f;

			if (m_bLand == true)
			{
				m_fJpower = 5.f;
				m_bLand = false;
			}
		}
	}

	if (m_dwKey & KEY_CONTROL)
	{
		m_dwState = ST_ATTACK;
	}

	if (m_dwKey & KEY_ALT && m_dwState != ST_PROSTRATE)
	{
		if (m_dwState == ST_UP)
		{
			if (m_dwKey & KEY_LEFT || m_dwKey & KEY_RIGHT)
			{
				m_dwState = ST_JUMP;

				if (m_bLand)
				{
					m_fJpower = -6.f;
					m_bLand = false;
				}
			}
		}
		else
		{
			m_dwState = ST_JUMP;

			if (m_bLand)
			{
				m_fJpower = -11.f;
				m_bLand = false;
			}
		}
	}


	//// ��ų
	if ((m_cTimer.fRemainTime[1] -= _delta) <= 0 && m_dwState != ST_UP && m_dwState != ST_PROSTRATE)
	{
		if (m_dwKey & KEY_Q && m_dwState != ST_UP && m_dwState != ST_PROSTRATE)
		{
			CParent* pSkill = CreateSkill(0);
			if (pSkill)
			{
				m_dwState = ST_ATTACK;
				m_pSkill->push_back(pSkill);
				m_cTimer.fRemainTime[1] = 800.f;
			}
		}
	}

	if ((m_cTimer.fRemainTime[2] -= _delta) <= 0 && m_dwState != ST_UP && m_dwState != ST_PROSTRATE)
	{
		if (m_dwKey & KEY_W)
		{
			CParent* pSkill = CreateSkill(1);
			if (pSkill)
			{
				m_dwState = ST_ATTACK2;
				m_pSkill->push_back(pSkill);
				m_cTimer.fRemainTime[2] = 800.f;
			}
		}
	}

	if ((m_cTimer.fRemainTime[3] -= _delta) <= 0 && m_dwState != ST_UP && m_dwState != ST_PROSTRATE)
	{
		if (m_dwKey & KEY_E)
		{
			CParent* pSkill = CreateSkill(2);
			if (pSkill)
			{
				m_dwState = ST_ATTACK;
				m_pSkill->push_back(pSkill);
				m_cTimer.fRemainTime[3] = 800.f;
			}
		}
	}

	if ((m_cTimer.fRemainTime[4] -= _delta) <= 0 && m_dwState != ST_UP && m_dwState != ST_PROSTRATE)
	{
		if (m_dwKey & KEY_R)
		{
			CParent* pSkill = CreateSkill(3);
			if (pSkill)
			{
				m_dwState = ST_ATTACK2;
				m_pSkill->push_back(pSkill);
				m_cTimer.fRemainTime[4] = 800.f;
			}
		}
	}

	if ((m_cTimer.fRemainTime[5] -= _delta) <= 0 && m_dwState != ST_UP && m_dwState != ST_PROSTRATE)
	{
		if (m_dwKey & KEY_A)
		{
			CParent* pSkill = CreateSkill(4);
			if (pSkill)
			{
				m_dwState = ST_ATTACK;
				m_pSkill->push_back(pSkill);
				m_cTimer.fRemainTime[5] = 800.f;
			}

		}
	}

	if ((m_cTimer.fRemainTime[6] -= _delta) <= 0 && m_dwState != ST_UP && m_dwState != ST_PROSTRATE)
	{
		if (m_dwKey & KEY_S)
		{
			CParent* pSkill = CreateSkill(5);
			if (pSkill)
			{
				m_dwState = ST_ATTACK2;
				m_pSkill->push_back(pSkill);
				m_cTimer.fRemainTime[6] = 800.f;
			}
		}
	}
}

void CPlayer::Rotation(void)
{
	m_dwKey = CKeyMgr::GetInstance()->GetKey();

	if ((m_dwKey & KEY_LEFT) && (m_dwState != ST_ATTACK) && (m_dwState != ST_PROSTRATE))
		m_strKey = "Player_LEFT";

	if ((m_dwKey & KEY_RIGHT) && (m_dwState != ST_ATTACK) && (m_dwState != ST_PROSTRATE))
		m_strKey = "Player_RIGHT";

	if (m_dwKey & KEY_UP)
	{
	}

	if ((m_dwKey & KEY_DOWN) && (m_dwState != ST_JUMP) && (m_dwState != ST_UP))
	{
		m_dwState = ST_PROSTRATE;
	}
}

void CPlayer::SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime)
{
	if (m_dwState & _dwState)
	{
		if (m_tSprite.iMotion != _iMotion)
			m_tSprite.iStart = 0;

		m_tSprite.iLast = _iLast;
		m_tSprite.iMotion = _iMotion;
		m_tSprite.dwTime = _dwTime;
	}
}

void CPlayer::ScrollX(void)
{
// ���� ��
	if(m_tInfo.fX < m_ptOffset.x - 100.f)
	{
		if(m_ptScroll.x > 0 - m_tStat.fSpeed)
		{
			if(m_tInfo.fX < 0)
				m_tInfo.fX = 0.f;

			return;
		}

		m_ptScroll.x += (long)m_tStat.fSpeed; 
		m_ptOffset.x -= (long)m_tStat.fSpeed;
	}

	// ���� ��
	if(m_tInfo.fX > m_ptOffset.x + 100.f)
	{
		if(m_ptScroll.x < WINCX - m_ptMapSize.x + m_tStat.fSpeed)
		{
			if(m_tInfo.fX > m_ptMapSize.x)
				m_tInfo.fX = (float)m_ptMapSize.x;

			return;
		}

		m_ptScroll.x -= (long)m_tStat.fSpeed;
		m_ptOffset.x += (long)m_tStat.fSpeed;
	}
}


void CPlayer::ScrollY(void)
{
	// ��� ��
	if(m_tInfo.fY < m_ptOffset.y - 50.f)
	{
		if(m_ptScroll.y > 0 - m_tStat.fSpeed)
		{
			if(m_tInfo.fY < 0)
				m_tInfo.fY = 0.f;

			return;
		}

		m_ptScroll.y += (long)m_tStat.fSpeed + m_fJpower;
		m_ptOffset.y -= (long)m_tStat.fSpeed + m_fJpower;
	}

	// �ϴ� ��
	if(GetRect().bottom > m_ptOffset.y + 50.f)
	{
		if(m_ptScroll.y < WINCY - m_ptMapSize.y + m_tStat.fSpeed)
		{
			if(m_tInfo.fY > m_ptMapSize.y)
				m_tInfo.fY = (float)m_ptMapSize.y;

			return;
		}

		m_ptScroll.y -= (long)m_tStat.fSpeed + m_fJpower;
		m_ptOffset.y += (long)m_tStat.fSpeed + m_fJpower;
	}
}

CParent* CPlayer::CreateSkill(int _iSlot)
{
	string _strkey;
	CParent* pSkill = NULL;
	vector<CIcon*>* pIcon = ((CQuickSlot*)m_pSlot)->GetSlot();

	if (m_strKey == "Player_LEFT")
	{
		if ((*pIcon)[_iSlot]->GetStrKey() == "Beyond_ON")
		{	
			if (m_iBeyond == 0)
			{
				pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX - 50, m_tInfo.fY - 30, "Beyond_LEFT");
				++m_iBeyond;
			}
			else if(m_iBeyond == 1)
			{
				pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX - 50, m_tInfo.fY - 30, "Beyond2_LEFT");
				++m_iBeyond;
			}
			else
			{
				pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX - 50, m_tInfo.fY - 30, "Beyond3_LEFT");
				m_iBeyond = 0;
			}

		}
		else if ((*pIcon)[_iSlot]->GetStrKey() == "Bolt_ON")
		{	
			pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX - 50, m_tInfo.fY - 30, "Bolt_LEFT");
		}
		else if ((*pIcon)[_iSlot]->GetStrKey() == "Typhoon_ON")
		{	
			pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX - 120, m_tInfo.fY - 30, "Typhoon_LEFT");
		}
		else if ((*pIcon)[_iSlot]->GetStrKey() == "Annihilation_ON")
		{	
			pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX - 80, m_tInfo.fY - 30, "Annihilation_LEFT");
		}
		else if ((*pIcon)[_iSlot]->GetStrKey() == "Range_ON")
		{	
			pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX - 30, m_tInfo.fY - 30, "Range");
		}
	}
	else
	{
		if ((*pIcon)[_iSlot]->GetStrKey() == "Beyond_ON")
		{	
			if (m_iBeyond == 0)
			{
				pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX + 50, m_tInfo.fY - 30, "Beyond_RIGHT");
				++m_iBeyond;
			}
			else if(m_iBeyond == 1)
			{
				pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX + 50, m_tInfo.fY - 30, "Beyond2_RIGHT");
				++m_iBeyond;
			}
			else
			{
				pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX + 50, m_tInfo.fY - 30, "Beyond3_RIGHT");
				m_iBeyond = 0;
			}

		}
		else if ((*pIcon)[_iSlot]->GetStrKey() == "Bolt_ON")
		{	
			pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX + 50, m_tInfo.fY - 30, "Bolt_RIGHT");
		}
		else if ((*pIcon)[_iSlot]->GetStrKey() == "Typhoon_ON")
		{	
			pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX + 120, m_tInfo.fY - 30, "Typhoon_RIGHT");
		}
		else if ((*pIcon)[_iSlot]->GetStrKey() == "Annihilation_ON")
		{	
			pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX + 80, m_tInfo.fY - 30, "Annihilation_RIGHT");
		}
		else if ((*pIcon)[_iSlot]->GetStrKey() == "Range_ON")
		{	
			pSkill = CFactory<CSkill>::CreateParent(m_tInfo.fX + 30, m_tInfo.fY - 30, "Range");
		}
	}

	((CQuickSlot*)m_pSlot)->SetCooltime(_iSlot, 0.f);

	if (pSkill)
		return pSkill;

	return 0;
}

void CPlayer::SetSkill(vector<CParent*>* _pSkill)
{
	m_pSkill = _pSkill;
}

void CPlayer::SetOffset(float _fX, float _fY)
{
	m_ptOffset.x = (long)_fX;
	m_ptOffset.y = (long)_fY;
}

void CPlayer::SetQuickSlot(CUI* _pSlot)
{
	m_pSlot = _pSlot;
}

void CPlayer::EquipItem(CItem* _pItem)
{
	if (_pItem->GetItem().iType == IT_WEAPON)
	{
		m_tStat.fAttack = m_fOriginAttack + _pItem->GetItem().iOption;
	}
	else if (_pItem->GetItem().iType == IT_ARMOR)
	{
		m_tStat.fDefense = m_fOriginDefense + _pItem->GetItem().iOption;
	}
}

void CPlayer::UnEquipItem(CItem* _pItem)
{
	if (_pItem->GetItem().iType == IT_WEAPON)
	{
		m_tStat.fAttack = m_fOriginAttack;
	}
	else if (_pItem->GetItem().iType == IT_ARMOR)
	{
		m_tStat.fDefense = m_fOriginDefense;
	}
}

void CPlayer::BuyItem(int _iGold)
{
	m_tStat.iGold -= _iGold;
}