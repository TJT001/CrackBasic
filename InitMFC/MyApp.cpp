#include "MyApp.h"
#include "MainWindow.h"

CMyApp::CMyApp()
{
	std::cout << "CMyApp 构造函数" << std::endl;
	m_CurrentApp = this;
}

CMyApp::~CMyApp()
{
	std::cout << "CMyApp 析构函数" << std::endl;
}

bool CMyApp::Instance()
{
	std::cout << "CMyApp Instance" << std::endl;
	m_pMainWnd = new CMainWindow;
	return false;
}
