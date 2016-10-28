#pragma once

#include "Parent.h"

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

public:
	CFactory(void){}
	~CFactory(void){}
};
