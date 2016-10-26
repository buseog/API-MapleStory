#pragma once
#include "Parent.h"

class CBitBmp;
class CMapEdit	:
	public CParent
{
private:
	vector<TILE*>			m_vecTile;
	vector<CBitBmp*>		m_vecBmp;
	int						m_iStage;
	bool					m_bType;

private:
	TILE*	CreateTile(float _fX, float _fY);
	void	PickingOn(void);
	void	PickingOff(void);
	void	KeyCheck(void);
	void	Scroll(void);

public:
	void			SetStage(int _iStage);
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CMapEdit(void);
	~CMapEdit(void);
};
