/*--------------------------------------------------------------
   add2crc32.cpp -- 计算文件的CRC32值
   　　　　　　　　　　　　　　　　　
                           (c) code by 段钢,www.pediy.com  2003
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
	ZeroMemory(&ofn, sizeof(ofn));                             // 初始化OPENFILENAME结构
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
			     FileSize=GetFileSize(hFile,&szTemp);  // 获取文件大小
			     if (FileSize == 0xFFFFFFFF) return FALSE;
			     pBuffer = new TCHAR [FileSize];     // 申请内存
			     if(ReadFile(hFile, pBuffer, FileSize, &szTemp, NULL)==NULL) return FALSE;// 读取数据
			     ptr=(BYTE*)pBuffer; //ptr指向文件头

		     }
		     else
		     {
			     MessageBox(NULL,"I can't access file!","CRC error",MB_ICONEXCLAMATION);
		             return 0;
		     }
	
	}
	else
		return 0;
		
	szCRC32=getCrc32(hFile);//计算CRC32
	szCRC32^=0x4597563;
	//读3ch处的PE文件头指针：
	PEheader = *(WORD*)(ptr+0x3c);
	
	DWORD Writeadd=DWORD(PEheader-4);//定位到PE文件头（即字串“PE\0\0”处）前4个字节处，准备在这写CRC-32值：
	SetFilePointer(hFile,Writeadd,NULL,FILE_BEGIN);//设置文件指针

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
// 计算文件的CRC32值
//
// 参数 : 文件的句柄
// 返回值 : 返回文件的CRC32值，错误返回0 

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

	PEheader = *(WORD*)(ptr+0x3c);//读3ch处的PE文件头指针：
	ptr=PEheader+ptr;
	fileSize=fileSize-DWORD(PEheader); //将PE 文件头前的数据长度减去

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
