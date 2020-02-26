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

	// ����ʱ����ʶ��
	// DECLARE_DYNAMIC(CMainWindow);

	// ��̬����
	// DECLARE_DYNCREATE(CMainWindow)

	static const CRuntimeClass classCMainWindow;
	virtual CRuntimeClass* GetRuntimeClass() const;
	// ����һ����Ա����
	static CObject* PASCAL CreateObject();
	CMainWindow();

	
public:
	//��������Ϣ������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

	// ��Ϣӳ�����=������
	// DECLARE_MESSAGE_MAP()

// չ��
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