#include "StdAfx.h"
#include "BitBmp.h"

CBitBmp::CBitBmp(void)
{
}

CBitBmp::~CBitBmp(void)
{
	Release();
}


CBitBmp* CBitBmp::LoadBmp(TCHAR* _pFileName)
{
	m_hdc = GetDC(g_hWnd);

	m_Memdc = CreateCompatibleDC(m_hdc);

	ReleaseDC(g_hWnd, m_hdc);

	m_bitmap = (HBITMAP)LoadImage(NULL, _pFileName, IMAGE_BITMAP, 0, 0, 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if(m_bitmap == NULL)
		MessageBox(g_hWnd, _pFileName, L"LOAD_ERROR", MB_OK);

	m_oldmap = (HBITMAP)SelectObject(m_Memdc, m_bitmap);
	return this;
}

void CBitBmp::Release(void)
{
	SelectObject(m_Memdc, m_oldmap);
	DeleteObject(m_bitmap);
	DeleteDC(m_Memdc);
}

HDC CBitBmp::GetMemdc(void)
{ 
	return m_Memdc; 
}
