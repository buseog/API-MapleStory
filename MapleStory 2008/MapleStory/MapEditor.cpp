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
	LoadBmp();

	m_pEdit = CFactory<CMapEdit>::CreateParent();
	m_pEdit->SetBitMap(&m_BitMap);
}

void CMapEditor::Progress(DWORD _delta)
{
	m_pEdit->Progress(_delta);
}

void CMapEditor::Render(HDC hdc)
{
	m_pEdit->Render(hdc);
}

void CMapEditor::Release(void)
{
	::Safe_Delete(m_pEdit);	
}