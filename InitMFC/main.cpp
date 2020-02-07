// #include <stdlib.h>
#include "MyApp.h"

CMyApp m_objApp;

// 模拟获取这个对象
CMyApp* afxGetApp()
{
	return m_objApp.m_CurrentApp;
}

int main()
{
	std::cout << "WinMain" << std::endl;
	
	CMyApp* pApp;
	pApp = afxGetApp();
	pApp->Instance();
	return 0;
	
}