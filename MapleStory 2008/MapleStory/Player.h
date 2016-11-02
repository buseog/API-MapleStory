#pragma once
#include "Parent.h"

class CUI;

class CPlayer	:
	public CParent
{
private:
	vector<CParent*>*	m_pSkill;
	POINT				m_ptOffset;
	POINT				m_ptMapSize;
	int					m_iBeyond;

private:
	void	SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime);
	void	KeyInput(DWORD _delta);
	void	Rotation(void);
	void	ScrollX(void);
	void	ScrollY(void);

public:
	CParent*	CreateSkill(float _fX, float _fY, string _strKey);
	void		SetSkill(vector<CParent*>* _pSkill);
	void		SetMapSize(float _fX, float _fY);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPlayer(void);
	~CPlayer(void);
};
