#pragma once
#include "bigheader.h"
#include "Player.h"

class CItem;


class CUI
{
protected:
	int		m_iPriority;
	INFO	m_tInfo;
	SPRITE	m_tSprite;
	DWORD	m_dwTime;
	int		m_iDrawID;
	float	m_fPercent[3];
	bool	m_bOnOff;

	CItem*	m_ReturnItem;
	CUI*	m_pCloseButton;

	string	m_strKey;
	static	CParent*				m_pPlayer;
	static	map<string, CBitBmp*>*	m_pBitMap;

public:
	static void SetBitMap(map<string, CBitBmp*>* _pBitMap);
	static void	SetPlayer(CParent* _pPlayer);
	void	SetPos(float _fX, float _fY);
	INFO	GetInfo(void);
	CItem*	GetReturnItem(void);
	void	SetReturnItem(void);
	bool	GetOnOff(void);
	void	SetOnOff(bool _YN);
	void	SetPriority(int _iInput);
	int		GetPriority(void);


public:
	virtual void UIPicking(void);
	virtual RECT GetRect(void);
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CUI(void);
	CUI(string _strKey);
	virtual ~CUI(void);
};
