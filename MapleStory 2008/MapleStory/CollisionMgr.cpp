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

	for (size_t j = 0; j < _pTile->size(); ++j)
	{
		if ((*_pTile)[j]->iOption)
		{
			if (IntersectRect(&rc, &pPlayer->GetRect(), &(*_pTile)[j]->GetRect()))
			{
				if ((pPlayer->GetInfo().fX >= (*_pTile)[j]->GetRect().left) && (pPlayer->GetInfo().fX <= (*_pTile)[j]->GetRect().right))
				{
					LONG fLength = rc.right - rc.left;
					LONG fHeight = rc.bottom - rc.top;

					if (fLength > fHeight)			//�����浹
					{
						switch ((*_pTile)[j]->iOption)
						{
						case 1:
							if ((pPlayer->GetRect().top <= (*_pTile)[j]->GetRect().top) && (pPlayer->GetJumpPower() >= 0))	//�÷��̾ ���̰�, ������ �������� ���϶�
							{
								if (pPlayer->GetState() == ST_UP)
									pPlayer->SetState(ST_STAND);

								pPlayer->SetLand(true);
								pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - fHeight);
							}
							break;

						case 2:
							if ((pPlayer->GetInfo().fY <= (*_pTile)[j]->GetRect().top) && (pPlayer->GetJumpPower() >= 0))	
							{
								if (pPlayer->GetState() == ST_UP)
									pPlayer->SetState(ST_STAND);
												
								pPlayer->SetLand(true);
								pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - fHeight);
							}
							break;

						case 3:
							if (pPlayer->GetState() != ST_UP)
							{
								if (GetAsyncKeyState(VK_UP))
								{
									pPlayer->SetLand(true);
									pPlayer->SetState(ST_UP);
									pPlayer->SetPos((*_pTile)[j]->fX, pPlayer->GetInfo().fY - 10.f);
								}
							}
							break;

						case 4:
							if ((pPlayer->GetInfo().fY <= (*_pTile)[j]->GetRect().top) && (pPlayer->GetJumpPower() >= 0))
							{
								if  (pPlayer->GetState() != ST_UP)
								{
									pPlayer->SetLand(true);
									pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - fHeight);

									if (GetAsyncKeyState(VK_DOWN) )
									{
										if (pPlayer->GetState() != ST_UP)
											pPlayer->SetPos((*_pTile)[j]->fX, pPlayer->GetInfo().fY + 30.f);

										pPlayer->SetLand(true);
										pPlayer->SetState(ST_UP);
										
									}
								}
								else
								{
									pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY - fHeight);
									pPlayer->SetState(ST_STAND);
								}

							}
							break;
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
		for (size_t j = 0; j < _pTile->size(); ++j)
		{
			if (!(*_pTile)[j]->iOption == 0)
			{
				if (IntersectRect(&rc, &(*_pMonster)[i]->GetRect(), &(*_pTile)[j]->GetRect()))
				{
					LONG fLength = rc.right - rc.left;
					LONG fHeight = rc.bottom - rc.top;

					if (fLength > fHeight)			//�����浹
					{
						switch ((*_pTile)[j]->iOption)
						{
						case 1:
							if ((rc.top <= (*_pTile)[j]->GetRect().top) && ((*_pMonster)[i]->GetJumpPower() >= 0))
							{
								(*_pMonster)[i]->SetLand(true);
								(*_pMonster)[i]->SetPos((*_pMonster)[i]->GetInfo().fX, (*_pMonster)[i]->GetInfo().fY - fHeight);
							}
							break;

						case 2:
							if ((rc.top <= (*_pTile)[j]->GetRect().top) && ((*_pMonster)[i]->GetJumpPower() >= 0))
							{
								(*_pMonster)[i]->SetLand(true);
								(*_pMonster)[i]->SetPos((*_pMonster)[i]->GetInfo().fX, (*_pMonster)[i]->GetInfo().fY - fHeight);
							}
							break;
						}
					}
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
		for (size_t j = 0; j < _pTile->size(); ++j)
		{
			if (!(*_pTile)[j]->iOption == 0)
			{
				if (IntersectRect(&rc, &(*_pItem)[i]->GetRect(), &(*_pTile)[j]->GetRect()))
				{
					LONG fLength = rc.right - rc.left;
					LONG fHeight = rc.bottom - rc.top;

					if (fLength > fHeight)			//�����浹
					{
						switch ((*_pTile)[j]->iOption)
						{
						case 1:
							if (rc.top <= (*_pTile)[j]->GetRect().top)
							{
								(*_pItem)[i]->SetPos((*_pItem)[i]->GetInfo().fX, (*_pItem)[i]->GetInfo().fY - fHeight);
							}
							break;

						case 2:
							if (rc.top <= (*_pTile)[j]->GetRect().top)
							{
								(*_pItem)[i]->SetPos((*_pItem)[i]->GetInfo().fX, (*_pItem)[i]->GetInfo().fY - fHeight);
							}
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
	float fExp = 0.f;

	for (size_t i = 0; i < _pSkill->size(); ++i)
	{
		for (size_t j = 0; j < _pMonster->size(); ++j)
		{
			if (!((CSkill*)(*_pSkill)[i])->GetHit())
			{
				if (IntersectRect(&rc, &(*_pSkill)[i]->GetRect(), &(*_pMonster)[j]->GetRect()))
				{
					LONG fLength = rc.right - rc.left;
					LONG fHeight = rc.bottom - rc.top;

					(*_pMonster)[j]->SetState(ST_HIT);

					SkillDamage((*_pSkill)[i], (*_pMonster)[j]);
					AddSkillEffect((*_pSkill)[i], (*_pMonster)[j]);

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

	return fExp;
}


//float CCollisionMgr::CollisionSKill(vector<CParent*>* _pSkill, vector<CParent*>* _pMonster)
//{
//	RECT rc;
//	float fExp = 0.f;
//
//	for (size_t i = 0; i < _pSkill->size(); ++i)
//	{
//		for (size_t j = 0; j < _pMonster->size(); ++j)
//		{
//			if (!((CSkill*)(*_pSkill)[i])->GetHit())
//			{
//				if (IntersectRect(&rc, &(*_pSkill)[i]->GetRect(), &(*_pMonster)[j]->GetRect()))
//				{
//					LONG fLength = rc.right - rc.left;
//					LONG fHeight = rc.bottom - rc.top;
//
//					if (fLength > fHeight)
//					{
//						(*_pMonster)[j]->SetState(ST_HIT);
//
//						SkillDamage((*_pSkill)[i], (*_pMonster)[j]);
//						AddSkillEffect((*_pSkill)[i], (*_pMonster)[j]);
//
//						if ((*_pMonster)[j]->GetStat().fHp <= 0)
//						{
//							((CMonster*)(*_pMonster)[j])->SetDrop(rand() % 2);
//							((*_pMonster)[j]->SetDestroy(true));
//
//							return (*_pMonster)[j]->GetStat().fExp;
//						}
//					}
//					else if (fHeight > fLength)
//					{
//						(*_pMonster)[j]->SetState(ST_HIT);
//
//						SkillDamage((*_pSkill)[i], (*_pMonster)[j]);
//						AddSkillEffect((*_pSkill)[i], (*_pMonster)[j]);
//
//						if ((*_pMonster)[j]->GetStat().fHp <= 0)
//						{
//							((CMonster*)(*_pMonster)[j])->SetDrop(rand() % 2);
//							((*_pMonster)[j]->SetDestroy(true));
//
//							return (*_pMonster)[j]->GetStat().fExp;
//						}
//					}
//				}
//			}
//		}
//		((CSkill*)(*_pSkill)[i])->SetHit(true);
//	}
//
//	return fExp;
//}

void CCollisionMgr::CollisionPortal(vector<CParent*>* _pPlayer, vector<CParent*>* _pPortal)
{
	RECT rc;
	CParent* pPlayer = _pPlayer->back();

	for (size_t j = 0; j < _pPortal->size(); ++j)
	{
		if (IntersectRect(&rc, &pPlayer->GetRect(), &(*_pPortal)[j]->GetRect()))
		{
			CSceneMgr::GetInstance()->SetScene(((CPortal*)(*_pPortal)[j])->GetPortal());
			return;
		}
	}
}

void CCollisionMgr::CollisionBodyButt(vector<CParent*>*	_pPlayer, vector<CParent*>* _pMonster)
{
	RECT rc;
	CParent* pPlayer = _pPlayer->back();

	for (size_t i = 0; i < _pMonster->size(); ++i)
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

	if (_pSkill->GetStrKey() == "Range")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Range_EFFECT"));
	}

	if (_pSkill->GetStrKey() == "Beyond_LEFT" || _pSkill->GetStrKey() == "Beyond_RIGHT")
	{
		CScene::SetEffect(CFactory<CSkillEffect>::CreateParent(_pMonster->GetInfo().fX,_pMonster->GetInfo().fY, "Beyond_EFFECT"));
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
		for (int i = 0; i < 8; ++i)
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
}

void CCollisionMgr::CollisionItem(vector<CParent*>* _pPlayer, vector<CItem*>* _pItem, vector<CUI*>* _pInventory)
{
	RECT rc;
	CParent* pPlayer = _pPlayer->back();
	CUI*	pInventory = _pInventory->back();

	for (size_t i = 0; i < _pItem->size(); ++i)
	{
		if (IntersectRect(&rc, &pPlayer->GetRect(), &(*_pItem)[i]->GetRect()))
		{
			if (pPlayer->GetInfo().fX > (*_pItem)[i]->GetRect().left &&
				pPlayer->GetInfo().fX < (*_pItem)[i]->GetRect().right)
			{
				if ((*_pItem)[i]->GetItem().iType == IT_GOLD)
				{
					pPlayer->SetGold((*_pItem)[i]->GetItem().iOption);
					(*_pItem)[i]->SetDropID(0);
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