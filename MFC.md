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

