// LowOnResources.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

#include "Header.h"

void CreateTooManySections()
{
	ulonglong var_MaxSize = 0x100000;
	_LARGE_INTEGER MaxSize = {0};
	MaxSize.QuadPart = var_MaxSize;

	while(1)
	{
		HANDLE hSection = 0;
		int ret = ZwCreateSection(&hSection,GENERIC_ALL,
			0,
			&MaxSize,
			PAGE_READWRITE,
			SEC_RESERVE,
			0);
		printf("ZwCreateSection, ret: %X\r\n",ret);
	
		if(ret >= 0)
		{
			//ZwClose(hSection);
		}

		var_MaxSize += 0x100000;
		MaxSize.QuadPart = var_MaxSize;
	}

	return;
}

bool bPrintXXXX = true;

void ThreadProcXXXX()
{
	if(bPrintXXXX)	printf("Hello from new thread\r\n");
	return;
}

void CreateThreadMine()
{

	_OBJECT_ATTRIBUTES ObjAttr = {0};
	ObjAttr.Length = sizeof(ObjAttr);
	
	HANDLE hThreadNew = 0;
	int ret = 
		ZwCreateThreadEx(&hThreadNew,GENERIC_ALL,&ObjAttr,
					GetCurrentProcess(),ThreadProcXXXX,0 /* Arg */,
					0 /* CreationFlags */,
					0 /* ZeroBits */,
					0x1000 /* StackSize */,
					0x10000 /* MaxStackSize */,
					0 /* AttributeList */);
	printf("ZwCreateThreadEx, ret: %X\r\n",ret);

}


int _tmain(int argc, _TCHAR* argv[])
{
	ulong tidsec = 0;
	HANDLE hThreadSec = CreateThread(0,0x1000,(LPTHREAD_START_ROUTINE)CreateTooManySections,0,0,&tidsec);

	//Create Too Many Threads
	while(1)
	{
		CreateThreadMine();
	}
	Sleep(-1);
	return 0;
}

