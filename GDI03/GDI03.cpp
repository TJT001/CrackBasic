
#include "GDI03.h"

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

	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()

	ON_WM_HSCROLL()
	ON_WM_VSCROLL()

	ON_WM_SIZE()
END_MESSAGE_MAP()


CMainWindow::CMainWindow()
	:m_cellWidth(0),
	 m_cellHeight(0),
	 m_ribbonWidth(0),
	 m_viewWidth(0),
	 m_viewHeight(0)
{
	/*RECT rect = { 50, 50, 800, 700 };
	Create(NULL, L"GDI基础03", WS_OVERLAPPEDWINDOW, rect);*/
	this->Create(NULL, L"Excel", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL);
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CFrameWnd::OnCreate(lpCreateStruct) == -1)
	return -1;

	CClientDC dc(this);
	m_cellWidth = dc.GetDeviceCaps(LOGPIXELSX);
	m_cellHeight = dc.GetDeviceCaps(LOGPIXELSY);
	m_ribbonWidth = m_cellWidth / 2;
	m_viewWidth = (26 * m_cellWidth) + m_ribbonWidth;
	m_viewHeight = m_cellHeight * 100;

	m_hscrollPos = m_vscrollPos;
	return 0;
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	

}

void CMainWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	


}

void CMainWindow::OnPaint()
{

	/*CPaintDC dc(this);
	CPen pen;
	CFont font;

	CRect rect;
	dc.SetBkMode(TRANSPARENT);
	GetClientRect(&rect);
	font.CreatePointFont(600, L"Calibri");
	dc.SelectObject(&font);

	rect.OffsetRect(15, 15);
	dc.SetTextColor(RGB(192, 190, 192));
	dc.DrawText("MyFont", &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
*/
	/*CPaintDC dc(this);
	CPen pen;
	CFont font;

	font.CreatePointFont(300, L"Calibri");
	dc.SelectObject(&pen);
	pen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	CPen* oldPen;
	oldPen = dc.SelectObject(&pen);


	// 画线前设定当前位置
	dc.MoveTo(10, 10);

	// 当前位置画一条线到指定位置
	dc.LineTo(30, 10);
	dc.LineTo(30, 30);

	// 定义一个数组 
	POINT pt[5] = { 40,40,100,40,100,100,40,100,40,40 };

	// 从当前位置将一系列的点用线段连接起来
	dc.Polyline(pt, 5);

	POINT pt2[] = { 100,40,100,100,40,100,40,40 };
	dc.MoveTo(40, 40);
	dc.Polyline(pt2, 4);

	//画图形
	dc.Ellipse(CRect(140, 130, 160, 160));

	CBrush brush;

	//亮灰色的画刷
	brush.CreateStockObject(LTGRAY_BRUSH);
	CRect rect(10, 130, 110, 160);
	dc.Rectangle(rect);
	dc.FillRect(&rect, &brush);
	rect.top++;
	rect.left++;
	
	// 画3D效果
	dc.Draw3dRect(&rect, RGB(255, 255, 255), RGB(128, 126, 128));
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText("Caption", &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	*/

	CPaintDC dc(this);
	dc.SetWindowOrg(m_hscrollPos, m_vscrollPos);
	CPen pen(PS_SOLID, 0, RGB(192, 192, 192));
	CPen *pOldpen = dc.SelectObject(&pen);

	for (int i = 0; i < 99; i++){

		int y = (i * m_cellHeight) + m_cellHeight;
		dc.MoveTo(0, y);
		dc.LineTo(m_viewWidth, y);
	}

	for (int i = 0; i < 26; i++){
		int x = (i * m_cellWidth) + m_ribbonWidth;
		dc.MoveTo(x, 0);
		dc.LineTo(x, m_viewHeight);
	}

	dc.SelectObject(pOldpen);

	CBrush brush;
	brush.CreateStockObject(LTGRAY_BRUSH);


	CRect rcTop(0, 0, m_viewWidth, m_cellHeight);
	dc.FillRect(rcTop, &brush);
	CRect rcLeft(0, 0, m_ribbonWidth, m_viewHeight);

	dc.FillRect(rcLeft, &brush);

	dc.MoveTo(0, m_cellHeight);
	dc.LineTo(m_viewWidth, m_cellHeight);
	dc.MoveTo(m_ribbonWidth, 0);
	dc.LineTo(m_ribbonWidth, m_viewHeight);

	dc.SetBkMode(TRANSPARENT);



	for (int i = 0; i < 99; i++){

		int y = (i * m_cellHeight) + m_cellHeight;
		dc.MoveTo(0, y);
		dc.LineTo(m_ribbonWidth, y);

		CString string;
		string.Format(_T("%d"), i + 1);

		CRect rect(0, y, m_ribbonWidth, y + m_cellHeight);

		dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		rect.top++;
		dc.Draw3dRect(rect, RGB(255, 255, 255), RGB(128, 128, 128));//3D效果
	}



	for (int j = 0; j < 26; j++)

	{

		int x = (j * m_cellWidth) + m_ribbonWidth;
		dc.MoveTo(x, 0);
		dc.LineTo(x, m_cellHeight);


		CString string;
		string.Format(_T("%c"), j + 'A');


		CRect rect(x, 0, x + m_cellWidth, m_cellHeight);
		dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);



		rect.left++;
		dc.Draw3dRect(rect, RGB(255, 255, 255), RGB(128, 128, 128));
	}

}

// 作业： 绘制一个excel表格

void CMainWindow::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nDelta = 0;

	switch (nSBCode)
	{
	case SB_LINELEFT:

		nDelta = -LINESIZE;
		break;

	case SB_LINERIGHT:

		nDelta = LINESIZE;
		break;

	case SB_PAGELEFT:

		nDelta = -m_hpageSize;
		break;
	case SB_PAGERIGHT:

		nDelta = m_hpageSize;
		break;
	case SB_THUMBTRACK:

		nDelta = (int)nPos - m_hscrollPos;
		break;
	default:
		break;
	}

	if (nDelta != 0)
	{
		m_hscrollPos += nDelta;
		SetScrollPos(SB_HORZ, m_hscrollPos, TRUE);
		ScrollWindow(-nDelta, 0);

	}
	CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMainWindow::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nDelta = 0;

	switch (nSBCode)
	{
	case SB_LINEDOWN:

		nDelta = LINESIZE;
		break;

	case SB_LINEUP:

		nDelta = -LINESIZE;
		break;

	case SB_THUMBTRACK:

		nDelta = (int)nPos - m_hscrollPos;
		break;

	case SB_PAGEUP:
		nDelta = -m_vpageSize;
		break;

	case SB_PAGEDOWN:

		nDelta = m_vpageSize;
		break;
	default:
		break;

	}

	if (nDelta != 0)
	{

		m_vscrollPos += nDelta;
		SetScrollPos(SB_VERT, m_vscrollPos, TRUE);
		ScrollWindow(0, -nDelta);
	}

	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CMainWindow::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	int nHScrollMax = 0;
	m_hpageSize = 0;


	if (cx < m_viewWidth){

		m_hpageSize = cx;
		nHScrollMax = m_viewWidth - 1;
	}



	SCROLLINFO si;

	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nHScrollMax - 1;
	si.nPos = m_hscrollPos;
	si.nPage = m_hpageSize;


	SetScrollInfo(SB_HORZ, &si, TRUE);

	int nVScrollMax = 0;
	m_vpageSize = 0;


	if (cy < m_viewHeight){

		nVScrollMax = m_viewHeight - 1;
		m_vpageSize = cy;
	}


	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nVScrollMax;
	si.nPos = m_vscrollPos;
	si.nPage = m_vpageSize;


	SetScrollInfo(SB_VERT, &si, TRUE);
}
