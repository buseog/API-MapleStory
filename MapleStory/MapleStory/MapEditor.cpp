#include "StdAfx.h"
#include "MapEditor.h"
#include "MapEdit.h"

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
	m_pEdit = new CMapEdit;
	m_pEdit->Initialize();
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