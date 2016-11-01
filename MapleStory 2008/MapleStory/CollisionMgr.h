#pragma once

class CParent;

class CCollisionMgr
{
private:
	static	void	AddEffect(CParent* _pSkill, CParent* _pMonster);

public:
	static	void	CollisionTile(vector<CParent*>* _pParent, vector<TILE*>* _pTile);
	static	void	CollisionSKill(vector<CParent*>* _pSkill, vector<CParent*>* _pMonster);

public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};
