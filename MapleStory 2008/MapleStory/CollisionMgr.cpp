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
		if ((*_pTile)[i]->iOption)
		{
			if (pPlayer->GetInfo().fX >= (*_pTile)[i]->fX - 100.f && pPlayer->GetInfo().fX <= (*_pTile)[i]->fX + 100.f &&
					pPlayer->GetInfo().fY >= (*_pTile)[i]->fY - 100.f && pPlayer->GetInfo().fY <= (*_pTile)[i]->fY + 100.f)
			{
				if (IntersectRect(&rc, &pPlayer->GetRect(), &(*_pTile)[i]->GetRect()))
				{
					LONG lWidth = rc.right - rc.left;
					LONG lHeight = rc.bottom - rc.top;

					if (lWidth > lHeight)			//상하충돌
					{
						if (pPlayer->GetRect().bottom <= (*_pTile)[i]->fY && pPlayer->GetJumpPower() >= 0)
						{
							switch ((*_pTile)[i]->iOption)
							{
							case 1:
								if (pPlayer->GetState() == ST_UP)
									pPlayer->SetState(ST_STAND);

								pPlayer->SetLand(true);
								pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - lHeight);
								break;

							case 2:
								if (pPlayer->GetState() == ST_UP)
									pPlayer->SetState(ST_STAND);
												
								pPlayer->SetLand(true);
								pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - lHeight);
								break;

							case 3:
								if (pPlayer->GetState() != ST_UP)
								{
									if (GetAsyncKeyState(VK_UP))
									{
										pPlayer->SetLand(true);
										pPlayer->SetState(ST_UP);
										pPlayer->SetPos((*_pTile)[i]->fX, pPlayer->GetInfo().fY - 10.f);
									}
								}
								break;

							case 4:
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
										
									}
								}
								else
								{
									pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - lHeight);
									pPlayer->SetState(ST_STAND);
								}
								break;
							}
						}
					}
				}
			}
		}
	}
}
void CCollisionMgr::CollisionMTile(vector<CParent*>* _pMonster, vector<TILE*>* _pTile)
{
	RECT rc;

	for (size_t i = 0; i < _pMonster->size(); ++i)
	{
		int ScrollX = (*_pMonster)[i]->GetInfo().fX - 350;
		int ScrollY = (*_pMonster)[i]->GetInfo().fY - 250;

		if (ScrollX <= 0)
			ScrollX = 0;

		if (ScrollY <= 0)
			ScrollY = 0;

		int iCountX = ScrollX / TILECX;
		int iCountY = ScrollY / TILECY;

		for (int j = 0 ; j < 30; ++j)
		{
			for (int k = 0; k < 30; ++k)
			{
				int iIndex = (j + iCountY) * 59 + (k + iCountX);
				
				if(iIndex < 0 || iIndex >= 59 * 48)
					return;

				if ((*_pTile)[iIndex]->iOption)
				{
					if (IntersectRect(&rc, &(*_pMonster)[i]->GetRect(), &(*_pTile)[iIndex]->GetRect()))
					{
						LONG lWidth = rc.right - rc.left;
						LONG lHeight = rc.bottom - rc.top;

						if (lWidth > lHeight)			//상하충돌
						{
							if ((*_pMonster)[i]->GetRect().top <= (*_pTile)[iIndex]->GetRect().top)
							{
								switch ((*_pTile)[iIndex]->iOption)
								{
								case 1:
									(*_pMonster)[i]->SetLand(true);
									(*_pMonster)[i]->SetPos((*_pMonster)[i]->GetInfo().fX, (*_pMonster)[i]->GetInfo().fY - lHeight);
									break;

								case 2:
									(*_pMonster)[i]->SetLand(true);
									(*_pMonster)[i]->SetPos((*_pMonster)[i]->GetInfo().fX, (*_pMonster)[i]->GetInfo().fY - lHeight);
									break;
								case 3:
									break;

								case 4:
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

//void CCollisionMgr::CollisionMTile(vector<CParent*>* _pMonster, vector<TILE*>* _pTile)
//{
//	RECT rc;
//
//	for (size_t i = 0; i < _pMonster->size(); ++i)
//	{
//		for (size_t j = 0; j < _pTile->size(); ++j)
//		{
//			if ((*_pTile)[j]->iOption)
//			{
//				if ((*_pMonster)[i]->GetInfo().fX >= (*_pTile)[j]->fX - 100.f && (*_pMonster)[i]->GetInfo().fX <= (*_pTile)[j]->fX + 100.f &&
//					(*_pMonster)[i]->GetInfo().fY >= (*_pTile)[j]->fY - 100.f && (*_pMonster)[i]->GetInfo().fY <= (*_pTile)[j]->fY + 100.f)
//				{
//					if (IntersectRect(&rc, &(*_pMonster)[i]->GetRect(), &(*_pTile)[j]->GetRect()))
//					{
//						LONG lWidth = rc.right - rc.left;
//						LONG lHeight = rc.bottom - rc.top;
//
//						if (lWidth > lHeight)			//상하충돌
//						{
//							if ((*_pMonster)[i]->GetRect().top <= (*_pTile)[j]->GetRect().top)
//							{
//								switch ((*_pTile)[j]->iOption)
//								{
//								case 1:
//									(*_pMonster)[i]->SetLand(true);
//									(*_pMonster)[i]->SetPos((*_pMonster)[i]->GetInfo().fX, (*_pMonster)[i]->GetInfo().fY - lHeight);
//									break;
//
//								case 2:
//									(*_pMonster)[i]->SetLand(true);
//									(*_pMonster)[i]->SetPos((*_pMonster)[i]->GetInfo().fX, (*_pMonster)[i]->GetInfo().fY - lHeight);
//									break;
//								case 3:
//									break;
//
//								case 4:
//									break;
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}


void CCollisionMgr::CollisionITile(vector<CItem*>* _pItem, vector<TILE*>* _pTile)
{
	RECT rc;

	for (size_t i = 0; i < _pItem->size(); ++i)
	{
		for (size_t j = 0; j < _pTile->size(); ++j)
		{
			if ((*_pTile)[j]->iOption)
			{
				if ((*_pItem)[i]->GetInfo().fX >= (*_pTile)[j]->fX - 100.f && (*_pItem)[i]->GetInfo().fX <= (*_pTile)[j]->fX + 100.f &&
					(*_pItem)[i]->GetInfo().fY >= (*_pTile)[j]->fY - 100.f && (*_pItem)[i]->GetInfo().fY <= (*_pTile)[j]->fY + 100.f)
				{
					if (IntersectRect(&rc, &(*_pItem)[i]->GetRect(), &(*_pTile)[j]->GetRect()))
					{
						LONG lWidth = rc.right - rc.left;
						LONG lHeight = rc.bottom - rc.top;

						switch ((*_pTile)[j]->iOption)
						{
						case 1:
							(*_pItem)[i]->SetPos((*_pItem)[i]->GetInfo().fX, (*_pItem)[i]->GetInfo().fY - lHeight);
							break;	

						case 2:
							(*_pItem)[i]->SetPos((*_pItem)[i]->GetInfo().fX, (*_pItem)[i]->GetInfo().fY - lHeight);
							break;
						}
					}
				}
			}
		}
	}
}

float CCollisionMgr::CollisionSKill(vector<CParent*>* _pSkill, vector<CParent*>* _pMonster)
{
	RECT rc;

	for (size_t i = 0; i < _pSkill->size(); ++i)
	{
		if (!((CSkill*)(*_pSkill)[i])->GetHit() && ((CSkill*)(*_pSkill)[i])->GetHitCount() > 0)
		{
			for (size_t j = 0; j < _pMonster->size(); ++j)
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
							((*_pMonster)[j]->SetDestroy(true));

							return (*_pMonster)[j]->GetStat().fExp;
						}
						
					}
				}
			}
			((CSkill*)(*_pSkill)[i])->SetHit(true);
		}
	}

	return 0.f;
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

	for (size_t i = 0; i < _pMonster->size(); ++i)
	{
		if (pPlayer->GetInfo().fX >= (*_pMonster)[i]->GetInfo().fX - 100.f && pPlayer->GetInfo().fX <= (*_pMonster)[i]->GetInfo().fX + 100.f &&
					pPlayer->GetInfo().fY >= (*_pMonster)[i]->GetInfo().fY - 100.f && pPlayer->GetInfo().fY <= (*_pMonster)[i]->GetInfo().fY + 100.f)
		{
			if (IntersectRect(&rc, &pPlayer->GetRect(), &(*_pMonster)[i]->GetRect()))
			{
				if(!pPlayer->GetUnbeatable())
				{
					pPlayer->SetState(ST_HIT);	
					if ((*_pMonster)[i]->GetInfo().fX - pPlayer->GetInfo().fX >= 0)
						pPlayer->SetPos(pPlayer->GetInfo().fX - 10, pPlayer->GetInfo().fY - 20);

					else
						pPlayer->SetPos(pPlayer->GetInfo().fX + 10, pPlayer->GetInfo().fY - 20);

					pPlayer->SetUnbeatable(true);
					AddEffect((*_pMonster)[i], pPlayer, 1);
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
	}

	else if (_pSkill->GetStrKey() == "Ascend_LEFT" || _pSkill->GetStrKey() == "Ascend_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Ascend_EFFECT"));
	}

	else if (_pSkill->GetStrKey() == "Typhoon_LEFT" ||_pSkill->GetStrKey() == "Typhoon_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX, _pMonster->GetInfo().fY, "Typhoon_EFFECT"));
	}

	else if (_pSkill->GetStrKey() == "Bolt_LEFT" || _pSkill->GetStrKey() == "Bolt_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Bolt_EFFECT"));
	}

	else if (_pSkill->GetStrKey() == "Range")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Range_EFFECT"));
	}

	else if (_pSkill->GetStrKey() == "Beyond_LEFT" || _pSkill->GetStrKey() == "Beyond_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond_EFFECT"));
	}

	else if (_pSkill->GetStrKey() == "Beyond2_LEFT" || _pSkill->GetStrKey() == "Beyond2_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond2_EFFECT"));
	}

	else if (_pSkill->GetStrKey() == "Beyond3_LEFT" || _pSkill->GetStrKey() == "Beyond3_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond3_EFFECT"));
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
	else if (Critical < 50)
	{
		_pDest->SetDamage((float)iDamage);
		CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pDest->GetInfo().fX,_pDest->GetInfo().fY - (30.f * Height), iDamage, "DamageEffect"));
	}
	else if (Critical >= 50)
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

	else if (_pSkill->GetStrKey() == "Ascend_LEFT" || _pSkill->GetStrKey() == "Ascend_RIGHT")
	{
		for (int i = 0; i < 2; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	else if (_pSkill->GetStrKey() == "Typhoon_LEFT" ||_pSkill->GetStrKey() == "Typhoon_RIGHT")
	{
		for (int i = 0; i < 4; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	else if (_pSkill->GetStrKey() == "Bolt_LEFT" || _pSkill->GetStrKey() == "Bolt_RIGHT")
	{
		for (int i = 0; i < 4; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	
	else if (_pSkill->GetStrKey() == "Range")
	{
		for (int i = 0; i < 8; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	else if (_pSkill->GetStrKey() == "Beyond_LEFT" || _pSkill->GetStrKey() == "Beyond_RIGHT")
	{
		for (int i = 0; i < 3; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	else if (_pSkill->GetStrKey() == "Beyond2_LEFT" || _pSkill->GetStrKey() == "Beyond2_RIGHT")
	{
		for (int i = 0; i < 3; ++i)
		{
			AddEffect(_pSkill, _pMonster, i);
		}
	}

	else if (_pSkill->GetStrKey() == "Beyond3_LEFT" || _pSkill->GetStrKey() == "Beyond3_RIGHT")
	{
		for (int i = 0; i < 3; ++i)
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