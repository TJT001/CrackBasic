#include "MyApp.h"
#include "MainWindow.h"

CMyApp::CMyApp()
{
	std::cout << "CMyApp ���캯��" << std::endl;
	m_CurrentApp = this;
}

CMyApp::~CMyApp()
{
	std::cout << "CMyApp ��������" << std::endl;
}

bool CMyApp::Instance()
{
	std::cout << "CMyApp Instance" << std::endl;
	m_pMainWnd = new CMainWindow;
	return false;
}
