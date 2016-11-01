#pragma once
#include "effect.h"

class CSkillEffect :
	public CEffect
{
public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);
public:
	CSkillEffect(void);
	~CSkillEffect(void);
};
