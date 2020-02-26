#pragma once
#include "CmdTarget.h"
#include "Wnd.h"
class CWinThread :
	public CCmdTarget
{
public:

	CWinThread();
	~CWinThread();

	virtual bool Instance() = 0;
public:
	CWnd* m_pMainWnd;
};

