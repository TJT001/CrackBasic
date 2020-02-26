#pragma once
#include <iostream>
#include <afxwin.h>

class CMyApp : public CWinApp
{
public:
	CMyApp();
	~CMyApp();

	static const CRuntimeClass classMyApp;
	virtual CRuntimeClass* GetRuntimeClass() const;

public:
	virtual BOOL InitInstance();

};


class CMainWindow :public CFrameWnd
{
	// ¶¯Ì¬´´½¨
	// DECLARE_DYNCREATE(CMainWindow)

/*
#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject* PASCAL CreateObject();
*/

public:

	// DECLARE_DYNAMIC(CMainWindow);

	static const CRuntimeClass classCMainWindow;
	virtual CRuntimeClass* GetRuntimeClass() const;

	// DECLARE_DYNAMIC(CMainWindow)
	static CObject* PASCAL CreateObject();
	CMainWindow();

	
};
