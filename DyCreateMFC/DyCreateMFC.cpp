#include "DyCreateMFC.h"

CMyApp m_objApp;
const CRuntimeClass CMyApp::classMyApp =
{
		"MyApp", sizeof(class CMyApp), 0xFFFF, NULL,((CRuntimeClass*)(&CWinApp::classCWinApp)), NULL, NULL
};
CRuntimeClass* CMyApp::GetRuntimeClass() const
{
	return (CRuntimeClass*)(&CWinApp::classCWinApp);
}

CMyApp::CMyApp()
{
	std::cout << "MyApp 构造函数" << std::endl;
}

CMyApp::~CMyApp()
{
	std::cout << "MyApp 析构函数" << std::endl;
}




BOOL CMyApp::InitInstance()
{
	// 运行是类型识别 结构体RUNTIME_CLASS
	/*
	#define RUNTIME_CLASS(class_name) _RUNTIME_CLASS(class_name)
	*/
	int i = IsKindOf((CRuntimeClass*)(&CWinApp::classCWinApp));
	
	// m_pMainWnd = new CMainWindow;
	m_pMainWnd = (CMainWindow*)RUNTIME_CLASS(CMainWindow)->CreateObject();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


// IMPLEMENT_DYNAMIC(CMainWindow, CFrameWnd)

// #define IMPLEMENT_RUNTIMECLASS(CMainWindow, base_class_name, wSchema, pfnNew, class_init)
const CRuntimeClass CMainWindow::classCMainWindow = {
		"CMainWindow", sizeof(class CMainWindow), 0xFFFF, CMainWindow::CreateObject,
			RUNTIME_CLASS(CFrameWnd), NULL, NULL };
CRuntimeClass* CMainWindow::GetRuntimeClass() const
{
	return RUNTIME_CLASS(CMainWindow);
}

// IMPLEMENT_DYNCREATE(CMainWindow, CFrameWnd)
/*
#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CObject* PASCAL class_name::CreateObject() \
		{ return new class_name; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject, NULL)
*/

// #define IMPLEMENT_DYNCREATE(class_name, base_class_name)
	
CObject* PASCAL CMainWindow::CreateObject()
		{ 
		return new CMainWindow;
	}
//IMPLEMENT_RUNTIMECLASS(CMainWindow, CFrameWnd, 0xFFFF,
//		CMainWindow::CreateObject, NULL)

/*
#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew, class_init) \
	AFX_COMDAT const CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			RUNTIME_CLASS(base_class_name), NULL, class_init }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return RUNTIME_CLASS(class_name); }
*/
// #define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew, class_init) 

CMainWindow::CMainWindow()
{
	// RECT rect = { 500, 400, 800, 700 };
	Create(NULL, L"HelloMFC");
}