#include "MY.h"

CMyWinApp theApp;

BOOL CMyWinApp::InitInstance()
{
	cout << "CMyWinApp::InitInstance" << endl;
	m_pMainWnd = new CFrameWnd;
	return TRUE;
}

// main����
int main()
{
	CWinApp* pApp = AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();

	return 0;
}


