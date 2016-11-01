#include "StdAfx.h"
#include "CollisionMgr.h"
#include "Parent.h"
#include "Effect.h"
#include "DamageEffect.h"
#include "SkillEffect.h"
#include "Portal.h"
#include "Factory.h"
#include "SceneMgr.h"

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
					if ((rc.top <= (*_pTile)[j]->GetRect().top) && ((*_pParent)[i]->GetJumpPower() >= 0))	//플레이어가 위
					{
						(*_pParent)[i]->SetLand(true);
						(*_pParent)[i]->SetPos((*_pParent)[i]->GetInfo().fX, (*_pParent)[i]->GetInfo().fY - fHeight);
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
			int Critical = rand() % 100;
			
			if (IntersectRect(&rc, &(*_pSkill)[i]->GetRect(), &(*_pMonster)[j]->GetRect()))
			{
				LONG fLength = rc.right - rc.left;
				LONG fHeight = rc.bottom - rc.top;

				if (fLength > fHeight)
				{
					(*_pMonster)[j]->SetDamage(3.f);
					AddSkillEffect((*_pSkill)[i], (*_pMonster)[j]);
					AddEffect(Critical, (*_pMonster)[j]);

					if ((*_pMonster)[j]->GetStat().fHp <= 0)
					{
						((*_pMonster)[j]->SetDestroy(true));
					}
				}
				else if (fHeight > fLength)
				{
					(*_pMonster)[j]->SetDamage(3.f);
					AddSkillEffect((*_pSkill)[i], (*_pMonster)[j]);
					AddEffect(Critical, (*_pMonster)[j]);

					if ((*_pMonster)[j]->GetStat().fHp <= 0)
					{
						((*_pMonster)[j]->SetDestroy(true));
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionPortal(vector<CParent*>* _pParent, vector<CParent*>* _pPortal)
{
	RECT rc;

	for (size_t i = 0; i < _pParent->size(); ++i)
	{
		for (size_t j = 0; j < _pPortal->size(); ++j)
		{
			if (IntersectRect(&rc, &(*_pParent)[i]->GetRect(), &(*_pPortal)[j]->GetRect()))
			{
				CSceneMgr::GetInstance()->SetScene(((CPortal*)(*_pPortal)[j])->GetPortal());
				return;
			}
		}
	}
}


void CCollisionMgr::AddSkillEffect(CParent* _pSkill, CParent* _pMonster)
{
	if (_pSkill->GetStrKey() == "Annihilation_LEFT" || _pSkill->GetStrKey() == "Annihilation_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Annihilation_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Ascend_LEFT" || _pSkill->GetStrKey() == "Ascend_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Ascend_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Typhoon_LEFT" ||_pSkill->GetStrKey() == "Typhoon_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Typhoon_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Bolt_LEFT" || _pSkill->GetStrKey() == "Bolt_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Bolt_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Beyond_LEFT" || _pSkill->GetStrKey() == "Beyond_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond1_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Beyond2_LEFT" || _pSkill->GetStrKey() == "Beyond2_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond2_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Beyond3_LEFT" || _pSkill->GetStrKey() == "Beyond3_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond3_EFFECT"));
	}
}

void CCollisionMgr::AddEffect(int _Critical, CParent* _pMonster)
{
	if (_Critical <= 50)
		CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY - 100, "DamageEffect"));

	else
		CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY - 100, "CriticalEffect"));

}