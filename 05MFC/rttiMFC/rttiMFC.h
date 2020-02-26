#pragma once
#include <iostream>
#include <afxwin.h>

class MyApp : public CWinApp
{
public:
	MyApp();
	~MyApp();

	/*
	#define DECLARE_DYNAMIC(class_name) \
public: \
	static const CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const; \
	*/

	// DECLARE_DYNAMIC(MyApp);

	// 还原宏替换  首先定义一个静态的不可修改的classMyApp
	static const CRuntimeClass classMyApp;
	virtual CRuntimeClass* GetRuntimeClass() const;

public:
	virtual BOOL InitInstance();

	// 但因父类信息
	void printInfo();
};


class CMainWindow :public CFrameWnd
{
public:

	// DECLARE_DYNAMIC(CMainWindow);

	static const CRuntimeClass classCMainWindow;
	virtual CRuntimeClass* GetRuntimeClass() const;
	CMainWindow();

};