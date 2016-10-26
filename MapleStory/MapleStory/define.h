#pragma once

#define PURE = 0

extern HWND g_hWnd;

const int WINCX = 800;
const int WINCY = 600;

const int TILEX = 59;
const int TILEY = 48;

const int TILECX = 30;
const int TILECY = 30;

template<typename T>
static void Safe_Delete(T& Temp)
{
	if(Temp)
	{
		delete Temp;
		Temp = NULL;
	}
}

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


static POINT GetMouse(void)
{
	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return pt;
}

enum MapEdit
{
	MAP_BACK,
	MAP_TILE
};

enum SCENEID
{
	SC_STAGE1,
	SC_STAGE2,
	SC_END
};
