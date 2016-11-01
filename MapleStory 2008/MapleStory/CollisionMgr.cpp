#include "StdAfx.h"
#include "CollisionMgr.h"
#include "Parent.h"
#include "Effect.h"
#include "DamageEffect.h"
#include "SkillEffect.h"
#include "Factory.h"

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

void CCollisionMgr::CollisionTile(vector<CParent*>* _pParent, vector<TILE*>* _pTile)
{
	RECT rc;

	for (size_t i = 0; i < _pParent->size(); ++i)
	{
		for (size_t j = 0; j < _pTile->size(); ++j)
		{
			IntersectRect(&rc, &(*_pParent)[i]->GetRect(), &(*_pTile)[j]->GetRect());
 
			if ((*_pTile)[j]->iOption == 1)
			{
				LONG fLength = rc.right - rc.left;
				LONG fHeight = rc.bottom - rc.top;

				if (fLength > fHeight)			//상하충돌
				{
					if (rc.top <= (*_pTile)[j]->GetRect().top)	//플레이어가 위
					{
						(*_pParent)[i]->SetLand(true);
						(*_pParent)[i]->SetPos((*_pParent)[i]->GetInfo().fX, (*_pParent)[i]->GetInfo().fY - fHeight);//(*_pParent)[i]->GetInfo().fY - fHeight);
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionSKill(vector<CParent*>* _pSkill, vector<CParent*>* _pMonster)
{
	RECT rc;

	for (size_t i = 0; i < _pSkill->size(); ++i)
	{
		for (size_t j = 0; j < _pMonster->size(); ++j)
		{
			IntersectRect(&rc, &(*_pSkill)[i]->GetRect(), &(*_pMonster)[j]->GetRect());

			LONG fLength = rc.right - rc.left;
			LONG fHeight = rc.bottom - rc.top;

			if (fLength > fHeight)
			{
				(*_pMonster)[j]->SetDamage(3.f);
				AddEffect((*_pSkill)[i], (*_pMonster)[j]);

				if ((*_pMonster)[j]->GetStat().fHp <= 0)
				{
					((*_pMonster)[j]->SetDestroy(true));
				}
			}
			else if (fHeight > fLength)
			{
				(*_pMonster)[j]->SetDamage(3.f);
				AddEffect((*_pSkill)[i], (*_pMonster)[j]);

				if ((*_pMonster)[j]->GetStat().fHp <= 0)
				{
					((*_pMonster)[j]->SetDestroy(true));
				}
			}
		}
	}
}

void	CCollisionMgr::AddEffect(CParent* _pSkill, CParent* _pMonster)
{
	if (_pSkill->GetStrKey() == "Annihilation_LEFT" || _pSkill->GetStrKey() == "Annihilation_RIGHT")
	{
		CScene::SetSkill(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Annihilation_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Ascend_LEFT" || _pSkill->GetStrKey() == "Ascend_RIGHT")
	{
		CScene::SetSkill(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Ascend_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Typhoon_LEFT" ||_pSkill->GetStrKey() == "Typhoon_RIGHT")
	{
		CScene::SetSkill(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Typhoon_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Bolt_LEFT" || _pSkill->GetStrKey() == "Bolt_RIGHT")
	{
		CScene::SetSkill(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Bolt_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Beyond_LEFT" || _pSkill->GetStrKey() == "Beyond_RIGHT")
	{
		CScene::SetSkill(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond1_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Beyond2_LEFT" || _pSkill->GetStrKey() == "Beyond2_RIGHT")
	{
		CScene::SetSkill(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond2_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Beyond3_LEFT" || _pSkill->GetStrKey() == "Beyond3_RIGHT")
	{
		CScene::SetSkill(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond3_EFFECT"));
	}
}