#include "StdAfx.h"
#include "Qeust.h"
#include "Factory.h"
#include "Inventory.h"
#include "ETC.h"

CQuest::CQuest(void)
{
}

CQuest::CQuest(string _strKey)
{
	m_pInventory = NULL;
	m_strKey = _strKey;
}

CQuest::~CQuest(void)
{
	Release();
}


void	CQuest::Initialize(void)
{
	m_bOnOff = false;
	m_tInfo = INFO(300.f, 200.f, 517.f, 188.f);
	m_dwTime = GetTickCount();
}

void	CQuest::Progress(DWORD _dwDelta)
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_bOnOff = false;
	}

	switch (((CPlayer*)m_pPlayer)->GetQuest())
	{
	case 0:
		QuestStart();
		break;

	case 1:
		QuestBoss();
		break;

	case 2:
		QuestEnding();
		break;

	case 3:
		QuestBye();
		break;
	}
}

void CQuest::Render(HDC hdc)
{
	BitBlt(hdc, 
	int(m_tInfo.fX - m_tInfo.fCX / 2.f), 
	int(m_tInfo.fY - m_tInfo.fCY / 2.f), 
	int(m_tInfo.fCX), 
	int(m_tInfo.fCY), 
	(*m_pBitMap)[m_strKey]->GetMemdc(), 
	0, 0, SRCCOPY);
	
	TextOut(hdc, int(m_tInfo.fX - 100), int(m_tInfo.fY - 50),
		szString, lstrlen(szString));
}

void CQuest::Release(void)
{
	m_pInventory = NULL;
}

void CQuest::UIPicking(void)
{

}

RECT CQuest::GetRect(void)
{
	RECT rc = {
		long(m_tInfo.fX - m_tInfo.fCX / 2.f),
		long(m_tInfo.fY - m_tInfo.fCY / 2.f),
		long(m_tInfo.fX + m_tInfo.fCX / 2.f),
		long(m_tInfo.fY - m_tInfo.fCY / 2.f + 20)
	};

	return rc;
}

void CQuest::QuestStart(void)
{
	HANDLE hFile = NULL;
	DWORD dwByte = 0;

	hFile = CreateFile(L"../Data/Quest_Start.dat",
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

	ReadFile(hFile, szString, sizeof(szString), &dwByte, NULL);

	CloseHandle(hFile);

	if (((CInventory*)m_pInventory)->ScanItem(1))
	{
		((CPlayer*)m_pPlayer)->SetQuest(1);

		CItem* pQuestItem = new CEtc(L"FreePass", 1, 1, 1, IT_ETC);	
		((CInventory*)m_pInventory)->AddItem(pQuestItem);
	}
}

void CQuest::QuestBoss(void)
{
	HANDLE hFile = NULL;
	DWORD dwByte = 0;

	hFile = CreateFile(L"../Data/Quest_Boss.dat",
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

	ReadFile(hFile, szString, sizeof(szString), &dwByte, NULL);

	CloseHandle(hFile);
}

void CQuest::QuestEnding(void)
{
	HANDLE hFile = NULL;
	DWORD dwByte = 0;

	hFile = CreateFile(L"../Data/Quest_Ending.dat",
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

	ReadFile(hFile, szString, sizeof(szString), &dwByte, NULL);

	CloseHandle(hFile);

	((CPlayer*)m_pPlayer)->SetQuest(3);
}

void CQuest::QuestBye(void)
{
	HANDLE hFile = NULL;
	DWORD dwByte = 0;

	hFile = CreateFile(L"../Data/Quest_Bye.dat",
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

	ReadFile(hFile, szString, sizeof(szString), &dwByte, NULL);

	CloseHandle(hFile);
}

void	CQuest::SetInventory(CUI*	_pInventory)
{
	m_pInventory = _pInventory;
}