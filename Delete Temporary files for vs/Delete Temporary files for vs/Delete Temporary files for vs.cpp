
// Delete Temporary files for vs.cpp : ����Ӧ�ó��������Ϊ��
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


// CDeleteTemporaryfilesforvsApp ����

CDeleteTemporaryfilesforvsApp::CDeleteTemporaryfilesforvsApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDeleteTemporaryfilesforvsApp ����

CDeleteTemporaryfilesforvsApp theApp;


// CDeleteTemporaryfilesforvsApp ��ʼ��

BOOL CDeleteTemporaryfilesforvsApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CDeleteTemporaryfilesforvsDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
void delete_ReleaseAndDebug(CString ReleaseAndDebugDir)
{
	CFileFind ff;
	CString strisdirpath;
	BOOL Releaseres = ff.FindFile( L"*.*");		//ɾ�� Release Debug  �ļ���
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

	BOOL Releaseres = ff.FindFile( L"*.*");		//ɾ�� Release Debug  �ļ���
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

	BOOL sdfres= sdf.FindFile(  L"*.sdf");		//ɾ�� sdf �ļ�
	while (sdfres)
	{
		sdfres = sdf.FindNextFileW();
		findfile = sdf.GetFilePath();
		DeleteFile( findfile );
	}
	BOOL ipchres = ipch.FindFile( L"*.ipch");		//ɾ�� ipch �ļ�
	while ( ipchres)
	{
		ipchres = ipch.FindNextFileW() ;
		findfile = ipch.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL pdbres = pdb.FindFile( L"*.pdb");		//ɾ�� pdb �ļ�
	while ( pdbres)
	{
		pdbres = pdb.FindNextFileW() ;
		findfile = pdb.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL idbres = ff.FindFile( L"*.idb");		//ɾ�� idb �ļ�
	while ( idbres)
	{
		idbres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL pchres = ff.FindFile( L"*.pch");		//ɾ�� pch �ļ�
	while ( pchres)
	{
		pchres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL objres = ff.FindFile( L"*.obj");		//ɾ�� obj �ļ�
	while ( objres)
	{
		objres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL ilkres = ff.FindFile( L"*.ilk");		//ɾ�� ilk �ļ�
	while ( ilkres)
	{
		ilkres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}
	BOOL resres = ff.FindFile( L"*.res");		//ɾ�� res �ļ�
	while ( resres)
	{
		ilkres = ff.FindNextFileW() ;
		findfile = ff.GetFilePath();
		DeleteFile (findfile);
	}


	BOOL dirres = ff.FindFile( L"*.*");		//������Ŀ¼
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
