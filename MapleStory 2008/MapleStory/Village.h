#pragma once
#include "Scene.h"

class CParent;
class CNPC;


class CVillage	:
	public CScene
{
private:
	CNPC*	m_pStoreNPC;
	CNPC*	m_pQuestNPC;

public:
	virtual void Initialize(void);
	virtual void Progress(DWORD _delta);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CVillage(void);
	~CVillage(void);
};
