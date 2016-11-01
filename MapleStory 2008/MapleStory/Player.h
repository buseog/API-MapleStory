#pragma once
#include "Parent.h"

class CUI;

class CPlayer	:
	public CParent
{
private:
	vector<CParent*>*	m_pSkill;
	POINT				m_ptOffset;
	int					m_iBeyond;
	CUI*				m_pUI[UI_END];
	bool				m_bUIOnOff[UI_END];

private:
	void	KeyInput(void);
	void	Rotation(void);
	void	SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime);
	void	Scroll(void);

public:
	CParent*	CreateSkill(float _fX, float _fY, string _strKey);
	void		SetSkill(vector<CParent*>* _pSkill);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPlayer(void);
	~CPlayer(void);
};
