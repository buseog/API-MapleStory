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

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

void CCollisionMgr::CollisionPTile(vector<CParent*>* _pPlayer, vector<TILE*>* _pTile)
{
	RECT rc;

	for (size_t j = 0; j < _pTile->size(); ++j)
	{
		if (!(*_pTile)[j]->iOption == 0)
		{
			if (IntersectRect(&rc, &_pPlayer->back()->GetRect(), &(*_pTile)[j]->GetRect()))
			{
				if ((_pPlayer->back()->GetInfo().fX >= (*_pTile)[j]->GetRect().left) && (_pPlayer->back()->GetInfo().fX <= (*_pTile)[j]->GetRect().right))
				{
					LONG fLength = rc.right - rc.left;
					LONG fHeight = rc.bottom - rc.top;

					if (fLength > fHeight)			//상하충돌
					{
						switch ((*_pTile)[j]->iOption)
						{
						case 1:
							if ((_pPlayer->back()->GetRect().top <= (*_pTile)[j]->GetRect().top) && (_pPlayer->back()->GetJumpPower() >= 0))	//플레이어가 위이고, 점프가 내려가는 중일때
							{
								if (_pPlayer->back()->GetState() == ST_UP)
									_pPlayer->back()->SetState(ST_STAND);

								_pPlayer->back()->SetLand(true);
								_pPlayer->back()->SetPos(_pPlayer->back()->GetInfo().fX, _pPlayer->back()->GetInfo().fY - fHeight);
							}
							break;

						case 2:
							if ((_pPlayer->back()->GetInfo().fY <= (*_pTile)[j]->GetRect().top) && (_pPlayer->back()->GetJumpPower() >= 0))	
							{
								if (_pPlayer->back()->GetState() == ST_UP)
									_pPlayer->back()->SetState(ST_STAND);
												
								_pPlayer->back()->SetLand(true);
								_pPlayer->back()->SetPos(_pPlayer->back()->GetInfo().fX, _pPlayer->back()->GetInfo().fY - fHeight);
							}
							break;

						case 3:
							if ((_pPlayer->back()->GetRect().top <= (*_pTile)[j]->GetRect().top) && (_pPlayer->back()->GetState() != ST_UP) && (_pPlayer->back()->GetState() != ST_JUMP))
							{
								_pPlayer->back()->SetPos(_pPlayer->back()->GetInfo().fX, _pPlayer->back()->GetInfo().fY - fHeight);
							}

							if (_pPlayer->back()->GetState() != ST_UP)
							{
								if (GetAsyncKeyState(VK_UP))
								{
									_pPlayer->back()->SetLand(true);
									_pPlayer->back()->SetState(ST_UP);
									_pPlayer->back()->SetPos((*_pTile)[j]->fX, _pPlayer->back()->GetInfo().fY - 10.f);
								}

								if (GetAsyncKeyState(VK_DOWN))
								{
									_pPlayer->back()->SetLand(true);
									_pPlayer->back()->SetState(ST_UP);
									_pPlayer->back()->SetPos((*_pTile)[j]->fX, _pPlayer->back()->GetInfo().fY + 20.f);
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

					if (fLength > fHeight)			//상하충돌
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

					if (fLength > fHeight)			//상하충돌
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

					if (fLength > fHeight)
					{
						(*_pMonster)[j]->SetState(ST_HIT);

						SkillDamage((*_pSkill)[i], (*_pMonster)[j]);
						AddSkillEffect((*_pSkill)[i], (*_pMonster)[j]);

						if ((*_pMonster)[j]->GetStat().fHp <= 0)
						{
							((CMonster*)(*_pMonster)[j])->SetDrop(rand() % 2);
							((*_pMonster)[j]->SetDestroy(true));

							fExp =  (*_pMonster)[j]->GetStat().fExp;
						}
					}
					if (fHeight > fLength)
					{
						(*_pMonster)[j]->SetState(ST_HIT);

						SkillDamage((*_pSkill)[i], (*_pMonster)[j]);
						AddSkillEffect((*_pSkill)[i], (*_pMonster)[j]);

						if ((*_pMonster)[j]->GetStat().fHp <= 0)
						{
							((CMonster*)(*_pMonster)[j])->SetDrop(rand() % 2);
							((*_pMonster)[j]->SetDestroy(true));

							fExp = (*_pMonster)[j]->GetStat().fExp;
						}
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

	for (size_t j = 0; j < _pPortal->size(); ++j)
	{
		if (IntersectRect(&rc, &_pPlayer->back()->GetRect(), &(*_pPortal)[j]->GetRect()))
		{
			CSceneMgr::GetInstance()->SetScene(((CPortal*)(*_pPortal)[j])->GetPortal());
			return;
		}
	}
}

void CCollisionMgr::CollisionBodyButt(vector<CParent*>*	_pPlayer, vector<CParent*>* _pMonster)
{
	RECT rc;

	for (size_t i = 0; i < _pMonster->size(); ++i)
	{
		if (IntersectRect(&rc, &_pPlayer->back()->GetRect(), &(*_pMonster)[i]->GetRect()))
		{
			if(!_pPlayer->back()->GetUnbeatable())
			{
				_pPlayer->back()->SetState(ST_HIT);	
				if ((*_pMonster)[i]->GetInfo().fX - _pPlayer->back()->GetInfo().fX >= 0)
					_pPlayer->back()->SetPos(_pPlayer->back()->GetInfo().fX - 10, _pPlayer->back()->GetInfo().fY - 20);

				else
					_pPlayer->back()->SetPos(_pPlayer->back()->GetInfo().fX + 10, _pPlayer->back()->GetInfo().fY - 20);

				_pPlayer->back()->SetUnbeatable(true);
				AddEffect((*_pMonster)[i], _pPlayer->back(), 1);
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
		CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pDest->GetInfo().fX,_pDest->GetInfo().fY - (50.f * Height), iDamage, "HitEffect"));
	}
	else if (Critical < 50)
	{
		_pDest->SetDamage((float)iDamage);
		CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pDest->GetInfo().fX,_pDest->GetInfo().fY - (50.f * Height), iDamage, "DamageEffect"));
	}
	else if (Critical >= 50)
	{
		_pDest->SetDamage((float)iDamage);
		CScene::SetEffect(CFactory<CDamageEffect>::CreateParent(_pDest->GetInfo().fX,_pDest->GetInfo().fY - (50.f * Height), iDamage, "CriticalEffect"));
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