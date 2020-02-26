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
	// 定义一个指针来保存当前的对象
	CMyApp* m_CurrentApp;
};

