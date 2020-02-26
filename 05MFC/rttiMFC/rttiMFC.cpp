// rttiMFC.cpp : 定义应用程序的入口点。

#include "rttiMFC.h"
MyApp m_objApp;

/*
	#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL, NULL)
*/

// IMPLEMENT_DYNAMIC(MyApp, CWinApp);

// 替换一
// IMPLEMENT_RUNTIMECLASS(MyApp, CWinApp, 0xFFFF, NULL, NULL);

// 还可以进一步替换为 实际上文字的替换游戏
// #define IMPLEMENT_RUNTIMECLASS(MyApp, base_class_name, wSchema, pfnNew, class_init) 
const CRuntimeClass MyApp::classMyApp =
{
		"MyApp", sizeof(class MyApp), 0xFFFF, NULL,((CRuntimeClass*)(&CWinApp::classCWinApp)), NULL, NULL
};
CRuntimeClass* MyApp::GetRuntimeClass() const
		{ 
	return (CRuntimeClass*)(&CWinApp::classCWinApp);
}

MyApp::MyApp()
{
	std::cout << "MyApp 构造函数" << std::endl;
}

MyApp::~MyApp()
{
	std::cout << "MyApp 析构函数" << std::endl;
}




BOOL MyApp::InitInstance()
{
	// 运行是类型识别 结构体RUNTIME_CLASS
	/*
	#define RUNTIME_CLASS(class_name) _RUNTIME_CLASS(class_name)
	*/
	int i = IsKindOf((CRuntimeClass*)(&CWinApp::classCWinApp));
	printInfo();
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

void MyApp::printInfo()
{
	// std::cout << classMyApp.m_pBaseClass << std::endl;
	// 打印出所有的父类信息 利用弗雷指针层层指向详细略
	OutputDebugString((LPCWSTR)classMyApp.m_pBaseClass->m_pBaseClass->m_pBaseClass->m_pBaseClass->m_pBaseClass);
	OutputDebugString((LPCWSTR)classMyApp.m_lpszClassName);
	OutputDebugString((LPCWSTR)classMyApp.m_pfnCreateObject);
}


// IMPLEMENT_DYNAMIC(CMainWindow, CFrameWnd)

// #define IMPLEMENT_RUNTIMECLASS(CMainWindow, base_class_name, wSchema, pfnNew, class_init)
const CRuntimeClass CMainWindow::classCMainWindow = {
		"CMainWindow", sizeof(class CMainWindow), 0xFFFF, NULL,
			RUNTIME_CLASS(CFrameWnd), NULL, NULL };
	CRuntimeClass* CMainWindow::GetRuntimeClass() const
		{ return RUNTIME_CLASS(CMainWindow); }

CMainWindow::CMainWindow()
{
	// RECT rect = { 500, 400, 800, 700 };
	Create(NULL, L"HelloMFC");
}
