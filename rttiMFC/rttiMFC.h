#pragma once
#include <iostream>
#include <afxwin.h>
#include <tchar.h>

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
	DECLARE_DYNAMIC(MyApp);
public:
	virtual BOOL InitInstance();
};


class MainWindow :public CFrameWnd
{
public:
	MainWindow();
	DECLARE_DYNCREATE(MainWindow);

};