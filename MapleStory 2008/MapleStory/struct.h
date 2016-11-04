#pragma once
#include <string>
using namespace std;

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
	float fFullHp;
	float fAttack;
	float fDefense;
	int   iLevel;
	float fExp;
	float fSpeed;
	int   iGold;

	tagStat(void){}
	tagStat(float _fHp, float _fFullHp, float _fAttack, float _fDefense, int _iLevel, float _fExp, float _fSpeed, int _iGold)
		: fHp(_fHp), fFullHp(_fFullHp), fAttack(_fAttack), fDefense(_fDefense), iLevel(_iLevel), fExp(_fExp), fSpeed(_fSpeed), iGold(_iGold)
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
	wstring m_strName;
	int m_iOption;
	int m_iCount;
	int m_iPrice;
	int m_iType;

	tagItem(){}
	tagItem(wstring	_strName, int _iOption, int _iCount, int _iPrice, int _iType)
		:m_strName(_strName), m_iOption(_iOption), m_iCount(_iCount), m_iPrice(_iPrice), m_iType(_iType)
	{
	}

}ITEM;