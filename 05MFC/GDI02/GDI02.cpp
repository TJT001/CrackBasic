
#include "GDI02.h"

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

END_MESSAGE_MAP()


CMainWindow::CMainWindow()
{
	RECT rect = { 0, 0, 1500, 1500 };
	Create(NULL, L"GDI基础02", WS_OVERLAPPEDWINDOW, rect);
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	// 设置映射模式
	dc.SetMapMode(MM_LOMETRIC);
	// 设备坐标转为逻辑坐标
	dc.DPtoLP(&point);

	// 逻辑转设备
	// dc.LPtoDP(&point);
	dc.Rectangle(point.x, point.y, point.x + 100, point.y - 100);

}

void CMainWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	
}

//void CMainWindow::OnPaint()
//{
//	CPaintDC dc(this);
//	CRect rect;
//	GetClientRect(&rect);
//
//	// 设置映射模式
//	/*dc.SetMapMode(MM_ANISOTROPIC);
//	dc.SetWindowExt(500, 500);
//	dc.SetViewportExt(rect.Width(), rect.Height());*/
//
//	//设置原点
//	// dc.SetWindowOrg(100, 100);
//	// 更改视口原点
//	dc.SetViewportExt(100, 100);
//	dc.Ellipse(100, 100, 500, 500);
//}

// 画一把尺子
void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	
	// 设置为英寸映射
	dc.SetMapMode(MM_LOENGLISH);
	dc.SetTextAlign(TA_CENTER | TA_BOTTOM); //对齐的点在底部边界中间
	dc.SetBkMode(TRANSPARENT);

	// 画尺子主题
	CRect rect(100,-100,1500,-250); // 长1200 宽150
	CBrush brush(RGB(255,255,0));
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(rect);
	dc.SelectObject(pOldBrush);

	// 画刻度
	for (int i = 125; i < 1500; i += 25){
		dc.MoveTo(i, -250);
		dc.LineTo(i, -230);
	}
	for (int i = 150; i < 1500; i += 50){
		dc.MoveTo(i, -250);
		dc.LineTo(i, -220);
	}
	for (int i = 200; i < 1500; i += 100) {
		dc.MoveTo(i, -250);
		dc.LineTo(i, -220);

		CString string;
		string.Format(_T("%d"), (i / 100) - 1);
		dc.TextOut(i, -220, string);
	}
}