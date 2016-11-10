#include "StdAfx.h"
#include "CollisionMgr.h"
#include "Parent.h"
#include "Player.h"
#include "Monster.h"
#include "Skill.h"
#include "Effect.h"
#include "DamageEffect.h"
#include "SkillEffect.h"
#include "Portal.h"
#include "Factory.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Item.h"
#include "UI.h"

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

void CCollisionMgr::CollisionPTile(vector<CParent*>* _pPlayer, vector<TILE*>* _pTile)
{
	RECT rc;
	CParent* pPlayer = _pPlayer->back();
	
	for (size_t i = 0; i < _pTile->size(); ++i)
	{
		if (IntersectRect(&rc, &pPlayer->GetRect(), &(*_pTile)[i]->GetRect()))
		{
			LONG lWidth = rc.right - rc.left;
			LONG lHeight = rc.bottom - rc.top;

			if (lWidth > lHeight)			//상하충돌
			{
			
				switch ((*_pTile)[i]->iOption)
				{
				case 1:
					if (pPlayer->GetState() == ST_UP)
						pPlayer->SetState(ST_STAND);

					pPlayer->SetLand(true);
					((CPlayer*)pPlayer)->SetTile((*_pTile)[i]->iOption);
					pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - lHeight);
					break;

				case 2:
					if (pPlayer->GetInfo().fY <= (*_pTile)[i]->GetRect().bottom && pPlayer->GetJumpPower() > 0.f)
					{
						pPlayer->SetLand(true);
						((CPlayer*)pPlayer)->SetTile((*_pTile)[i]->iOption);
						pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - lHeight);
					}
					break;

				case 3:
					if (pPlayer->GetState() != ST_UP && pPlayer->GetState() != ST_HIT)
					{
						if (GetAsyncKeyState(VK_UP))
						{
							pPlayer->SetLand(true);
							pPlayer->SetState(ST_UP);
							((CPlayer*)pPlayer)->SetTile((*_pTile)[i]->iOption);
							pPlayer->SetPos((*_pTile)[i]->fX, pPlayer->GetInfo().fY - 10.f);
						}
					}
					break;

				case 4:
					if (pPlayer->GetInfo().fY <= (*_pTile)[i]->GetRect().bottom)
					{
						if  (pPlayer->GetState() != ST_UP)
						{
							pPlayer->SetLand(true);
							pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - lHeight);

							if (GetAsyncKeyState(VK_DOWN) )
							{
								if (pPlayer->GetState() != ST_UP)
									pPlayer->SetPos((*_pTile)[i]->fX, pPlayer->GetInfo().fY + 30.f);

								pPlayer->SetLand(true);
								pPlayer->SetState(ST_UP);
								((CPlayer*)pPlayer)->SetTile((*_pTile)[i]->iOption);
							}
						}
						else
						{
							pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - lHeight);
							((CPlayer*)pPlayer)->SetTile((*_pTile)[i]->iOption);
							pPlayer->SetState(ST_STAND);
						}
					}
					break;
				}
			}
		}
	}
}

void CCollisionMgr::CollisionITile(vector<CItem*>* _pItem, vector<TILE*>* _pTile)
{
	RECT rc;

	for (size_t i = 0; i < _pItem->size(); ++i)
	{
		for (size_t j = 0; j < _pTile->size();)
		{
			if ((*_pTile)[j]->iOption)
			{
				if (IntersectRect(&rc, &(*_pItem)[i]->GetRect(), &(*_pTile)[j]->GetRect()))
				{
					LONG lWidth = rc.right - rc.left;
					LONG lHeight = rc.bottom - rc.top;

					if (rc.top == (*_pTile)[j]->GetRect().top)
					{
						switch ((*_pTile)[j]->iOption)
						{
						case 1:
							(*_pItem)[i]->SetPos((*_pItem)[i]->GetInfo().fX, (*_pItem)[i]->GetInfo().fY - lHeight);
							break;	

						case 2:
							(*_pItem)[i]->SetPos((*_pItem)[i]->GetInfo().fX, (*_pItem)[i]->GetInfo().fY - lHeight);
							break;
						}
						break;
					}
					else
						++j;
				}
				else
					++j;
			}
			else
				++j;
		}
	}
}

float CCollisionMgr::CollisionSKill(vector<CParent*>* _pSkill, vector<CParent*>* _pMonster)
{
	RECT rc;
	float fExp = 0.f;

	for (size_t i = 0; i < _pSkill->size(); ++i)
	{
		if (!((CSkill*)(*_pSkill)[i])->GetHit() && ((CSkill*)(*_pSkill)[i])->GetHitCount() > 0)
		{
			for (size_t j = 0; j < _pMonster->size(); ++j)
			{
				if ((*_pMonster)[j]->GetState() != ST_DEATH)
				{
					if ((*_pSkill)[i]->GetInfo().fX >= (*_pMonster)[j]->GetInfo().fX - 300.f && (*_pSkill)[i]->GetInfo().fX <= (*_pMonster)[j]->GetInfo().fX + 200.f &&
						(*_pSkill)[i]->GetInfo().fY >= (*_pMonster)[j]->GetInfo().fY - 300.f && (*_pSkill)[i]->GetInfo().fY <= (*_pMonster)[j]->GetInfo().fY + 200.f)
					{
						if (IntersectRect(&rc, &(*_pSkill)[i]->GetRect(), &(*_pMonster)[j]->GetRect()))
						{
							(*_pMonster)[j]->SetState(ST_HIT);

							SkillDamage((*_pSkill)[i], (*_pMonster)[j]);
							AddSkillEffect((*_pSkill)[i], (*_pMonster)[j]);
							((CSkill*)(*_pSkill)[i])->SetHitCount();

							if ((*_pMonster)[j]->GetStat().fHp <= 0)
							{
								((CMonster*)(*_pMonster)[j])->SetDrop(rand() % 2);
								(*_pMonster)[j]->SetState(ST_DEATH);
								fExp += (*_pMonster)[j]->GetStat().fExp;
							}		
						}
					}
				}
			}
			((CSkill*)(*_pSkill)[i])->SetHit(true);
		}
	}

	return fExp;
}

void CCollisionMgr::CollisionBoss(CParent* _pBoss, CParent* _pPlayer)
{
	if (((_pBoss->GetInfo().fX - _pPlayer->GetInfo().fX) >= 450.f) && (_pBoss->GetState() != ST_ATTACK))
	{
		_pBoss->SetState(ST_ATTACK);
	}
	else if (_pBoss->GetStat().fHp / _pBoss->GetStat().fFullHp <= 0.5 && _pBoss->GetState() != ST_ATTACK2)
	{
		_pBoss->SetState(ST_ATTACK2);
	}
	
	if (_pBoss->GetState() == ST_ATTACK)
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pPlayer->GetInfo().fX, _pPlayer->GetInfo().fY, "Boss_Back"));
		_pPlayer->SetPos(_pPlayer->GetInfo().fX + 4.f, _pPlayer->GetInfo().fY);
	}
	else if (_pBoss->GetState() == ST_ATTACK2)
	{
		if (!_pPlayer->GetUnbeatable())
		{
			CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pPlayer->GetInfo().fX, _pPlayer->GetInfo().fY, "Boss_Fire"));
			_pPlayer->SetUnbeatable(true);
			_pPlayer->SetDamage(_pBoss->GetStat().fAttack);
			CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pPlayer->GetInfo().fX, _pPlayer->GetInfo().fY - 30, int(_pBoss->GetStat().fAttack), "HitEffect"));
		}
	}

	if (_pBoss->GetStat().fHp <= 0)
	{	
		_pBoss->SetState(ST_DEATH);
		((CPlayer*)_pPlayer)->SetQuest(2);
	}

}


void CCollisionMgr::CollisionPortal(vector<CParent*>* _pPlayer, vector<CParent*>* _pPortal)
{
	RECT rc;
	CParent* pPlayer = _pPlayer->back();
	RECT rc1 = {pPlayer->GetRect().left + 15,
			pPlayer->GetRect().top,
			pPlayer->GetRect().right - 15,
			pPlayer->GetRect().bottom};

	for (size_t i = 0; i < _pPortal->size(); ++i)
	{
		if (pPlayer->GetInfo().fX >= (*_pPortal)[i]->GetInfo().fX - 100.f && pPlayer->GetInfo().fX <= (*_pPortal)[i]->GetInfo().fX + 100.f &&
					pPlayer->GetInfo().fY >= (*_pPortal)[i]->GetInfo().fY - 100.f && pPlayer->GetInfo().fY <= (*_pPortal)[i]->GetInfo().fY + 100.f)
		{
			RECT rc2 = {(*_pPortal)[i]->GetRect().left + 20,
						(*_pPortal)[i]->GetRect().top + 20,
						(*_pPortal)[i]->GetRect().right -20,
						(*_pPortal)[i]->GetRect().bottom};

			if (IntersectRect(&rc, &rc1, &rc2))
			{
				CSceneMgr::GetInstance()->SetScene(((CPortal*)(*_pPortal)[i])->GetPortal());
				return;
			}
		}
	}
}

void CCollisionMgr::CollisionBodyButt(vector<CParent*>*	_pPlayer, vector<CParent*>* _pMonster)
{
	RECT rc;
	CParent* pPlayer = _pPlayer->back();

	if(!pPlayer->GetUnbeatable())
	{
		for (size_t i = 0; i < _pMonster->size(); ++i)
		{
			if ((*_pMonster)[i]->GetState() != ST_DEATH)
			{
				if (pPlayer->GetInfo().fX >= (*_pMonster)[i]->GetInfo().fX - 50.f && pPlayer->GetInfo().fX <= (*_pMonster)[i]->GetInfo().fX + 50.f &&
							pPlayer->GetInfo().fY >= (*_pMonster)[i]->GetInfo().fY - 50.f && pPlayer->GetInfo().fY <= (*_pMonster)[i]->GetInfo().fY + 50.f)
				{
					if (IntersectRect(&rc, &pPlayer->GetRect(), &(*_pMonster)[i]->GetRect()))
					{
						pPlayer->SetState(ST_HIT);	
						pPlayer->SetUnbeatable(true);

						if ((*_pMonster)[i]->GetInfo().fX - pPlayer->GetInfo().fX >= 0)
						{
							pPlayer->SetPos(pPlayer->GetInfo().fX - 25, pPlayer->GetInfo().fY - 20);
						}
						else
						{
							pPlayer->SetPos(pPlayer->GetInfo().fX + 25, pPlayer->GetInfo().fY - 20);
						}
						
						AddEffect((*_pMonster)[i], pPlayer, 1);
					}
				}
			}
		}
	}

}

void CCollisionMgr::AddSkillEffect(CParent* _pSkill, CParent* _pMonster)
{
	if (_pSkill->GetStrKey() == "Annihilation_LEFT" || _pSkill->GetStrKey() == "Annihilation_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Annihilation_EFFECT"));

		if (_pSkill->GetStrKey() == "Annihilation_LEFT")
			_pMonster->SetPos(_pMonster->GetInfo().fX - 20, _pMonster->GetInfo().fY);

		else
			_pMonster->SetPos(_pMonster->GetInfo().fX + 20, _pMonster->GetInfo().fY);
	}

	if (_pSkill->GetStrKey() == "Ascend_LEFT" || _pSkill->GetStrKey() == "Ascend_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Ascend_EFFECT"));

		if (_pSkill->GetStrKey() == "Ascend_LEFT")
			_pMonster->SetPos(_pMonster->GetInfo().fX - 20, _pMonster->GetInfo().fY);

		else
			_pMonster->SetPos(_pMonster->GetInfo().fX + 20, _pMonster->GetInfo().fY);
	}

	if (_pSkill->GetStrKey() == "Typhoon_LEFT" ||_pSkill->GetStrKey() == "Typhoon_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Typhoon_EFFECT"));

		if (_pSkill->GetStrKey() == "Typhoon_LEFT")
			_pMonster->SetPos(_pMonster->GetInfo().fX - 20, _pMonster->GetInfo().fY);

		else
			_pMonster->SetPos(_pMonster->GetInfo().fX + 20, _pMonster->GetInfo().fY);
	}

	if (_pSkill->GetStrKey() == "Bolt_LEFT" || _pSkill->GetStrKey() == "Bolt_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Bolt_EFFECT"));

		if (_pSkill->GetStrKey() == "Bolt_LEFT")
			_pMonster->SetPos(_pMonster->GetInfo().fX - 20, _pMonster->GetInfo().fY);

		else
			_pMonster->SetPos(_pMonster->GetInfo().fX + 20, _pMonster->GetInfo().fY);
	}

	if (_pSkill->GetStrKey() == "Range")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Range_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Beyond_LEFT" || _pSkill->GetStrKey() == "Beyond_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond_EFFECT"));

		if (_pSkill->GetStrKey() == "Beyond_LEFT")
			_pMonster->SetPos(_pMonster->GetInfo().fX - 20, _pMonster->GetInfo().fY);

		else
			_pMonster->SetPos(_pMonster->GetInfo().fX + 20, _pMonster->GetInfo().fY);
	}

	if (_pSkill->GetStrKey() == "Beyond2_LEFT" || _pSkill->GetStrKey() == "Beyond2_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond2_EFFECT"));

		if (_pSkill->GetStrKey() == "Beyond2_LEFT")
			_pMonster->SetPos(_pMonster->GetInfo().fX - 20, _pMonster->GetInfo().fY);

		else
			_pMonster->SetPos(_pMonster->GetInfo().fX + 20, _pMonster->GetInfo().fY);
	}

	if (_pSkill->GetStrKey() == "Beyond3_LEFT" || _pSkill->GetStrKey() == "Beyond3_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond3_EFFECT"));

		if (_pSkill->GetStrKey() == "Beyond3_LEFT")
			_pMonster->SetPos(_pMonster->GetInfo().fX - 20, _pMonster->GetInfo().fY);

		else
			_pMonster->SetPos(_pMonster->GetInfo().fX + 20, _pMonster->GetInfo().fY);
	}

	if (_pSkill->GetStrKey() == "Fire_LEFT" || _pSkill->GetStrKey() == "Fire_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Fire_EFFECT"));

		if (_pSkill->GetStrKey() == "Fire_LEFT")
			_pMonster->SetPos(_pMonster->GetInfo().fX - 20, _pMonster->GetInfo().fY);

		else
			_pMonster->SetPos(_pMonster->GetInfo().fX + 20, _pMonster->GetInfo().fY);
	}
}

void CCollisionMgr::AddEffect(CParent* _pParent, CParent* _pDest, int Height)
{
	int Critical = rand() % 100;
	int iDamage = int(_pParent->GetStat().fAttack + (_pParent->GetStat().fAttack * Critical) / 100.f);


	if (_pDest->GetUnbeatable())
	{
		_pDest->SetDamage(_pParent->GetStat().fAttack);
		CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pDest->GetInfo().fX,_pDest->GetInfo().fY - (30.f * Height), iDamage, "HitEffect"));
	}
	if (Critical < 50)
	{
		_pDest->SetDamage((float)iDamage);
		CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pDest->GetInfo().fX,_pDest->GetInfo().fY - (30.f * Height), iDamage, "DamageEffect"));
	}
	if (Critical >= 50)
	{
		_pDest->SetDamage((float)iDamage);
		CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pDest->GetInfo().fX,_pDest->GetInfo().fY - (30.f * Height), iDamage, "CriticalEffect"));
	}

}

void CCollisionMgr::SkillDamage(CParent* _pSkill, CParent* _pMonster)
{
	if (_pSkill->GetStrKey() == "Annihilation_LEFT" || _pSkill->GetStrKey() == "Annihilation_RIGHT")
	{
		for (int i = 0; i < 2; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	if (_pSkill->GetStrKey() == "Ascend_LEFT" || _pSkill->GetStrKey() == "Ascend_RIGHT")
	{
		for (int i = 0; i < 2; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	if (_pSkill->GetStrKey() == "Typhoon_LEFT" ||_pSkill->GetStrKey() == "Typhoon_RIGHT")
	{
		for (int i = 0; i < 4; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	if (_pSkill->GetStrKey() == "Bolt_LEFT" || _pSkill->GetStrKey() == "Bolt_RIGHT")
	{
		for (int i = 0; i < 4; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	
	if (_pSkill->GetStrKey() == "Range")
	{
		for (int i = 0; i < 6; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	if (_pSkill->GetStrKey() == "Beyond_LEFT" || _pSkill->GetStrKey() == "Beyond_RIGHT")
	{
		for (int i = 0; i < 3; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	if (_pSkill->GetStrKey() == "Beyond2_LEFT" || _pSkill->GetStrKey() == "Beyond2_RIGHT")
	{
		for (int i = 0; i < 3; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	if (_pSkill->GetStrKey() == "Beyond3_LEFT" || _pSkill->GetStrKey() == "Beyond3_RIGHT")
	{
		for (int i = 0; i < 3; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	if (_pSkill->GetStrKey() == "Fire_LEFT" || _pSkill->GetStrKey() == "Fire_RIGHT")
	{
		for (int i = 0; i < 8; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}
}

void CCollisionMgr::CollisionItem(vector<CParent*>* _pPlayer, vector<CItem*>* _pItem, vector<CUI*>* _pInventory)
{
	RECT rc;
	CParent* pPlayer = _pPlayer->back();
	CUI*	pInventory = _pInventory->back();

	for (size_t i = 0; i < _pItem->size(); ++i)
	{
		if (pPlayer->GetInfo().fX >= (*_pItem)[i]->GetRect().left &&
			pPlayer->GetInfo().fX <= (*_pItem)[i]->GetRect().right)
		{
			if (IntersectRect(&rc, &pPlayer->GetRect(), &(*_pItem)[i]->GetRect()))
			{
				if ((*_pItem)[i]->GetItem().iType == IT_GOLD)
				{
					pPlayer->SetGold((*_pItem)[i]->GetItem().iOption);
					(*_pItem)[i]->SetDropID(0);
					::Safe_Delete((*_pItem)[i]);
					_pItem->erase(_pItem->begin() + i);
				}
				else
				{
					((CInventory*)pInventory)->AddItem((*_pItem)[i]);
					(*_pItem)[i]->SetDropID(0);
					_pItem->erase(_pItem->begin() + i);
				}
			}
		}
	}
}