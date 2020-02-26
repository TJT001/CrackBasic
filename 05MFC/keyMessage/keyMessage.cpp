
#include "keyMessage.h"
#define MWM_MYMSG_1 WM_USER+1

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
	ON_WM_CHAR()
	ON_MESSAGE(MWM_MYMSG_1, OnMyMessage)
END_MESSAGE_MAP()


CMainWindow::CMainWindow()
{
	RECT rect = { 50, 50, 800, 700 };
	Create(NULL, L"GDI基础03", WS_OVERLAPPEDWINDOW, rect);
}

void CMainWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/*CString str;
	if (nChar = VK_F1)
	{
		str.Format(L"OnKeyDown: %c", nChar);
		OutputDebugString(str);
	}*/
	if (nChar == VK_F2)
	{
		if (StartHook())
		{
			SetWindowText(L"调用成功");
		}
		else
		{
			SetWindowText(L"调用失败");
		}
	}
}

void CMainWindow::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

LRESULT CMainWindow::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_KEYDOWN)
	{
		MessageBox(L"keydown", L"提示", MB_OK);
	}

	return 0;
}

BOOL CMainWindow::StartHook()
{
	// 定义一个函数指针
	typedef BOOL (*STARTHOOK)(HWND hwnd);
	STARTHOOK stFun;
	stFun = (STARTHOOK)GetProcAddress(LoadLibrary(L"MFCKeyHOOKDll.dll"), "StartHook");
	return stFun(m_hWnd);
}

