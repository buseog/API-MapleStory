#include "StdAfx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Factory.h"
#include "Skill.h"
#include "UI.h"

CPlayer::CPlayer(void)
:m_pSkill(NULL)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);
	m_tStat = STAT(10.f, 10.f, 10.f, 10.f);
	m_tSprite = SPRITE(0, 5, 0, 80);
	m_pUI[UI_INVENTORY] = CFactory<CUI>::CreateParent(600.f, 300.f, "Inventory");
	m_pUI[UI_EQUIPMENT] = CFactory<CUI>::CreateParent(500.f, 300.f, "Equipment");
	m_pUI[UI_SKILL] = CFactory<CUI>::CreateParent(600.f, 400.f, "Skill");
	
	for (int i = 0; i < UI_END; ++i)
	{
		m_bUIOnOff[i] = false;
	}

	m_dwTime = GetTickCount();
	m_strKey = "Player_LEFT";
	m_dwKey = 0;
	m_iDrawID = 0;

	m_ptOffset.x = WINCX / 2;
	m_ptOffset.y = WINCY / 2;
}

void CPlayer::Progress(void)
{
	KeyInput();
	Rotation();
	Gravity();
	Scroll();

	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
 		if (m_dwState != ST_STAND && m_dwState != ST_PROSTRATE && m_dwState != ST_JUMP)
			m_dwState = ST_STAND;

		m_tSprite.iStart = 0;
	}
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
		RGB(71, 0, 60));

		for (int i = 0; i < UI_END; ++i)
		{
			if (m_bUIOnOff[i] == true)
			{
				m_pUI[i]->Render(hdc);
			}
		}
}

void CPlayer::Release(void)
{
}

void CPlayer::KeyInput(void)
{
	m_dwKey = CKeyMgr::GetInstance()->GetKey();

	if (!m_dwKey && (m_dwState != ST_ATTACK) && m_bLand == true)
	{
		SetState(ST_STAND, 5, 0, 80);
   		m_dwState = ST_STAND;
	}

	if (m_dwKey && (m_dwState != ST_ATTACK) && (m_dwState != ST_PROSTRATE) && m_bLand == true)
	{
		SetState(ST_WALK, 3, 1, 100);
		m_dwState = ST_WALK;
	}

	if (m_dwKey & KEY_LEFT)
		m_tInfo.fX -= m_tStat.fSpeed;

	if (m_dwKey & KEY_RIGHT)
		m_tInfo.fX += m_tStat.fSpeed;

	if (m_dwKey & KEY_UP)
	{

	}

	if (m_dwKey & KEY_DOWN)
	{

	}

	if (m_dwKey & KEY_CONTROL)
	{
		SetState(ST_ATTACK, 3, 2, 100);
		m_dwState = ST_ATTACK;
	}

	if (m_dwKey & KEY_SPACE)
	{
		SetState(ST_JUMP, 1, 6, 100);
		m_dwState = ST_JUMP;

		if (m_bLand == true)
		{
			m_fJpower = -13.f;
			m_bLand = false;
		}
	}

	if (m_dwKey & KEY_I)	// 인벤토리
	{
		if (m_bUIOnOff[UI_INVENTORY])
			m_bUIOnOff[UI_INVENTORY] = false;
		
		else
			m_bUIOnOff[UI_INVENTORY] = true;
	}

	if (m_dwKey & KEY_U)	// 장비창
	{
		if (m_bUIOnOff[UI_EQUIPMENT])
			m_bUIOnOff[UI_EQUIPMENT] = false;
		
		else
			m_bUIOnOff[UI_EQUIPMENT] = true;
	}

	if (m_dwKey & KEY_K)	// 스킬창
	{
		if (m_bUIOnOff[UI_SKILL])
			m_bUIOnOff[UI_SKILL] = false;
		
		else
			m_bUIOnOff[UI_SKILL] = true;
	}

	if (m_dwKey & KEY_Q)
	{
		if (m_strKey == "Player_LEFT") 
			m_pSkill->push_back(CreateSkill(m_tInfo.fX, m_tInfo.fY,"Annihilation_LEFT"));

		else if (m_strKey == "Player_RIGHT")
			m_pSkill->push_back(CreateSkill(m_tInfo.fX, m_tInfo.fY,"Annihilation_RIGHT"));

		return;
	}

	if (m_dwKey & KEY_W)
	{
		if (m_strKey == "Player_LEFT") 
			m_pSkill->push_back(CreateSkill(m_tInfo.fX, m_tInfo.fY,"Typhoon_LEFT"));

		else if (m_strKey == "Player_RIGHT")
			m_pSkill->push_back(CreateSkill(m_tInfo.fX, m_tInfo.fY,"Typhoon_RIGHT"));

		return;
	}

	if (m_dwKey & KEY_E)
	{
		if (m_strKey == "Player_LEFT") 
			m_pSkill->push_back(CreateSkill(m_tInfo.fX, m_tInfo.fY,"Range_LEFT"));

		else if (m_strKey == "Player_RIGHT")
			m_pSkill->push_back(CreateSkill(m_tInfo.fX, m_tInfo.fY,"Range_LEFT"));

		return;
	}

	if (m_dwKey & KEY_R)
	{
		if (m_strKey == "Player_LEFT") 
			m_pSkill->push_back(CreateSkill(m_tInfo.fX, m_tInfo.fY,"Beyond_LEFT"));

		else if (m_strKey == "Player_RIGHT")
			m_pSkill->push_back(CreateSkill(m_tInfo.fX, m_tInfo.fY,"Beyond_RIGHT"));

		return;
	}
}

void CPlayer::Rotation(void)
{
	m_dwKey = CKeyMgr::GetInstance()->GetKey();

	if (m_dwKey & KEY_LEFT)
		m_strKey = "Player_LEFT";

	if (m_dwKey & KEY_RIGHT)
		m_strKey = "Player_RIGHT";

	/*if (m_dwKey & KEY_UP)
		m_strKey = "Player_UP";*/

	if (m_dwKey & KEY_DOWN)
	{
		SetState(ST_PROSTRATE, 1, 5, 100);
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

void CPlayer::Scroll(void)
{
// 좌측 끝
	if(m_tInfo.fX < m_ptOffset.x)
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

	// 우측 끝
	if(m_tInfo.fX > m_ptOffset.x)
	{
		if(m_ptScroll.x < WINCX - 3840.f + m_tStat.fSpeed)
		{
			if(m_tInfo.fX > 1920.f)
				m_tInfo.fX = 1920.f;

			return;
		}

		m_ptScroll.x -= (long)m_tStat.fSpeed;
		m_ptOffset.x += (long)m_tStat.fSpeed;
	}

	// 상단 끝
	if(m_tInfo.fY < m_ptOffset.y)
	{
		if(m_ptScroll.y > 0 - m_tStat.fSpeed)
		{
			if(m_tInfo.fY < 0)
				m_tInfo.fY = 0.f;

			return;
		}

		m_ptScroll.y += (long)m_tStat.fSpeed;
		m_ptOffset.y -= (long)m_tStat.fSpeed;
	}

	// 하단 끝
	if(m_tInfo.fY > m_ptOffset.y)
	{
		if(m_ptScroll.y < WINCY - 680.f + m_tStat.fSpeed)
		{
			if(m_tInfo.fY > 680.f)
				m_tInfo.fY = 680.f;

			return;
		}

		m_ptScroll.y -= (long)m_tStat.fSpeed;
		m_ptOffset.y += (long)m_tStat.fSpeed;
	}
}

CParent* CPlayer::CreateSkill(float _fX, float _fY, string _strKey)
{

	CParent* pSkill = CFactory<CSkill>::CreateParent(_fX, _fY, _strKey);

	return pSkill;
}

void CPlayer::SetSkill(vector<CParent*>* _pSkill)
{
	m_pSkill = _pSkill;
}