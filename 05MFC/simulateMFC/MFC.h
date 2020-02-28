#pragma once
#define BOOL int
#define TRUE 1
#define FALSE 0

#include <iostream>
using namespace std;

// vs编译《深入浅出MFC》章3 

class CObject
{
public:
	CObject() { }
	~CObject() { }
};


class CCmdTarget :
	 public CObject
{
public:

	CCmdTarget() { }
	~CCmdTarget() { }
};

class CWinThread :
	 public CCmdTarget
{
public:

	CWinThread() { }
	~CWinThread() { }

	// 添加虚函数，模拟初始化过程
	virtual BOOL InitInstance() 
	{
		cout << "CWinThread::InitInstance" << endl;
		return TRUE;
	}

	virtual int Run() 
	{
		cout << "CWinThread::Run" << endl;
		return TRUE;
	}
};

class CWnd :
	public CCmdTarget
{
public:

	CWnd() { }
	~CWnd() { }

	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
};

class CWinApp :
	public CWinThread
{
public:
	CWinApp* m_pCurrentWinApp;
	CWnd* m_pMainWnd;

public:
	CWinApp() { m_pCurrentWinApp = this; }
	~CWinApp() { }

	virtual BOOL InitApplication()
	{
		cout << "CWinApp::InitApplication" << endl;
		return TRUE;
	}

	virtual BOOL InitInstance()
	{
		cout << "CWinApp::InitInstance"<< endl;
		return TRUE;
	}

	virtual int Run()
	{
		cout << "CWinApp::Run" << endl;
		return CWinThread::Run();
	}

};

class CDocument :
	public CCmdTarget
{
public:
	CDocument() { }
	~CDocument() { }
};




class CFrameWnd :
	 public CWnd
{
public:

	CFrameWnd() { }
	~CFrameWnd() { }
	BOOL Create();
	virtual BOOL PreCreateWindow();
};

class CView :
	public CWnd
{
public:
	CView() { }
	~CView() { }
};


// 定义全局函数
CWinApp* AfxGetApp();