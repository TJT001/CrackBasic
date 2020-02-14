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
	CPoint m_ptForm;
	CPoint m_ptIo;

public:
	CMainWindow();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT hHitTest, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
