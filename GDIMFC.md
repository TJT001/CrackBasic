[toc]



# MFC之GDI基础

* GDI图形设备接口

Windows中负责图形输出的是`Graphics Device Interface`(图形设备接口)，他为应用程序提供了可调用的多种服务，这些服务一起构成了强大和通用的图形编程语言。

* DC设备描述符

当Windows程序在屏幕、打印机或者其它输出输出设备上画图时，它并不将像素直接输出到设备上，而是将图形绘制设备描述符表DC表示的逻辑意义上的显示平面上去，他是Windows中的一种数据结构，包含了GDI需要的所有显示平面情况的描述。

* 常用的三个DC类
  * CPaintDC用于在窗口客户区画图（仅限于OnPaint处理程序）
  * CClientDC用于在窗口客户区画图（处理OnPaint外的任何处理程序）
  * CWindowDC用于在窗口内任意地方画图（包括非客户区）

```CPP
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
```

