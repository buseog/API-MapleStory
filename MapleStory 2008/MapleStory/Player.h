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
	int					m_iBeyond;
	CUI*				m_pSlot;
	int					m_iQuest;
	int					m_iTile;


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
	void		SetOffset(float _fX, float _fY);
	void		EquipItem(CItem* _pItem);
	void		UnEquipItem(CItem* _pItem);
	void		BuyItem(int _iGold);
	void		SetQuest(int _iQuest);
	int			GetQuest(void);

	void		SetTile(int _iTile);
	int			GetTile(void);
	

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPlayer(void);
	~CPlayer(void);
};
