// rttiMFC.cpp : 定义应用程序的入口点。

#include "rttiMFC.h"
MyApp m_objApp;

/*
	#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL, NULL)
*/

IMPLEMENT_DYNAMIC(MyApp, CWinApp);

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
	int i = IsKindOf(RUNTIME_CLASS(CWinApp));

	m_pMainWnd = new MainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

MainWindow::MainWindow()
{
	// RECT rect = { 500, 400, 800, 700 };
	Create(NULL, L"HelloMFC");
}

IMPLEMENT_DYNCREATE(MainWindow, CFrameWnd);