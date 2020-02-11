#pragma once

#include <iostream>
#include <afxwin.h>

class CMyApp : public CWinApp
{
public:
	CMyApp();
	~CMyApp();

	static const CRuntimeClass classMyApp;
	virtual CRuntimeClass* GetRuntimeClass() const;

public:
	virtual BOOL InitInstance();
};


class CMainWindow :public CFrameWnd
{

public:

	// 运行时类型识别
	// DECLARE_DYNAMIC(CMainWindow);

	// 动态创建
	// DECLARE_DYNCREATE(CMainWindow)

	static const CRuntimeClass classCMainWindow;
	virtual CRuntimeClass* GetRuntimeClass() const;
	// 增加一个成员函数
	static CObject* PASCAL CreateObject();
	CMainWindow();

	
public:
	//添加左键消息处理函数
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

	// 消息映射机制=》声明
	// DECLARE_MESSAGE_MAP()

// 展开
//#define DECLARE_MESSAGE_MAP() 
protected: 
	static const AFX_MSGMAP* PASCAL GetThisMessageMap();
	virtual const AFX_MSGMAP* GetMessageMap() const;
};


class CNewWnd :
	public CMainWindow
{
public:
	CNewWnd();
};