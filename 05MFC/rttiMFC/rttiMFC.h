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

	// ��ԭ���滻  ���ȶ���һ����̬�Ĳ����޸ĵ�classMyApp
	static const CRuntimeClass classMyApp;
	virtual CRuntimeClass* GetRuntimeClass() const;

public:
	virtual BOOL InitInstance();

	// ��������Ϣ
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