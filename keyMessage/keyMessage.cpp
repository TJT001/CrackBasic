
#include "keyMessage.h"

CMyApp m_objApp;


BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


IMPLEMENT_DYNCREATE(CMainWindow, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_KEYDOWN()
	
END_MESSAGE_MAP()


CMainWindow::CMainWindow()
{
	RECT rect = { 50, 50, 800, 700 };
	Create(NULL, L"GDI基础03", WS_OVERLAPPEDWINDOW, rect);
}

void CMainWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString str;
	if (nChar = VK_F1)
	{
		str.Format(L"OnKeyDown: %c", nChar);
		OutputDebugString(str);
	}

}



