#include "StdAfx.h"
#include "Start.h"

#include <Vfw.h>
#pragma comment(lib, "Vfw32.lib")

#include "SceneMgr.h"

CStart::CStart(void)
{
}

CStart::~CStart(void)
{
	Release();
}


void CStart::Initialize(void)
{
	m_hVideo = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD,
		L"../Video/Logo.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, NULL);
	MCIWndPlay(m_hVideo);
}

void CStart::Progress(DWORD _delta)
{
	if(GetAsyncKeyState(VK_RETURN))
	{
		CSceneMgr::GetInstance()->SetScene(SC_LOGIN);
		return;
	}
}

void CStart::Render(HDC hdc)
{

}

void CStart::Release(void)
{
	MCIWndClose(m_hVideo);
}