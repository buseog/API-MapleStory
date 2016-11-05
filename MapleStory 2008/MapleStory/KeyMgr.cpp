#include "StdAfx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = NULL;

CKeyMgr::CKeyMgr(void)
:m_dwKey(0)
{
}

CKeyMgr::~CKeyMgr(void)
{
}

void CKeyMgr::KeyCheck(void)
{
	m_dwKey = 0;

	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwKey |= KEY_LEFT;

	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwKey |= KEY_RIGHT;

	if(GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwKey |= KEY_UP;

	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwKey |= KEY_DOWN;

	if(GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_dwKey |= KEY_CONTROL;

	if(GetAsyncKeyState(VK_MENU) & 0x8000)
		m_dwKey |= KEY_ALT;

	if (GetAsyncKeyState('Q') & 0x0001)
		m_dwKey |= KEY_Q;

	if (GetAsyncKeyState('W') & 0x0001)
		m_dwKey |= KEY_W;

	if (GetAsyncKeyState('E') & 0x0001)
		m_dwKey |= KEY_E;

	if (GetAsyncKeyState('R') & 0x0001)
		m_dwKey |= KEY_R;

	if (GetAsyncKeyState('I') & 0x0001)
		m_dwKey |= KEY_I;

	if (GetAsyncKeyState('U') & 0x0001)
		m_dwKey |= KEY_U;

	if (GetAsyncKeyState('K') & 0x0001)
		m_dwKey |= KEY_K;

	if (GetAsyncKeyState('J') & 0x0001)
		m_dwKey |= KEY_J;

	if (GetAsyncKeyState(VK_F5) & 0x8000)
		m_dwKey |= KEY_F5;

	if (GetAsyncKeyState(VK_F6) & 0x8000)
		m_dwKey |= KEY_F6;

	if (GetAsyncKeyState(VK_F7) & 0x8000)
		m_dwKey |= KEY_F7;

	if (GetAsyncKeyState(VK_F8) & 0x8000)
		m_dwKey |= KEY_F8;

	if (GetAsyncKeyState('A') & 0x0001)
		m_dwKey |= KEY_A;

	if (GetAsyncKeyState('S') & 0x0001)
		m_dwKey |= KEY_S;

	if (GetAsyncKeyState('D') & 0x0001)
		m_dwKey |= KEY_D;

	if (GetAsyncKeyState('F') & 0x0001)
		m_dwKey |= KEY_F;
	
	if (GetAsyncKeyState('Z') & 0x0001)
		m_dwKey |= KEY_Z;

}

DWORD CKeyMgr::GetKey(void)
{
	return m_dwKey;
}