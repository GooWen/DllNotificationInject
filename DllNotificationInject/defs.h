#pragma once

#include <Windows.h>
#include <winternl.h>

typedef struct _LDR_DLL_UNLOADED_NOTIFICATION_DATA {
	ULONG Flags;                    //Reserved.
	PCUNICODE_STRING FullDllName;   //The full path name of the DLL module.
	PCUNICODE_STRING BaseDllName;   //The base file name of the DLL module.
	PVOID DllBase;                  //A pointer to the base address for the DLL in memory.
	ULONG SizeOfImage;              //The size of the DLL image, in bytes.
} LDR_DLL_UNLOADED_NOTIFICATION_DATA, * PLDR_DLL_UNLOADED_NOTIFICATION_DATA;

typedef struct _LDR_DLL_LOADED_NOTIFICATION_DATA {
	ULONG Flags;                    //Reserved.
	PCUNICODE_STRING FullDllName;   //The full path name of the DLL module.
	PCUNICODE_STRING BaseDllName;   //The base file name of the DLL module.
	PVOID DllBase;                  //A pointer to the base address for the DLL in memory.
	ULONG SizeOfImage;              //The size of the DLL image, in bytes.
} LDR_DLL_LOADED_NOTIFICATION_DATA, * PLDR_DLL_LOADED_NOTIFICATION_DATA;

typedef union _LDR_DLL_NOTIFICATION_DATA {
	LDR_DLL_LOADED_NOTIFICATION_DATA Loaded;
	LDR_DLL_UNLOADED_NOTIFICATION_DATA Unloaded;
} LDR_DLL_NOTIFICATION_DATA, * PLDR_DLL_NOTIFICATION_DATA;

using PCLDR_DLL_NOTIFICATION_DATA = const PLDR_DLL_NOTIFICATION_DATA;


using LdrDllNotificationFunc = VOID(CALLBACK*) (
	_In_     ULONG                       NotificationReason,
	_In_     PCLDR_DLL_NOTIFICATION_DATA NotificationData,
	_In_opt_ PVOID                       Context
	);

using PLDR_DLL_NOTIFICATION_FUNCTION = LdrDllNotificationFunc*;

using LdrRegisterDllNotificationFunc = NTSTATUS(NTAPI*)(
	_In_     ULONG                          Flags,
	_In_     PLDR_DLL_NOTIFICATION_FUNCTION NotificationFunction,
	_In_opt_ PVOID                          Context,
	_Out_    PVOID* Cookie
	);

typedef struct _LDR_DLL_NOTIFICATION_ENTRY {
	LIST_ENTRY                     List;
	PLDR_DLL_NOTIFICATION_FUNCTION Callback;
	PVOID                          Context;
} LDR_DLL_NOTIFICATION_ENTRY, * PLDR_DLL_NOTIFICATION_ENTRY;
