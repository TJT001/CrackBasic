// #include "..\InitMFC\MyWinApp.h"
// HelloMFC.cpp : 定义应用程序的入口点。

#include "HelloMFC.h"

CMyApp m_objApp;

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CMainWindow::CMainWindow()
{
	RECT rect = { 500, 400, 800, 700 };
	Create(NULL, L"HelloMFC",WS_OVERLAPPEDWINDOW,rect);
}


