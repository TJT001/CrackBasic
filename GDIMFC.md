[toc]

# MFC之GDI基础

## GDI设备接口和类

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

## GDI坐标系和空间

* 页面空间和设备空间（逻辑坐标与设备坐标）以及映射模式

**映射模式**是设备描述表的属性，用于确定逻辑坐标到设备坐标的转换，传给CDC输出函数的是逻辑坐标值。设备坐标值是指窗口中相应的像素位置。通过调用`CDC::SetMapMod`来修改映射模式。

**坐标空间**Windows下的程序运用坐标空间和转换来对图形输出进行缩放、旋转、平移、斜切和反射。坐标空间是一个平面的空间，通过使用两个互相垂直并且长度相等的轴来定位二维图像

<center>逻辑坐标 ==》 设备空间 ==》 物理设备</center>
```CPP
#define MM_TEXT             1 
#define MM_LOMETRIC         2
#define MM_HIMETRIC         3
#define MM_LOENGLISH        4
#define MM_HIENGLISH        5
#define MM_TWIPS            6
#define MM_ISOTROPIC        7
#define MM_ANISOTROPIC      8

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	// 设置映射模式
	dc.SetMapMode(MM_ANISOTROPIC);

	dc.SetWindowExt(500, 500);
	dc.SetViewportExt(rect.Width(), rect.Height());
	dc.Ellipse(0, 0, 500, 500);
}
```

* 窗口和视口对应的原点和范围

**页面空间**到**设备空间**的转换是根据映射方式来确定绘图操作的单位大小的一种量度的转换，映射方式主要是确定如何将页面空间的一个坐标点（逻辑）转换到设备空间的一个设备坐标点。

映射方式是一种几乎影响整个客户区域绘图的设备环境属性

另外四种客户环境属性：

1. 窗口原点  `SetWindowOrg()`
2. 视口远点  `SetViewportOrg()`
3. 窗口范围  `SetWindowExt()`
4. 视口范围  `SetViewportExt()`

```cpp
void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	// 设置映射模式
	/*dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(500, 500);
	dc.SetViewportExt(rect.Width(), rect.Height());*/

	//设置原点
	// dc.SetWindowOrg(100, 100);
	// 更改视口原点
	dc.SetViewportExt(100, 100);
	dc.Ellipse(100, 100, 500, 500);
}
```



* 设备空间的三大坐标系
  1. 客户区域坐标
  2. 屏幕坐标
  3. 窗口坐标
* 思考：画一个尺子

```cpp
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
```



## GDI绘图

```cpp
void CMainWindow::OnPaint()
{
	CPaintDC dc(this);

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
```

# 鼠标消息

* 客户区消息

* 非客户区消息

# 键盘消息

* `Windows`键盘消息

​        Windows通过给拥有输入焦点的窗口发送WM_KEYDOWN和WM_KEYUP消息来报靠按键被按下和抬起的消息，除了ALT和F10以外的所有键都产生按下和抬起的消息，ALT和F10是系统健，对Windows有特殊的意义。

函数原型：

```cpp
afx_msg void OnKeyDown(
    UINT nChar,
    UINT nRepCnt,
    UINT nFlags);
/*
nChar
指定给定键的虚拟键代码。 有关标准虚拟键代码的列表，请参阅 Winuser.h
nRepCnt
重复计数（用户按住该键时，重复击键的次数）。
nFlags
指定扫描代码、键转换代码、上一个密钥状态和上下文代码，如下面的列表所示：
值	描述
0-7	扫描代码（与 OEM 相关的值）。
8	扩展键，如数字键盘上的函数键或键（如果它是扩展键，则为1）。
9-10	未使用。
11-12	由 Windows 在内部使用。
13	上下文代码（如果按下了键，则为 1; 否则为0）。
14	上一个键状态（如果键在调用之前关闭，则为 1; 如果键已启动，则为0）。
15	转换状态（如果正在释放密钥，则为 1; 如果按下该键，则为0）。
对于 WM_KEYDOWN 消息，键转换位（位15）为0，上下文代码位（第13）为0。
*/

```

* 安装一个拦截键盘消息的钩子

```cpp
HHOOK g_Hook;
HWND g_Wnd;

// 回调函数
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, // hook code
	WPARAM wParam,  // message identifier
	LPARAM lParam)  // meaage data
{
	if (wParam == WM_KEYDOWN)
	{
		MessageBox(NULL, L"KEYDOWN", L"提示",MB_OK);
	}
	return CallNextHookEx(g_Hook, nCode, wParam, lParam);
}


BOOL StartHook(HWND hwnd)
{
	if (hwnd == NULL)
		return false;
	g_Wnd = hwnd;
	g_Hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandleW(L"MFCKeyHOOKDll.dll"), 0);
	if (g_Hook)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
```

