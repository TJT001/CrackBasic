#pragma once

#include <iostream>
#include <afxwin.h>

#define LINESIZE 8

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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();

	// 定义变量
protected:
	int m_cellWidth;   // 格子宽度
	int m_cellHeight;  // 格子高度
	int m_ribbonWidth;
	int m_viewWidth;
	int m_viewHeight;
	int m_hscrollPos;
	int m_vscrollPos;
	int m_hpageSize;
	int m_vpageSize;
	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
