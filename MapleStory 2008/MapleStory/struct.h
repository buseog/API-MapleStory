#pragma once

typedef struct tagInfo
{
	float fX; 
	float fY;
	float fCX; 
	float fCY;

	tagInfo(void){}
	tagInfo(float _fX, float _fY, float _fCX, float _fCY)
		: fX(_fX), fY(_fY), fCX(_fCX), fCY(_fCY)
	{

	}

}INFO;

typedef struct tagStat
{
	float fHp;
	float fAttack;
	float fDefense;
	float fSpeed;

	tagStat(void){}
	tagStat(float _fHp, float _fAttack, float _fDefense, float _fSpeed)
		: fHp(_fHp), fAttack(_fAttack), fDefense(_fDefense), fSpeed(_fSpeed)
	{

	}

}STAT;

typedef	 struct tagTile
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;
	int		iOption;
	int		iDrawID;

	RECT	GetRect(void)
	{
		RECT rc = {long(fX - fCX / 2), long(fY - fCY / 2), long(fX + fCX / 2), long(fY + fCY / 2)};

		return rc;
	}


}TILE;


typedef struct tagSprite
{
	int		iStart;
	int		iLast;
	int		iMotion;
	DWORD	dwTime;

	tagSprite(){}
	tagSprite(int _iStart, int _iLast, int _iMotion, DWORD _dwTime)
		: iStart(_iStart), iLast(_iLast), iMotion(_iMotion), dwTime(_dwTime) 
	{

	}

}SPRITE;

typedef struct tagItem
{
	int m_iAttack;
	int m_iDeffense;
	int m_iCount;
	int m_iPrice;
	int m_iType;

	tagItem(){}
	tagItem(int _iAttack, int _iDeffense, int _iCount, int _iPrice, int _iType)
		:m_iAttack(_iAttack), m_iDeffense(_iDeffense), m_iCount(_iCount), m_iPrice(_iPrice), m_iType(_iType)
	{
	}

}ITEM;