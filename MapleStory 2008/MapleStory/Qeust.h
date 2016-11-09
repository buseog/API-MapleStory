#pragma once
#include "ui.h"

class CQuest :
	public CUI
{
private:
	TCHAR szString[128];
	CUI*	m_pInventory;

private:
	void	QuestStart(void);
	void	QuestBoss(void);
	void	QuestEnding(void);
	void	QuestBye(void);

public:
	void	SetInventory(CUI*	_pInventory);

public:
	virtual void UIPicking(void);
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CQuest(void);
	CQuest(string _strKey);
	~CQuest(void);
};
