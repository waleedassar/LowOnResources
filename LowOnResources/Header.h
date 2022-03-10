#pragma once
#include "windows.h"



#define ulong unsigned long
#define ulonglong unsigned long long
#define longlong long long
#define ULONG unsigned long
#define ULONGLONG unsigned long long
#define ushort unsigned short
#define USHORT unsigned short
#define UCHAR unsigned char
#define uchar unsigned char

#define OBJ_PROTECT_CLOSE 		0x00000001
#define OBJ_INHERIT             0x00000002
#define OBJ_AUDIT_OBJECT_CLOSE  0x00000004
#define OBJ_PERMANENT           0x00000010
#define OBJ_EXCLUSIVE           0x00000020
#define OBJ_CASE_INSENSITIVE    0x00000040
#define OBJ_OPENIF              0x00000080
#define OBJ_OPENLINK            0x00000100
#define OBJ_KERNEL_HANDLE       0x00000200
#define OBJ_FORCE_ACCESS_CHECK  0x00000400
#define OBJ_VALID_ATTRIBUTES    0x000007F2
#define OBJ_CREATOR_INFO_MINE   0x00010000

#define 	FILE_SUPERSEDE   0x00000000
#define 	FILE_OPEN   0x00000001
#define 	FILE_CREATE   0x00000002
#define 	FILE_OPEN_IF   0x00000003
#define 	FILE_OVERWRITE   0x00000004
#define 	FILE_OVERWRITE_IF   0x00000005
#define 	FILE_MAXIMUM_DISPOSITION   0x00000005
#define 	FILE_DIRECTORY_FILE   0x00000001
#define 	FILE_WRITE_THROUGH   0x00000002
#define 	FILE_SEQUENTIAL_ONLY   0x00000004
#define 	FILE_NO_INTERMEDIATE_BUFFERING   0x00000008
#define 	FILE_SYNCHRONOUS_IO_ALERT   0x00000010
#define 	FILE_SYNCHRONOUS_IO_NONALERT   0x00000020
#define 	FILE_NON_DIRECTORY_FILE   0x00000040
#define 	FILE_CREATE_TREE_CONNECTION   0x00000080
#define 	FILE_COMPLETE_IF_OPLOCKED   0x00000100
#define 	FILE_NO_EA_KNOWLEDGE   0x00000200
#define 	FILE_OPEN_FOR_RECOVERY   0x00000400
#define 	FILE_RANDOM_ACCESS   0x00000800
#define 	FILE_DELETE_ON_CLOSE   0x00001000
#define 	FILE_OPEN_BY_FILE_ID   0x00002000
#define 	FILE_OPEN_FOR_BACKUP_INTENT   0x00004000
#define 	FILE_NO_COMPRESSION   0x00008000
#define 	FILE_OPEN_REQUIRING_OPLOCK   0x00010000
#define 	FILE_DISALLOW_EXCLUSIVE   0x00020000
#define 	FILE_SESSION_AWARE   0x00040000
#define 	FILE_RESERVE_OPFILTER   0x00100000
#define 	FILE_OPEN_REPARSE_POINT   0x00200000
#define 	FILE_OPEN_NO_RECALL   0x00400000
#define 	FILE_OPEN_FOR_FREE_SPACE_QUERY   0x00800000

#define SEC_IMAGE           0x1000000
#define SEC_NEVER_RELOCATE 0x8000000 //SEC_DATA
#define SEC_UNK 0x100000
#define SEC_PROTECTED_IMAGE 0x2000000
#define SEC_FOR_DRIVER 0x400000
#define SEC_UNK2 0x4000000
#define SEC_UNK3 0x10000000
#define SEC_UNK4 0x40000000
#define SEC_UNK5 0x80000000


#define SEC_FILE           0x800000
#define SEC_VLM           0x2000000
#define SEC_RESERVE       0x4000000
#define SEC_COMMIT        0x8000000
#define SEC_NOCACHE      0x10000000

typedef enum _SECTION_INHERIT {
    ViewShare=1,
    ViewUnmap=2
} SECTION_INHERIT, *PSECTION_INHERIT;


struct _PEB_LDR_DATA
{
   ulong Length;
   uchar Initialized;
   uchar Pad[3];
   ulonglong SsHandle;
   _LIST_ENTRY InLoadOrderModuleList;
   _LIST_ENTRY InMemoryOrderModuleList;
   _LIST_ENTRY InInitializationOrderModuleList;
   ulonglong EntryInProgress;
   uchar ShutdownInProgress;
   uchar Pad_[7];
   ulonglong ShutdownThreadId;
};

struct _PEB
{
   uchar InheritedAddressSpace;
   uchar ReadImageFileExecOptions;
   uchar BeingDebugged;
   uchar BitField;
   uchar Padding0[4];
   ulonglong Mutant;
   void* ImageBaseAddress;
   _PEB_LDR_DATA* Ldr;
   void* ProcessParameters;
   void* SubSystemData;

};


struct _UNICODE_STRING
{
	unsigned short Length;
	unsigned short MaxLength;
	unsigned long Pad;
	wchar_t* Buffer;
};
typedef struct _OBJECT_ATTRIBUTES {
  ULONGLONG           Length;
  HANDLE          RootDirectory;
  _UNICODE_STRING* ObjectName;
  ULONGLONG           Attributes;
  PVOID           SecurityDescriptor;
  PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES;


typedef struct _IO_STATUS_BLOCK {
  union {
    NTSTATUS Status;
    void*    Pointer;
  } DUMMYUNIONNAME;
  ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;


struct _CLIENT_ID
{
	unsigned long long UniqueProcess;
	unsigned long long UniqueThread;
};


struct _SECTION_IMAGE_INFORMATION
{
   void* TransferAddress;	//EntryPoint after relocation
   ulong ZeroBits;
   ulong Pad;
   ulonglong MaximumStackSize;
   ulonglong CommittedStackSize;
   ulong SubSystemType;
   ushort SubSystemMinorVersion;
   ushort SubSystemMajorVersion;
   ulong GpValue;
   ushort ImageCharacteristics;
   ushort DllCharacteristics;
   ushort Machine;
   uchar ImageContainsCode;
   struct
   {
	uchar ComPlusNativeReady:1;
	uchar ComPlusILOnly:1;
	uchar ImageDynamicallyRelocated:1;
    uchar ImageMappedFlat:1;
	uchar Reserved:4;
   }ImageFlags;
   ulong LoaderFlags;
   ulong ImageFileSize;
   ulong CheckSum;
};

struct _SECTION_0
{
	ulonglong LeftChild;
	ulong SectionFlags;
	ulong Pad;
	ulonglong SizeOfSegment;
};

extern "C"
{
		int ZwCreateSection(HANDLE* SectionHandle,
						ACCESS_MASK DesiredAccess,
						_OBJECT_ATTRIBUTES* ObjectAttributes,
						_LARGE_INTEGER* MaximumSize,
						ulonglong SectionPageProtection,
						ulonglong AllocationAttributes,
						HANDLE FileHandle);


		int ZwOpenFile(HANDLE* FileHandle,
			ACCESS_MASK DesiredAccess, 
			_OBJECT_ATTRIBUTES* ObjectAttributes, 
			_IO_STATUS_BLOCK* IoStatusBlock, 
			ulonglong ShareAccess,
			ulonglong OpenOptions);


		 
		int ZwMapViewOfSection(HANDLE SectionHandle,
			HANDLE ProcessHandle, 
			void* *BaseAddress,
			ulonglong ZeroBits,
			ulonglong CommitSize, 
			_LARGE_INTEGER* SectionOffset, 
			ulonglong* ViewSize,
			SECTION_INHERIT InheritDisposition,
			ulonglong AllocationType,
			ulonglong Win32Protect);
 
		int ZwClose(HANDLE Handle);

		int ZwUnmapViewOfSection(HANDLE ProcessHandle,void* BaseAddress ) ;

		int ZwExtendSection(HANDLE SectionHandle, _LARGE_INTEGER* NewSectionSize);

		
		int NtQuerySection
		(HANDLE SectionHandle, 
		ulonglong SectionInformationClass, 
		void* SectionInformation, 
		ulonglong SectionInformationLength,  
		ulonglong* ReturnLength);


		int ZwQueryInformationProcess(HANDLE ProcessHandle,ulonglong ProcessInformationClass,  void* ProcessInformation,ulonglong ProcessInformationLength,  ulonglong* ReturnLength);
		int ZwSetInformationProcess(HANDLE ProcessHandle,ulonglong ProcessInformationClass, void* ProcessInformation,ulonglong ProcessInformationLength);
}

struct _PS_ATTRIBUTE
{
	ulonglong Attribute;
    ulonglong Size;
    ulonglong Value;
    ulonglong ReturnLength;
};

struct _PS_ATTRIBUTE_LIST
{
   ulonglong TotalLength;
   _PS_ATTRIBUTE Attributes[1];
};

extern "C"
{
	int ZwCreateThreadEx(HANDLE* ThreadHandle,
		ACCESS_MASK DesiredAccess,
		_OBJECT_ATTRIBUTES* ObjectAttributes,
		HANDLE ProcessHandle,
		void* StartRoutine,
		void* Argument,
		ulonglong CreateFlags,
		ulonglong ZeroBits,
		ulonglong StackSize,
		ulonglong MaximumStackSize,
		_PS_ATTRIBUTE_LIST* AttributeList);
}