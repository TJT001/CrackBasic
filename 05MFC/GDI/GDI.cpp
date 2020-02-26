// GDI.cpp : 定义应用程序的入口点。
//


#include "GDI.h"
CMyApp m_objApp;


BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


IMPLEMENT_DYNCREATE(CMainWindow, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()

END_MESSAGE_MAP()


CMainWindow::CMainWindow() 
{
	RECT rect = { 50, 50, 800, 700 };
	Create(NULL, L"GDI基础", WS_OVERLAPPEDWINDOW, rect);
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*
	HDC dc;
	dc = ::GetDC(m_hWnd);
	::Ellipse(dc, 0, 0, 150, 150);
	::ReleaseDC(m_hWnd,dc);
	*/
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* oldPen = dc.SelectObject(&pen);
	CBrush brush(RGB(255, 180, 0));
	dc.SelectObject(&brush);
	// CWindowDC dc(NULL);
	// dc.Ellipse(0, 0, 150, 150);
	dc.Rectangle(200, 100, 500, 500);

}

void CMainWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	// 客户区画一段文字 文字颜色蓝色
	CWindowDC dc(NULL);
	dc.SetTextColor(RGB(0, 0, 255));
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(L"Hello GDI", CRect(200, 300, 400, 400), DT_SINGLELINE);
}

void CMainWindow::OnPaint()
{
	/*
	HDC dc;
	PAINTSTRUCT ps;
	dc = ::GetDC(m_hWnd);
	::BeginPaint(m_hWnd, &ps);
	::DrawText(dc, L"Hello GDI", strlen("Hello GDI"), CRect(200, 200, 300, 300), DT_SINGLELINE);
	::EndPaint(m_hWnd, &ps);
	*/

	CPaintDC dc(this);
	/*dc.SetTextColor(RGB(255, 0, 0));
	dc.SetBkColor(RGB(255, 180, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(L"Hello GDI", CRect(200, 200, 300, 300), DT_SINGLELINE);*/

	// 画一个圆 画笔红色 画刷黄色
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* oldPen = dc.SelectObject(&pen);
	CBrush brush(RGB(255, 180, 0));
	dc.SelectObject(&brush);
	dc.Ellipse(100, 100, 400, 400);
}
