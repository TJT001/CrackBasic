// MFCKeyHOOKDll.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "MFCKeyHOOKDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMFCKeyHOOKDllApp

BEGIN_MESSAGE_MAP(CMFCKeyHOOKDllApp, CWinApp)

END_MESSAGE_MAP()


// CMFCKeyHOOKDllApp 构造

CMFCKeyHOOKDllApp::CMFCKeyHOOKDllApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCKeyHOOKDllApp 对象

CMFCKeyHOOKDllApp theApp;


// CMFCKeyHOOKDllApp 初始化

BOOL CMFCKeyHOOKDllApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

#define WH_KEYBOARD_LL 13
// 通过一个自定义消息
#define WM_USER 0x400
#define MWM_MYMSG_1 WM_USER+1

HHOOK g_Hook;
HWND g_Wnd;

// 回调函数
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, // hook code
	WPARAM wParam,  // message identifier
	LPARAM lParam)  // meaage data
{
	if (nCode == HC_ACTION)
	{
		SendMessage(g_Wnd, MWM_MYMSG_1, wParam, lParam);
	}
	return CallNextHookEx(g_Hook, nCode, wParam, lParam);
}


BOOL StartHook(HWND hwnd)
{
	if (hwnd == NULL)
		return false;
	g_Wnd = hwnd;
	g_Hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandleW(L"MFCKeyHOOKDll.dll"), 0);
	if (g_Hook)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	

}


// 作业： 通过代码去实现一个全局的钩子
// 在dll的键盘钩子里面，通过SendMessage把消息传递给主窗口来处理
