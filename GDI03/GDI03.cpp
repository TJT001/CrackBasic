
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

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()

END_MESSAGE_MAP()


CMainWindow::CMainWindow()
{
	RECT rect = { 50, 50, 800, 700 };
	Create(NULL, L"GDI基础03", WS_OVERLAPPEDWINDOW, rect);
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
	CPaintDC dc(this);
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

}

// 作业： 绘制一个excel表格