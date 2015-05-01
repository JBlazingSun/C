/*--------------------------------------------------------------
   add2crc32.cpp -- �����ļ���CRC32ֵ
   ����������������������������������
                           (c) code by �θ�,www.pediy.com  2003
  --------------------------------------------------------------*/

#include <windows.h>

int patch();
DWORD getCrc32(HANDLE);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{

	patch();
    		
	return 0;
}

//////////////////////////////////////////////////////////////////////



int patch()
{
	TCHAR szFileName[MAX_PATH ] ;
	static OPENFILENAME ofn ;
	HANDLE hFile;	
	DWORD szTemp;
	long FileSize;
	DWORD szCRC32;
	TCHAR  *pBuffer ;
	BYTE* ptr;
	WORD PEheader;

	static TCHAR szFilter[] =TEXT ("EXE Files (*.exe)\0*.exe\0") \
		TEXT ("All Files (*.*)\0*.*\0\0") ;

	szFileName[0] = '\0';                         
	ZeroMemory(&ofn, sizeof(ofn));                             // ��ʼ��OPENFILENAME�ṹ
	ofn.lStructSize       = sizeof (OPENFILENAME) ;
	ofn.lpstrFilter       = szFilter ;
	ofn.lpstrFile         = szFileName ;         
	ofn.nMaxFile          = MAX_PATH ;   
	ofn.nMaxFileTitle     = MAX_PATH ;
	ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;           

	if(GetOpenFileName (&ofn))
	{

		hFile = CreateFile(
			szFileName,
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ, 
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		    
		     if( hFile != INVALID_HANDLE_VALUE )
		     {
			     FileSize=GetFileSize(hFile,&szTemp);  // ��ȡ�ļ���С
			     if (FileSize == 0xFFFFFFFF) return FALSE;
			     pBuffer = new TCHAR [FileSize];     // �����ڴ�
			     if(ReadFile(hFile, pBuffer, FileSize, &szTemp, NULL)==NULL) return FALSE;// ��ȡ����
			     ptr=(BYTE*)pBuffer; //ptrָ���ļ�ͷ

		     }
		     else
		     {
			     MessageBox(NULL,"I can't access file!","CRC error",MB_ICONEXCLAMATION);
		             return 0;
		     }
	
	}
	else
		return 0;
		
	szCRC32=getCrc32(hFile);//����CRC32
	szCRC32^=0x4597563;
	//��3ch����PE�ļ�ͷָ�룺
	PEheader = *(WORD*)(ptr+0x3c);
	
	DWORD Writeadd=DWORD(PEheader-4);//��λ��PE�ļ�ͷ�����ִ���PE\0\0������ǰ4���ֽڴ���׼������дCRC-32ֵ��
	SetFilePointer(hFile,Writeadd,NULL,FILE_BEGIN);//�����ļ�ָ��

	if(!WriteFile(hFile,&szCRC32,4,&szTemp,NULL))
	{
		MessageBox(NULL,"Error while patching !","Patch aborted",MB_ICONEXCLAMATION);
		CloseHandle(hFile);
		return 0;
	}


	CloseHandle(hFile);
	MessageBox(NULL,"Patch successfull !","Patch",MB_ICONINFORMATION);
	return 1;

}

//	delete pBuffer; 
//	return FALSE;

////////////////////////////////////////////////////////////////
// �����ļ���CRC32ֵ
//
// ���� : �ļ��ľ��
// ����ֵ : �����ļ���CRC32ֵ�����󷵻�0 

DWORD getCrc32(HANDLE hFile)
{
	//generate CRC constant table :
	DWORD crcTable[256];
	DWORD crcTmp1;
	BYTE* ptr;
	WORD PEheader;
    
	for (int i=0; i<256; i++)
    {
        crcTmp1 = i;
        for (int j=8; j>0; j--)
        {
            if (crcTmp1&1) crcTmp1 = (crcTmp1 >> 1) ^ 0xEDB88320L;
            else crcTmp1 >>= 1;
        }

        crcTable[i] = crcTmp1;
    }


	//getfilesize :
	DWORD fileSize = GetFileSize(hFile,NULL);
	if (fileSize == 0xFFFFFFFF) return 0;


	//Compute CRC32 : 
	HANDLE hFileMapping = CreateFileMapping(
		hFile,
		NULL,PAGE_READONLY,
		0,
		0,
		NULL);
		
	if (!hFileMapping) return 0;

	ptr = (BYTE*)MapViewOfFile(
		hFileMapping,
		FILE_MAP_READ,
		0,
		0,
		0);

	if (!ptr)
	{
		CloseHandle(hFileMapping);
		return 0;
	}

	BYTE* ptr_tmp = ptr; // save base pointer
	DWORD crcTmp2= 0xFFFFFFFF;

	PEheader = *(WORD*)(ptr+0x3c);//��3ch����PE�ļ�ͷָ�룺
	ptr=PEheader+ptr;
	fileSize=fileSize-DWORD(PEheader); //��PE �ļ�ͷǰ�����ݳ��ȼ�ȥ

	while(fileSize--)
	{
		crcTmp2 = ((crcTmp2>>8) & 0x00FFFFFF) ^ crcTable[ (crcTmp2^(*ptr)) & 0xFF ];
		ptr++;
	}

	crcTmp2^=618;

	UnmapViewOfFile(ptr_tmp);
	CloseHandle(hFileMapping);
	return (crcTmp2^0xFFFFFFFF);
}
