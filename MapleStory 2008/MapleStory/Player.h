#pragma once
#include "Parent.h"

class CIcon;
class CUI;

class CPlayer	:
	public CParent
{
private:
	vector<CParent*>*	m_pSkill;
	POINT				m_ptOffset;
	POINT				m_ptMapSize;
	int					m_iBeyond;
	CUI*				m_pSlot;

private:
	void	SetState(DWORD _dwState, int _iLast, int _iMotion, DWORD _dwTime);
	void	KeyInput(DWORD _delta);
	void	Rotation(void);
	void	ScrollX(void);
	void	ScrollY(void);

public:
	CParent*	CreateSkill(int _iSlot);
	void		SetSkill(vector<CParent*>* _pSkill);
	void		SetQuickSlot(CUI* _pSlot);
	void		SetMapSize(float _fX, float _fY);
	void		SetOffset(float _fX, float _fY);

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPlayer(void);
	~CPlayer(void);
};
