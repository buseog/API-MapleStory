#include "StdAfx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Factory.h"
#include "Skill.h"

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

	m_dwTime = GetTickCount();
	m_strKey = "Player_LEFT";
	m_dwKey = 0;
	m_iDrawID = 0;
}

void CPlayer::Progress(void)
{
	KeyInput();
	Rotation();
	Gravity();

	if (m_dwTime + m_tSprite.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();

		++m_tSprite.iStart;
	}

	if (m_tSprite.iStart >= m_tSprite.iLast)
	{
		if (m_dwState != ST_STAND && m_dwState != ST_PROSTRATE)
			m_dwState = ST_STAND;

		m_tSprite.iStart = 0;
	}
}

void CPlayer::Render(HDC hdc)
{
		TransparentBlt(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + m_fScrollY),
		int(m_tInfo.fCX), 
		int(m_tInfo.fCY), 
		(*m_pBitMap)[m_strKey]->GetMemdc(),
		int(m_tInfo.fCX * m_tSprite.iStart), 
		int(m_tInfo.fCY * m_tSprite.iMotion),
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY, 
		RGB(71, 0, 60));
}

void CPlayer::Release(void)
{
}

void CPlayer::KeyInput(void)
{
	m_dwKey = CKeyMgr::GetInstance()->GetKey();


	if (m_dwKey & KEY_LEFT)
		m_tInfo.fX -= m_tStat.fSpeed;

	if (m_dwKey & KEY_RIGHT)
		m_tInfo.fX += m_tStat.fSpeed;

	if (m_dwKey & KEY_UP)
		//m_tInfo.fY -= m_tStat.fSpeed;

	if (m_dwKey & KEY_DOWN)
		//m_tInfo.fY += m_tStat.fSpeed;

	if (m_dwKey & KEY_CONTROL)
	{
		SetState(ST_ATTACK, 3, 2, 100);
		m_dwState = ST_ATTACK;
	}

	if (m_dwKey & KEY_SPACE)
	{
		if (m_bLand == true)
		{
			SetState(ST_JUMP, 1, 6, 100);
			m_dwState = ST_JUMP;
			m_fJpower = -10.f;
			m_bLand = false;
		}
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
}

void CPlayer::Rotation(void)
{
	m_dwKey = CKeyMgr::GetInstance()->GetKey();

	if (!m_dwKey && (m_dwState != ST_ATTACK) && (m_dwState != ST_JUMP))
	{
		SetState(ST_STAND, 5, 0, 80);
		m_dwState = ST_STAND;
	}
	if (m_dwKey && (m_dwState != ST_ATTACK) && (m_dwState != ST_JUMP) && (m_dwState != ST_PROSTRATE))
	{
		SetState(ST_WALK, 3, 1, 100);
		m_dwState = ST_WALK;
	}

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