#include "StdAfx.h"
#include "MapEditor.h"
#include "MapEdit.h"
#include "Factory.h"

CMapEditor::CMapEditor(void)
:m_pEdit(NULL)
{
}

CMapEditor::~CMapEditor(void)
{
	Release();
}

void CMapEditor::Initialize(void)
{
	m_BitMap["Back"] = (new CBitBmp)->LoadBmp(L"../Texture/Back.bmp");
	m_BitMap["Tile"] = (new CBitBmp)->LoadBmp(L"../Texture/Tile.bmp");

	m_BitMap["Village"] = (new CBitBmp)->LoadBmp(L"../Texture/Village.bmp");
	m_BitMap["Stage1"] = (new CBitBmp)->LoadBmp(L"../Texture/Stage1.bmp");
	m_BitMap["Stage2"] = (new CBitBmp)->LoadBmp(L"../Texture/Stage2.bmp");


	m_pEdit = CFactory<CMapEdit>::CreateParent();
	m_pEdit->SetBitMap(&m_BitMap);
}

void CMapEditor::Progress(void)
{
	m_pEdit->Progress();
}

void CMapEditor::Render(HDC hdc)
{
	m_pEdit->Render(hdc);
}

void CMapEditor::Release(void)
{
	::Safe_Delete(m_pEdit);	
}