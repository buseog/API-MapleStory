#pragma once

#include "bigheader.h"

class CKeyMgr
{
private:
	static CKeyMgr*		m_pInstance;
	DWORD				m_dwKey;

public:
	void	KeyCheck(void);
	DWORD	GetKey(void);

public:
	static CKeyMgr*		GetInstance(void)
	{
		if(m_pInstance == NULL)
			m_pInstance = new CKeyMgr;

		return m_pInstance;
	}

	void DestroyInst(void)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}


private:
	CKeyMgr(void);
	~CKeyMgr(void);
};
