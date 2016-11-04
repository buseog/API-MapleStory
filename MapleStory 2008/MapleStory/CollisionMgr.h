#pragma once

class CParent;

class CCollisionMgr
{
private:
	static	void	AddEffect(CParent* _pSkill, CParent* _pParent, int Height);
	static	void	AddSkillEffect(CParent* _pSkill, CParent* _pMonster);
	static	void	SkillDamage(CParent* _pSkill, CParent* _pMonster);

public:
	static	void	CollisionPTile(vector<CParent*>* _pPlayer, vector<TILE*>* _pTile);
	static	void	CollisionMTile(vector<CParent*>* _pMonster, vector<TILE*>* _pTile);
	static	float	CollisionSKill(vector<CParent*>* _pSkill, vector<CParent*>* _pMonster);
	static	void	CollisionPortal(vector<CParent*>* _pParent, vector<CParent*>* _pPortal);
	static	void	CollisionBodyButt(vector<CParent*>*	_pPlayer, vector<CParent*>* _pMonster);
public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};
