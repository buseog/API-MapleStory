#include "StdAfx.h"
#include "Loading.h"

#include <Vfw.h>
#pragma comment(lib, "Vfw32.lib")

#include "SceneMgr.h"

CLoading::CLoading(void)
{
}

CLoading::~CLoading(void)
{
	Release();
}


void CLoading::Initialize(void)
{
	m_hVideo = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD,
		L"../Video/Logo.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, NULL);
	MCIWndPlay(m_hVideo);
}

void CLoading::Progress(DWORD _delta)
{
	if(GetAsyncKeyState(VK_RETURN))
	{
		CSceneMgr::GetInstance()->SetScene(SC_LOGIN);
		return;
	}
}

void CLoading::Render(HDC hdc)
{

}

void CLoading::Release(void)
{
	MCIWndClose(m_hVideo);
}