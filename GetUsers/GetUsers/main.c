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
    LPUSER_INFO_1 pBuf = NULL;
    LPWSTR servername = NULL;
    DWORD level = 1;
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
    int LUcount = 0;
    LPUSER_INFO_1 pBuf2 = pBuf;
    for (int i = 0; i < entriesread; i++) {
        if (pBuf->usri1_priv == 0) {
            wprintf(L"\t-- %s\n", pBuf->usri1_name);
            LUcount += 1;
        }
        pBuf++;
    }   
    fprintf(stderr, "\nTotal of %d local users enumerated\n", LUcount);
    NetApiBufferFree(pBuf2);
    return 0;
}