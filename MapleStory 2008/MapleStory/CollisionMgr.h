#pragma once

class CParent;

class CCollisionMgr
{
public:
	static	void	CollisionTile(vector<CParent*>* _pParent, vector<TILE*>* _pTile);

public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};
