#include "msgMapMFC.h"

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

// IMPLEMENT_DYNAMIC(CMainWindow, CFrameWnd)

// #define IMPLEMENT_RUNTIMECLASS(CMainWindow, base_class_name, wSchema, pfnNew, class_init)

const CRuntimeClass CMainWindow::classCMainWindow = {
		"CMainWindow", sizeof(class CMainWindow), 0xFFFF, 
		CMainWindow::CreateObject,RUNTIME_CLASS(CFrameWnd), NULL, NULL };

CRuntimeClass* CMainWindow::GetRuntimeClass() const
{
	return RUNTIME_CLASS(CMainWindow);
}

CObject* PASCAL CMainWindow::CreateObject()
{
	return new CMainWindow;
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

// 添加消息
// BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)

// 展开 
// #define BEGIN_MESSAGE_MAP(theClass, baseClass)
//	PTM_WARNING_DISABLE
const AFX_MSGMAP* CMainWindow::GetMessageMap() const
{ 
	return GetThisMessageMap(); 
} 

const AFX_MSGMAP* PASCAL CMainWindow::GetThisMessageMap()
{ 
		typedef CMainWindow ThisClass;
		typedef CFrameWnd TheBaseClass;
		__pragma(warning(push))							   
		__pragma(warning(disable: 4640)) /* message maps can only be called by single threaded message pump */
		static const AFX_MSGMAP_ENTRY _messageEntries[] = 
{

//例：添加一个鼠标左键消息
// ON_WM_LBUTTONDOWN()
// 展开ON_WM_LBUTTONDOWN()
{WM_LBUTTONDOWN, 0, 0, 0, AfxSig_vwp,
	  (AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)> (&ThisClass::OnLButtonDown))},

//绘制一行文字
// ON_WM_PAINT()
// 展开ON_WM_PAINT()
	{WM_PAINT, 0, 0, 0, AfxSig_vv,
	(AFX_PMSG)(AFX_PMSGW)
	(static_cast<void (AFX_MSG_CALL CWnd::*)(void)> (&ThisClass::OnPaint)) },

// END_MESSAGE_MAP()

// 展开END_MESSAGE_MAP()
// #define END_MESSAGE_MAP()
		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 }
};
		__pragma(warning(pop))
		static const AFX_MSGMAP messageMap =
		{ 
			&CFrameWnd::GetThisMessageMap, &_messageEntries[0] 
		};
		return &messageMap;
}				
// PTM_WARNING_RESTORE


CMainWindow::CMainWindow()
{
	// RECT rect = { 500, 400, 800, 700 };
	Create(NULL, L"msgMapMFC");
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	MessageBox(L"OnLButtonDown");
	//AfxMessageBox(L"OnLButtonDown");
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	dc.DrawText("onPaint", CRect(100, 100, 200, 200), DT_SINGLELINE);
}

// 作业点击左键创建一个CNewWindow
// CNewWindow之创建一次，点击左键弹出MessageBox
CNewWnd::CNewWnd()
{

}
