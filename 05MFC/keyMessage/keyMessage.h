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
	BOOL StartHook();

	
	afx_msg void  OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnMyMessage(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
