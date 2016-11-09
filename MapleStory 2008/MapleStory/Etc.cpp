#include "StdAfx.h"
#include "Etc.h"

CEtc::CEtc(void)
{
}


CEtc::CEtc(wstring _strName, int _iOption, int _iCount, int _iPrice, int _iType)
:CItem(_strName, _iOption, _iCount, _iPrice, _iType)
{
	Initialize();
}

CEtc::CEtc(const CItem &_Item) :CItem(_Item)
{
}


CEtc::~CEtc(void)
{
}

void CEtc::Initialize(void)
{
	if (m_tItem.strName == L"DragonStone")
	{
		m_tInfo = INFO(0, 0, 32.f, 32.f);
		m_DropId = 1;
	}
	else if (m_tItem.strName == L"FreePass")
	{
		m_tInfo = INFO(0, 0, 32.f, 32.f);
		m_DropId = 0;
	}
}

void CEtc::Progress(DWORD _delta)
{
	if (m_DropId == 1)
	{
		m_tInfo.fY += 5.f;
	}

	if(PtInRect(&GetRect(), GetMouse()))
	{
		m_DrawId = 1;
	}
	else
		m_DrawId = 0;
}

void CEtc::Render(HDC hdc)
{
	SetBkMode((*m_pBitMap)["Back"]->GetMemdc(),TRANSPARENT);

	string str;

	str.assign(m_tItem.strName.begin(), m_tItem.strName.end());


	if (m_DropId == 0)
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[str]->GetMemdc(),
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
	}
	else if (m_DropId == 1)
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + CParent::m_ptScroll.x),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f + CParent::m_ptScroll.y),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			(*m_pBitMap)[str]->GetMemdc(),
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
	}

	if (m_DrawId == 1)
	{
		BitBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + 30),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f + 30),
		150,
		120,
		(*m_pBitMap)["ItemStat"]->GetMemdc(),
		0,
		0,
		SRCCOPY);

		TCHAR szString[128] = L"";

		wsprintf(szString, L"이름 : %s", m_tItem.strName.c_str());
					TextOut(hdc,
						int(m_tInfo.fX + 30), int(m_tInfo.fY + 30),
						szString, lstrlen(szString));

		wsprintf(szString, L"%s", L"퀘스트 재료");
					TextOut(hdc, 
						int(m_tInfo.fX + 30), int(m_tInfo.fY + 45),
						szString, lstrlen(szString));
	}
}

void CEtc::Release(void)
{

}