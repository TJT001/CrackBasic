#pragma once
#include <iostream>
#include <afxwin.h>


class CMyApp :
	public CWinApp
{
public:
	virtual BOOL InitInstance();
};


class CMainWindow :
	public CFrameWnd
{
	DECLARE_DYNCREATE(CMainWindow)
public:
	CMainWindow();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

};