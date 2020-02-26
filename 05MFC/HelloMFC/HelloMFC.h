#pragma once
#include<afxwin.h>

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow :public CFrameWnd
{
public:
	CMainWindow();
};