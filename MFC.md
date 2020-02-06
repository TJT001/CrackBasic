[toc]

# 手动创建第一个MFC程序

* 基于MFC的窗口必须也只能有一个CWinApp派生的对象

* 必须覆盖CWinApp的虚函数InitInstance在里面创建窗口并把窗口对象保存在它的成员变量m_pMainWnd中

```cpp
class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow :public CFrameWnd
{
public:
	CMainWindow();
};
```



* 创建窗口是通过派生CFrameWind对象，在它的构造函数里面调用成员函数create

```cpp
OOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CMainWindow::CMainWindow()
{
	Create(NULL, L"HelloMFC");
}
```



## 注意

* 创建Win32应用程序
* 包含MFC运行库

![image-20200205215903446](../../学习笔记/assets/image-20200205215903446.png)

* 包含头文件`afxwin.h`

# MFC的初始化

