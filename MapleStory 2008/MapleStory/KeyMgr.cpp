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

	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwKey |= KEY_SPACE;

	if (GetAsyncKeyState('Q') & 0x8000)
		m_dwKey |= KEY_Q;

	if (GetAsyncKeyState('W') & 0x8000)
		m_dwKey |= KEY_W;

	if (GetAsyncKeyState('E') & 0x8000)
		m_dwKey |= KEY_E;

	if (GetAsyncKeyState('R') & 0x8001)
		m_dwKey |= KEY_R;

	if (GetAsyncKeyState('I') & 0x8000)
		m_dwKey |= KEY_I;

	if (GetAsyncKeyState('U') & 0x8000)
		m_dwKey |= KEY_U;

	if (GetAsyncKeyState('K') & 0x8000)
		m_dwKey |= KEY_K;

	if (GetAsyncKeyState(VK_F5) & 0x8000)
		m_dwKey |= KEY_F5;
}

DWORD CKeyMgr::GetKey(void)
{
	return m_dwKey;
}