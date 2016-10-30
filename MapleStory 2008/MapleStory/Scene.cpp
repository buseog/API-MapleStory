#include "StdAfx.h"
#include "Scene.h"
#include "MapEdit.h"

vector<CParent*>	CScene::m_vecParent[OBJ_END];

CScene::CScene(void)
{
	
}

CScene::~CScene(void)
{

}

void CScene::LoadMap(void)
{
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		::Safe_Delete(m_vecTile[i]);
	}
	m_vecTile.clear();
	vector<TILE*>().swap(m_vecTile);


	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	if (m_strKey == "Village")
	{
		hFile = CreateFile(L"../Data/Village.dat",
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	if (m_strKey == "Stage1")
	{
		hFile = CreateFile(L"../Data/Stage1.dat", 
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	if (m_strKey == "Stage2")
	{
		hFile = CreateFile(L"../Data/Stage2.dat", 
							GENERIC_READ, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	}

	while(true)
	{
		TILE*		pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pTile);
			break;
		}

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd,L"로드됨.", L"메세지", MB_OK);
}