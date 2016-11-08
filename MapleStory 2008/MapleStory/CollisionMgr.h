#pragma once

class CParent;
class CItem;
class CUI;

class CCollisionMgr
{
private:
	static	void	AddEffect(CParent* _pSkill, CParent* _pParent, int Height);
	static	void	AddSkillEffect(CParent* _pSkill, CParent* _pMonster);
	static	void	SkillDamage(CParent* _pSkill, CParent* _pMonster);

public:
	static	void	CollisionItem(vector<CParent*>* _pPlayer, vector<CItem*>* _pItem, vector<CUI*>* _Inventory);
	static	void	CollisionBodyButt(vector<CParent*>*	_pPlayer, vector<CParent*>* _pMonster);
	static	void	CollisionPTile(vector<CParent*>* _pPlayer, vector<TILE*>* _pTile);
	static	void	CollisionITile(vector<CItem*>* _pItem, vector<TILE*>* _pTile);
	static	float	CollisionSKill(vector<CParent*>* _pSkill, vector<CParent*>* _pMonster);
	static	void	CollisionPortal(vector<CParent*>* _pParent, vector<CParent*>* _pPortal);

public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};
