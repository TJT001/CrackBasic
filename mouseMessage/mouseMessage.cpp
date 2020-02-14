
#include "mouseMessage.h"

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

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
	// 客户区鼠标消息
	ON_WM_MOUSEMOVE()
	// 非客户区鼠标消息
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONUP()

END_MESSAGE_MAP()


CMainWindow::CMainWindow()
{
	RECT rect = { 50, 50, 800, 700 };
	Create(NULL, L"GDI基础03", WS_OVERLAPPEDWINDOW, rect);
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ptForm = point;
	SetCapture();
}

void CMainWindow::OnRButtonDown(UINT nFlags, CPoint point)
{



}

void CMainWindow::OnPaint()
{


}

void CMainWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	/*CString str;
	if (nFlags&MK_RBUTTON)
	{
		str.Format(L"OnLButtonDown:%d,%d", point.x, point.y);
		SetWindowText(str);
	}*/


}

void CMainWindow::OnNcLButtonDown(UINT hHitTest, CPoint point)
{
	CString str;
	/*f (hHitTest == HTSYSMENU)
	{
		str.Format(L"OnLButtonDown:%d,%d", point.x, point.y);
		SetWindowText(str);
	}*/
	
	//CFrameWnd::OnNcLButtonDown(hHitTest, point);
}

LRESULT CMainWindow::OnNcHitTest(CPoint point)
{
	UINT nHitRet;

	// 点击窗口
	nHitRet = CFrameWnd::OnNcHitTest(point);
	if (nHitRet == HTCAPTION)
	{
		// 点击标题
		nHitRet = HTCLIENT;
	}

	return nHitRet;
}

void CMainWindow::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	dc.MoveTo(m_ptForm);
	dc.LineTo(point);
	if (GetCapture() == this)
		ReleaseCapture();
	
}

// 作业：按下鼠标左键画直线
// Ctrl + 左键画矩形
// 右键随意画图