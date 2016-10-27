#include "StdAfx.h"
#include "Scene.h"
#include "MapEdit.h"

CScene::CScene(void)
:m_pPlayer(NULL)
{
	
}

CScene::~CScene(void)
{

}

void CScene::SetPlayer(CParent*	_pPlayer)
{
	m_pPlayer = _pPlayer;
}