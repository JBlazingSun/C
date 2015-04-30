
// Delete Temporary files for vs.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Delete Temporary files for vs.h"
#include "Delete Temporary files for vsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDeleteTemporaryfilesforvsDlg *deleteDlg ;

// CDeleteTemporaryfilesforvsApp

BEGIN_MESSAGE_MAP(CDeleteTemporaryfilesforvsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDeleteTemporaryfilesforvsApp 构造

CDeleteTemporaryfilesforvsApp::CDeleteTemporaryfilesforvsApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CDeleteTemporaryfilesforvsApp 对象

CDeleteTemporaryfilesforvsApp theApp;


// CDeleteTemporaryfilesforvsApp 初始化

BOOL CDeleteTemporaryfilesforvsApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CDeleteTemporaryfilesforvsDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
void delete_ReleaseAndDebug(CString ReleaseAndDebugDir)
{
	CFileFind ff;
	CString strisdirpath;
	BOOL Releaseres = ff.FindFile( L"*.*");		//删除 Release Debug  文件夹
	while ( Releaseres)
	{
		Releaseres = ff.FindNextFileW();
		if ( ff.IsDots())
		{
			continue;
		}
		if ( !ff.IsDirectory() && !ff.IsDots() )
		{
			DeleteFile(ff.GetFilePath());
		}
	}
}

void Searchfile ( CString strisdirpath )
{
	CString strdir;
	CString ReleaseAndDebug;
	CString findfile;
	CFileFind sdf;
	CFileFind ipch;
	CFileFind pdb;
	CFileFind ff;
	::SetDlgItemTextW( deleteDlg ->m_hWnd ,IDC_EDIT1, strisdirpath );
	SetCurrentDirectory(strisdirpath);

	BOOL Releaseres = ff.FindFile( L"*.*");		//删除 Release Debug  文件夹
	while ( Releaseres)
	{
		Releaseres = ff.FindNextFileW();
		if ( ff.IsDots())
		{
			continue;
		}
		if ( ff.IsDirectory() )
		{
			strisdirpath  = ff.GetFileName();
			if ( !wcscmp( strisdirpath , L"Release") )
			{
				SetCurrentDirectory( ff.GetFilePath() );
				delete_ReleaseAndDebug( ff.GetFilePath() );
				ReleaseAndDebug=ff.GetFilePath();
				SetCurrentDirectory( L".." );
				RemoveDirectory(ReleaseAndDebug);
			}
			if ( !wcscmp( strisdirpath , L"Debug") )
			{
				SetCurrentDirectory( ff.GetFilePath() );
				delete_ReleaseAndDebug( ff.GetFilePath() );
				ReleaseAndDebug=ff.GetFilePath();
				SetCurrentDirectory( L".." );
				RemoveDirectory(ReleaseAndDebug);
			}
		}
	}

	BOOL sdfres= sdf.FindFile(  L"*.sdf");		//删除 sdf 文件
	while (sdfres)
	{
		sdfres = sdf.FindNextFileW();
		findfile = sdf.GetFilePath();
		DeleteFile( findfile );
	}
	BOOL ipchres = ipch.FindFile( L"*.ipch");		//删除 ipch 文件
	while ( ipchres)
	{
		ipchres = ipch.FindNextFileW() ;
		findfile = ipch.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL pdbres = pdb.FindFile( L"*.pdb");		//删除 pdb 文件
	while ( pdbres)
	{
		pdbres = pdb.FindNextFileW() ;
		findfile = pdb.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL idbres = ff.FindFile( L"*.idb");		//删除 idb 文件
	while ( idbres)
	{
		idbres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL pchres = ff.FindFile( L"*.pch");		//删除 pch 文件
	while ( pchres)
	{
		pchres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL objres = ff.FindFile( L"*.obj");		//删除 obj 文件
	while ( objres)
	{
		objres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL ilkres = ff.FindFile( L"*.ilk");		//删除 ilk 文件
	while ( ilkres)
	{
		ilkres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL resres = ff.FindFile( L"*.res");		//删除 res 文件
	while ( resres)
	{
		ilkres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}


	BOOL dirres = ff.FindFile( L"*.*");		//进入子目录
	while (dirres)
	{
		dirres = ff.FindNextFileW();
		if ( ff.IsDots())
		{
			continue;
		}
		if ( ff.IsDirectory() )
		{
			strisdirpath  = ff.GetFilePath();
			Searchfile( strisdirpath );
		}
	}
	
}
