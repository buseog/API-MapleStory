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