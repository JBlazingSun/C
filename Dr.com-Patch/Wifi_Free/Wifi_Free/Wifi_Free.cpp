// Wifi_Free.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Wifi_Free.h"

#include "MyApp.h"
#include <fstream>
#include "iostream"
#include "Winsvc.h"
#include "AmHttpSocket.h"
#include "MessageDlg.h"


using namespace std;


JysNT jy;
//CMessageDlg mdlg;
int CheckNet=0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
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
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CWifi_FreeApp

BEGIN_MESSAGE_MAP(CWifi_FreeApp, CWinApp)
END_MESSAGE_MAP()


// CWifi_FreeApp 构造

CWifi_FreeApp::CWifi_FreeApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CWifi_FreeApp 对象

CWifi_FreeApp theApp;


// CWifi_FreeApp 初始化

#define IDoffset 0x8DC00
void MyWifi::GetId()
{
	DWORD drauthsvr_dll_baseaddr,idaddr;
	drauthsvr_dll_baseaddr=(DWORD)GetModuleHandle(L"drauthsvr.dll");
	while(!drauthsvr_dll_baseaddr)
	{
		drauthsvr_dll_baseaddr=(DWORD)GetModuleHandle(L"drauthsvr.dll");
		Sleep(200);
	}
	idaddr=drauthsvr_dll_baseaddr+IDoffset;

	DWORD OldProtect;
	VirtualProtect((LPVOID)idaddr,100,PAGE_READWRITE,&OldProtect);
	this->strgetid=(char*)idaddr;
	VirtualProtect((LPVOID)idaddr,100,OldProtect,&OldProtect);
}

BOOL MyWifi::CheckId()
{
	CAmHttpSocket Chttp; 
	MyWifi wifi;
	CString AccessURL=L"http://ftpanyele.w4.12by.cn/Check/Querylogin.asp?txtUserId=";
	if (!this->strgetid)
	{
		MessageBox(0,L"获取ID失败,请关闭客户端重新打开",0,0);
	}
	AccessURL+=this->strgetid;
	CString str1=(CString)Chttp.GetPage(AccessURL,0,0,0);
	CString str2=L"正确";

	if(!_tcsicmp(str1,str2))
	{
		_beginthread(PatchMem,0,0);
		MessageBox(0,L"破解成功，可以打开Connectify或类似的共享软件了",L"成功",0);
		HINSTANCE hinstance;
		hinstance =(HINSTANCE)GetModuleHandle(L"Wifi_Free.dll");
		FreeLibrary( hinstance);
	}
	
	else
	{
		MessageBox(0,L"请联系管理员帮你的账号授权。如果授权之后也出现本提示，有可能是服务器出问题，请耐心等待下",0,0);
		HINSTANCE hinstance;
		hinstance =(HINSTANCE)GetModuleHandle(L"Wifi_Free.dll");
		FreeLibrary( hinstance);
	}
}

void PatchMem(void *arg1)
{
	//char Connectifyfilenamecomp[0xA]={0x43,0x6F,0x6E,0x6E,0x65,0x63,0x74,0x69,0x66,0x79}; //0x43,0x6F,0x6E,0x6E,0x65,0x63,0x74,0x69,0x66,0x79   43 6F 6E 6E 65 63 74 69 66 79
	char WIN7filenamecomp[0x8]={0x41,0x75,0x74,0x68,0x53,0x76,0x72,0x41}; // 41 75 74 68 53 76 72 41 改成AuthSvrA		偏移 66070

	Sleep(1);
	DWORD spbase;
	spbase=(DWORD)GetModuleHandle(L"drauthsvr.dll");
	while(!spbase)
	{
		spbase=(DWORD)GetModuleHandle(L"drauthsvr.dll");
		Sleep(100);
	}
	if (spbase)
	{
		Sleep(2000);
		int filenamecompaddr=(int)jy.MemSearch((const unsigned char*)spbase,647168,(const unsigned char*)WIN7filenamecomp,0x8);
		if (IsBadReadPtr((void*)filenamecompaddr,4))
		{
			MessageBoxA(NULL,"版本错误，无法开启。1","",NULL);
		}

		DWORD dwOldFlag;
		VirtualProtect((void*)(filenamecompaddr),8848,PAGE_READWRITE,&dwOldFlag);

		for (int i=0;i<10000;i++)
		{
			*(byte*)(filenamecompaddr+i)=0x90;
		}
		VirtualProtect((void*)(filenamecompaddr),8848,dwOldFlag,&dwOldFlag);
	}
	
}

void killProcessthread(void *)
{
	while(1)
	{
		HANDLE handle=jy.CreateToolhelp32SnapshottoOpenProcess(L"DrUpdate.exe");
		TerminateProcess(handle,0);
		Sleep(100);
	}
}

BOOL CheckInternet()
{
	CString m_url=L"http://www.sina.com.cn";
	BOOL bConn = ::InternetCheckConnection(m_url, 1, 0);  
	if (bConn)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void CheckNet_Thread(void *)
{
	int i=0;
	i=CheckInternet();
	while( !i )
	{
		i=CheckInternet();
		Sleep(300);
	}
	CheckNet=1;
}

void Patchthread( void *)
{
	int i=0;
	while ( !i )
	{
		if (CheckNet==1)
		{
			i=1;
		}
		Sleep(300);
	}
	MyWifi wifi;
	wifi.GetId();
	wifi.CheckId();
}

BOOL EnableDebugPrivilege() 
{ 
	HANDLE hToken; 
	BOOL fOk=FALSE; 
	if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken)) 
	{ 
		TOKEN_PRIVILEGES tp; 
		tp.PrivilegeCount=1; 
		if(!LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&tp.Privileges[0].Luid)) 
			printf("Can't lookup privilege value.\n"); 
		tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED; 
		if(!AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(tp),NULL,NULL)) 
			printf("Can't adjust privilege value.\n"); 
		fOk=(GetLastError()==ERROR_SUCCESS); 
		CloseHandle(hToken); 
	} 
	return fOk; 
} 

BOOL CWifi_FreeApp::InitInstance()
{
	CWinApp::InitInstance();
	EnableDebugPrivilege();

	CMessageDlg *MDlg=new CMessageDlg;
	MDlg->Create( IDD_DIALOG1,0);
	MDlg->ShowWindow( SW_SHOW);

	_beginthread(CheckNet_Thread,0,0); //检测网络是否连通

	_beginthread(Patchthread,0,0);

//	_beginthread(PatchMem,0,0);

	_beginthread(killProcessthread,0,0);
	

	return TRUE;
}


extern "C" _declspec(dllexport) void Hello()
{
	;
}