#include "MainWindow.h"

CMainWindow::CMainWindow()
{
	std::cout << "CMainWindow 构造函数" << std::endl;
	Create();
}


CMainWindow::~CMainWindow()
{
	std::cout << "CMainWindow 析构函数" << std::endl;
}

void CMainWindow::Create()
{
	std::cout << "CMainWindow Create" << std::endl;
}
