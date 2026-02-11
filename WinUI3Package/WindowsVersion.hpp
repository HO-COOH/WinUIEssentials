#ifndef __RTL_VERSION_H__
#define __RTL_VERSION_H__

#include <windows.h>

#ifdef _MSC_VER
// not tested yet
#pragma comment(lib, "ntdll")
#endif // _MSC_VER

#ifdef  __cplusplus
extern "C" {
#endif // __cplusplus

    typedef _Success_(return >= 0) LONG NTSTATUS;
    typedef NTSTATUS* PNTSTATUS;

    NTSYSAPI NTSTATUS NTAPI RtlGetVersion(
        _Out_ PRTL_OSVERSIONINFOEXW lpVersionInformation
    );

    NTSYSAPI NTSTATUS NTAPI RtlVerifyVersionInfo(
        _In_ PRTL_OSVERSIONINFOEXW VersionInfo,
        _In_ ULONG TypeMask,
        _In_ ULONGLONG ConditionMask
    );

    // rev
    NTSYSAPI VOID NTAPI RtlGetNtVersionNumbers(
        _Out_opt_ PULONG NtMajorVersion,
        _Out_opt_ PULONG NtMinorVersion,
        _Out_opt_ PULONG NtBuildNumber
    );

#ifdef  __cplusplus
}
#endif // __cplusplus

OSVERSIONINFOEXW const& GetWindowsVersion();

#endif // __RTL_VERSION_H__