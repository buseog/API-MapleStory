#include "StdAfx.h"
#include "CollisionMgr.h"
#include "Parent.h"

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

			if (fLength > fHeight || fLength < fHeight)
			{
				(*_pMonster)[j]->SetDamage(3.f);

				if ((*_pMonster)[j]->GetStat().fHp <= 0)
				{
					((*_pMonster)[j]->SetDestroy(true));
				}
			}
		}

	}
}