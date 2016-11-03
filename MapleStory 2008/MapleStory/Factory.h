#pragma once

#include "Parent.h"
#include "UI.h"

template<typename T>
class CFactory
{
public:
	static CParent* CreateParent(void)
	{
		CParent* pParent = new T;

		pParent->Initialize();

		return pParent;
	}
	
	static CParent* CreateParent(float _fX, float _fY)
	{
		CParent* pParent = new T;

		pParent->Initialize();
		pParent->SetPos(_fX, _fY);

		return pParent;
	}

	static CParent* CreateParent(float _fX, float _fY, string _strKey)
	{
		CParent* pParent = new T;
		pParent->SetStrKey(_strKey);
		pParent->Initialize();
		pParent->SetPos(_fX, _fY);

		return pParent;
	}

	static CParent* CreateParent(float _fX, float _fY, int _Damage, string _strKey)
	{
		CParent* pParent = new T;
		pParent->SetStrKey(_strKey);
		((T*)pParent)->SetDamage(_Damage);
		pParent->Initialize();
		pParent->SetPos(_fX, _fY);

		return pParent;
	}

	static CUI* CreateUI(float _fX, float _fY)
	{
		CUI* pUI = new T;
		pUI->Initialize();
		pUI->SetPos(_fX, _fY);

		return pUI;
	}

	static CUI* CreateUI(float _fX, float _fY, string _strKey)
	{
		CUI* pUI = new T(_strKey);
		pUI->Initialize();
		pUI->SetPos(_fX, _fY);

		return pUI;
	}

public:
	CFactory(void){}
	~CFactory(void){}
};
