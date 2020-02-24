
// listCtrlDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "listCtrl.h"
#include "listCtrlDlg.h"
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


// ClistCtrlDlg 对话框



ClistCtrlDlg::ClistCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LISTCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClistCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(ClistCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &ClistCtrlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ClistCtrlDlg 消息处理程序

BOOL ClistCtrlDlg::OnInitDialog()
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

	// 设置自定义的风格
	initExtendListCtrlStyle();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ClistCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void ClistCtrlDlg::OnPaint()
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
HCURSOR ClistCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

VOID ClistCtrlDlg::initExtendListCtrlStyle()
{
	// 设置VListCtrl扩展风格
	int nStyle = m_listCtrl.GetExtendedStyle();
	nStyle |= LVS_EX_FULLROWSELECT; // 选中项高亮
	//nStyle |= LVS_EX_GRIDLINES;     // 网格线
	//nStyle |= LVS_EX_CHECKBOXES;  // 带复选框

	// 设置风格
	m_listCtrl.SetExtendedStyle(nStyle);

	// 添加图标


	/*m_listCtrl.SetColumnWidth(0, 300);
	m_listCtrl.SetColumnWidth(1, 400);
	m_listCtrl.SetColumnWidth(2, 500);*/
	m_listCtrl.InsertColumn(0, _T("地址"),LVCFMT_CENTER,90);
	m_listCtrl.InsertColumn(1, _T("汇编"), LVCFMT_CENTER, 120);
	m_listCtrl.InsertColumn(2, _T("注释"), LVCFMT_CENTER, 70);

	// 添加数据
	int nPos = m_listCtrl.InsertItem(0,_T("第一行数据"));
	m_listCtrl.SetItemText(nPos, 1, _T("第一行第二列数据"));
	m_listCtrl.SetItemText(nPos, 2, _T("第一行第三列数据"));
	int nPos1 = m_listCtrl.InsertItem(1, _T("第二行"));
	m_listCtrl.SetItemText(nPos1, 1, _T("第二行第二列数据"));
	m_listCtrl.SetItemText(nPos1, 2, _T("第二行第三列数据"));
	m_listCtrl.InsertItem(2, _T("第三行"));

	return VOID();
}



void ClistCtrlDlg::OnBnClickedButton1()
{
	// 读取列中的数据 1行2列
	//CString str = m_listCtrl.GetItemText(0, 1);

	// 读取任意一行
	CString str;
	for (int i = 0; i < m_listCtrl.GetItemCount(); i++)
	{
		if (m_listCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			str.Format(_T("选中了第：%d行"), i+1);
			AfxMessageBox(str);
		}
	}
}
