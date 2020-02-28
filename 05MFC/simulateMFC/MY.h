#pragma once
#include <iostream>
#include "MFC.h"

class CMyWinApp :
	public CWinApp
{
public:
	CMyWinApp() { }
	~CMyWinApp() { }
	virtual BOOL InitInstance();
};

class CMyFrameWnd :
	public CFrameWnd
{
public:
	CMyFrameWnd() { cout << "CMyFrameWnd Constructor" << endl; }
	~CMyFrameWnd() { cout << "CMyFrameWnd Destructor" << endl; }
};