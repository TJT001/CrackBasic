
// treeListDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "treeList.h"
#include "treeListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtreeListDlg 对话框



CtreeListDlg::CtreeListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TREELIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtreeListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeList);
}

BEGIN_MESSAGE_MAP(CtreeListDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtreeListDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtreeListDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CtreeListDlg 消息处理程序

BOOL CtreeListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtreeListDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtreeListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtreeListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtreeListDlg::OnBnClickedButton1()
{
	HTREEITEM hRootitem = m_treeList.InsertItem(L"父节点0");
	m_treeList.InsertItem(L"父节点1");
	m_treeList.InsertItem(L"父节点2");
	// 添加子节点
	m_treeList.InsertItem(L"这是子节点0", hRootitem, TVI_SORT);
	m_treeList.InsertItem(L"这是子节点1", hRootitem, TVI_SORT);
	m_treeList.InsertItem(L"这是子节点2", hRootitem, TVI_SORT);
	m_treeList.InsertItem(L"这是子节点3", hRootitem, TVI_SORT);
	HTREEITEM hChilditem = m_treeList.InsertItem(L"这是子节点4", hRootitem, TVI_SORT);
	m_treeList.InsertItem(L"这是子节点4-0", hChilditem,TVI_SORT);
	m_treeList.InsertItem(L"这是子节点4-1", hChilditem, TVI_SORT);
	m_treeList.InsertItem(L"这是子节点4-2", hChilditem, TVI_SORT);
}


void CtreeListDlg::OnBnClickedButton2()
{
	// 获取节点 默认获取最上层的父节点
	HTREEITEM hRootitem = m_treeList.GetRootItem();
	CString strName = m_treeList.GetItemText(hRootitem);

	// 获取同级别的下一个节点
	HTREEITEM hNextRootItem = m_treeList.GetNextSiblingItem(hRootitem);
	//m_treeList.GetNextItem(hRootitem, TVGN_NEXT);
	CString strNextRootName = m_treeList.GetItemText(hNextRootItem);

	// 获取子节点 0-0
	HTREEITEM hChildItem = m_treeList.GetChildItem(hRootitem);

	CString strChildName = m_treeList.GetItemText(hChildItem);
	AfxMessageBox(strNextRootName);
}
