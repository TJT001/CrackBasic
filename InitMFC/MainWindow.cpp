#include "MainWindow.h"

CMainWindow::CMainWindow()
{
	std::cout << "CMainWindow ���캯��" << std::endl;
	Create();
}


CMainWindow::~CMainWindow()
{
	std::cout << "CMainWindow ��������" << std::endl;
}

void CMainWindow::Create()
{
	std::cout << "CMainWindow Create" << std::endl;
}
