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

![image-20200205215839263](C:/Users/123/AppData/Roaming/Typora/draftsRecover/2020-2-11 MFC 114204.assets/image-20200205215839263.png)

* 包含头文件`afxwin.h`

# MFC的初始化过程

## CWinApp的层次结构

* 全局对象或者全局变量会在main()函数之前执行

```cpp
CObject
    |__CCmdTarget
           |__CWndApp
                 |__CWinApp
                     
```

## CFrameWnd的层次结构

*  CFrameWnd提供Windows单文档重叠或是弹出式框架窗口，以及管理窗口的成员

```cpp
CObject
    |__CCmdTarget
           |__CWndApp
                 |__CFrameWnd
```

# MFC的运行时类型识别(RTTI)

* RTTI(Runtime Type Information)

运行时类型信息程序能够使用基类的指针或者引用来检查这些指针或引用所指的对象的实际派生类

* 三个关键的宏

**DECLARE_DYNAMIC**

**IMPLEMENT_DYNAMIC**

**RUNTIMEI_CLASS**

* 一个关键的结构体

```cpp
struct CRuntimeClass
{
// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema; // schema number of the loaded class
	CObject* (PASCAL* m_pfnCreateObject)(); // NULL => abstract class
#ifdef _AFXDLL
	CRuntimeClass* (PASCAL* m_pfnGetBaseClass)();
#else
	CRuntimeClass* m_pBaseClass;
#endif

// Operations
	CObject* CreateObject();
	BOOL IsDerivedFrom(const CRuntimeClass* pBaseClass) const;

	// dynamic name lookup and creation
	static CRuntimeClass* PASCAL FromName(LPCSTR lpszClassName);
	static CRuntimeClass* PASCAL FromName(LPCWSTR lpszClassName);
	static CObject* PASCAL CreateObject(LPCSTR lpszClassName);
	static CObject* PASCAL CreateObject(LPCWSTR lpszClassName);

// Implementation
	void Store(CArchive& ar) const;
	static CRuntimeClass* PASCAL Load(CArchive& ar, UINT* pwSchemaNum);

	// CRuntimeClass objects linked together in simple list
	CRuntimeClass* m_pNextClass;       // linked list of registered classes
	const AFX_CLASSINIT* m_pClassInit;
};
```



# 动态创建

动态创建和C++的new运算符没有区别，但是回避了C++语言中没有如下语句执行的缺点

```cpp
char *className = "MyClass"
Cobject *obj = new className
```

* 两个关键的宏

**DECLARE_DYNCREATE**

**IMPLEMENT_DYNCREATE**

```cpp
#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject* PASCAL CreateObject();
// 相比运行时动态识别多了一个成员函数
CObject* PASCAL CMainWindow::CreateObject()
		{ 
		return new CMainWindow;
	}

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CObject* PASCAL class_name::CreateObject() \
		{ return new class_name; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject, NULL)
```

# 消息映射

​        消息映射是MFC内建的一个消息分派机制，只要利用数个宏以及固定形式的写法，类似于填表格就可以让我们的框架知道一旦消息发生，就该往哪一个类去传递，每一个类只能拥有一个消息映射表格也可以没有

* 三个关键的宏

**DECLARE_MESSAGE_MAP()**

**BEGIN_MESSAGE_MAP()**

**END_MESSAGE_MAP()**

```cpp
// 展开宏
#define DECLARE_MESSAGE_MAP()
protected:
	static const AFX_MSGMAP* PASCAL GetThisMessageMap();
	virtual const AFX_MSGMAP* GetMessageMap() const;

#define BEGIN_MESSAGE_MAP(theClass, baseClass)
	PTM_WARNING_DISABLE
	const AFX_MSGMAP* theClass::GetMessageMap() const
		{ return GetThisMessageMap(); }
	const AFX_MSGMAP* PASCAL theClass::GetThisMessageMap()
	{ 
		typedef theClass ThisClass;						 
		typedef baseClass TheBaseClass;					 
		__pragma(warning(push))						
		__pragma(warning(disable: 4640)) /* message maps can only be called by single threaded message pump */ 
		static const AFX_MSGMAP_ENTRY _messageEntries[] = 
		{
            
#define END_MESSAGE_MAP() 
		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 } 
	}; 
		__pragma(warning(pop))	
		static const AFX_MSGMAP messageMap = 
		{ &TheBaseClass::GetThisMessageMap, &_messageEntries[0] };
        // messageMap保存着父类的消息映射
		return &messageMap;
	}								 
	PTM_WARNING_RESTORE  
```



一个关键的结构体

```cpp
struct AFX_MSGMAP_ENTRY
{
	UINT nMessage;   // windows message
    // Windows消息
	UINT nCode;      // control code or WM_NOTIFY code
    // 对于窗口消息为0，处理命令消息和控件通知的函数使用与此相同的消息映象
	UINT nID;        // control ID (or 0 for windows messages)
    // 命令消息的起始范围
	UINT nLastID;    // used for entries specifying a range of control id's
	// 命令消息ID范围的终点
    UINT_PTR nSig;   // signature type (action) or pointer to message #
	// 消息的动作标识enum AfxmSig里面的成员
    AFX_PMSG pfn;    // routine to call (or special value)
    // 响应消息时应执行的函数
};

```



* 添加消息

```cpp
***.h
    //添加左键消息处理函数
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	// 消息映射机制=》声明
	DECLARE_MESSAGE_MAP()
        
***.cpp
    // 添加消息
BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)

//例：添加一个鼠标左键消息
ON_WM_LBUTTONDOWN()

END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	// RECT rect = { 500, 400, 800, 700 };
	Create(NULL, L"msgMapMFC");
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	AfxMessageBox(L"OnLButtonDown");
}

```

# 命令传递

​       消息会按照规定的线路游走于各个对象之间，知道找到它的消息处理函数，如果找不到，则最终把他交给::DefWindowProc函数处理



# MFC对话框

​        MFC的对话框实际上是一个窗口，它不仅可以接收消息，而且还可以被移动和关闭,还可以在它的客户区域进行绘图，我们可以把它看成是一个大的容器，在上面可以放置各种各样的控件，使程序支持用户输入的手段更加的丰富。

* 向导生成的对话框分析

* 模态对话框和非模态对话框

# MFC控件

* 控件的属性和方法
  ### BUTTON
  
  
  
  ### EDIT
  
  
  
  ### RADIOBOX
  
  
  
  ### Ccombobox
  
  ​        类CComboBox封装了Windows组合框。组合框由一个列表框和一个静态控件（或编辑控件）组成。列表框部分可以是一直显示的，也可以是隐藏的，在用户单击编辑控件边上的按钮（下拉箭头）时下拉该列表框。列表框中当前选中的项（如果有的话）显示在静态控件或编辑控件中。如果组合框带有下拉风格，则当用户在编辑框中输入列表项的开始字符时，对应项（如果有的话）中的第一个将会加亮显示。
  
  ```cpp
  /*  控件类型
  Simple 总是可见 编辑控件  
  Drop-down 当用户单击控件边上的下拉箭头时 编辑控件  
  Drop-downlist 当用户单击控件边上的下拉箭头时 静态控件  
  */
  ```
  
  * 控件下拉的多行显示，在data中编辑并用分号隔开下一行
  * Ccombobox消息

```cpp
// 下拉事件
void CCcomboxDlgDlg::OnDropdownCombo1()
{
	SetWindowText(L"OnDropdownCombo1");
}

// 改变选中
void CCcomboxDlgDlg::OnSelchangeCombo1()
{
	SetWindowText(L"OnSelchangeCombo1");
}

```





* ListCtrl控件
  * 设置控件的风格report
  * CListCtrl的扩展风格

```cpp
#define LVS_EX_GRIDLINES        0x00000001 // 网格线
#define LVS_EX_SUBITEMIMAGES    0x00000002 // 
#define LVS_EX_CHECKBOXES       0x00000004 // 带复选框
#define LVS_EX_TRACKSELECT      0x00000008 // 自动换行
#define LVS_EX_HEADERDRAGDROP   0x00000010 
#define LVS_EX_FULLROWSELECT    0x00000020 // applies to report mode only使某行高亮
#define LVS_EX_ONECLICKACTIVATE 0x00000040 // 单击激活
#define LVS_EX_TWOCLICKACTIVATE 0x00000080 // 双击激活
#define LVS_EX_FLATSB           0x00000100 // 扁平滚动条
#define LVS_EX_REGIONAL         0x00000200 // 
#define LVS_EX_INFOTIP          0x00000400 // listview does InfoTips for you
#define LVS_EX_UNDERLINEHOT     0x00000800
#define LVS_EX_UNDERLINECOLD    0x00001000
#define LVS_EX_MULTIWORKAREAS   0x00002000
#define LVS_EX_LABELTIP         0x00004000 // listview unfolds partly hidden labels if it does not have infotip text
#define LVS_EX_BORDERSELECT     0x00008000 // border selection style instead of highlight
```

* treeCtrl

```cpp
// 控件风格

```



