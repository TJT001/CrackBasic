#pragma once
#include "WinApp.h"

class CMyApp :
	public CWinApp
{
public:
	CMyApp();
	~CMyApp();

	virtual bool Instance();
public:
	// ����һ��ָ�������浱ǰ�Ķ���
	CMyApp* m_CurrentApp;
};

