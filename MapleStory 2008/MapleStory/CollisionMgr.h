#pragma once

class CParent;

class CCollisionMgr
{
public:
	static	void	CollisionTile(vector<CParent*>* _pParent, vector<TILE*>* _pTile);
	static	void	CollisionSKill(vector<CParent*>* _pSkill, vector<CParent*>* _pMonster);

public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};
