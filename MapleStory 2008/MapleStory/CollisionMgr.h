#pragma once

class CParent;

class CCollisionMgr
{
private:
	static	void	AddSkillEffect(CParent* _pSkill, CParent* _pMonster);
	static	void	AddEffect(int _Critical, CParent* _pMonster);

public:
	static	void	CollisionTile(vector<CParent*>* _pParent, vector<TILE*>* _pTile);
	static	void	CollisionSKill(vector<CParent*>* _pSkill, vector<CParent*>* _pMonster);
	static	void	CollisionPortal(vector<CParent*>* _pParent, vector<CParent*>* _pPortal);
public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};
