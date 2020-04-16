#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <assert.h>
#include <windows.h> 
#include <lm.h>

int wmain(int argc, wchar_t* argv[])
{
    LPUSER_INFO_0 pBuf = NULL;
    LPWSTR servername = NULL;
    DWORD level = 0;
    DWORD filter = 0;
    DWORD prefmaxlen = MAX_PREFERRED_LENGTH;
    DWORD entriesread = 0;
    DWORD totalentries = 0;
    DWORD resume_handle = 0;
    NET_API_STATUS nStatus;
    printf("Local users: \n");
    nStatus = NetUserEnum(
            servername,
            level,
            filter,
            (LPBYTE*)&pBuf,
            prefmaxlen,
            &entriesread,
            &totalentries,
            &resume_handle);
    for (int i = 0; i < entriesread; i++) {
        wprintf(L"\t-- %s\n", pBuf->usri0_name);
           pBuf++;
    }
    if (pBuf != NULL)
    {
        NetApiBufferFree(pBuf);
        pBuf = NULL;
    }
    fprintf(stderr, "\nTotal of %d entries enumerated\n", totalentries);

    return 0;
}