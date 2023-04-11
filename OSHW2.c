#include <Windows.h>
#include <stdio.h>

int main(void) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    TCHAR CommandLine[] = TEXT("C:\\Program Files\\WindowsApps\\Microsoft.Paint_11.2301.22.0_x64__8wekyb3d8bbwe\\PaintApp\\mspaint.exe");

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL,               // No Module name (use command line)
        CommandLine,   // Command Line   
        NULL,                           // Process handle not inheritable
        NULL,                           // Thread handle not inheritable
        FALSE,                           // Set handle inheritance to False
        0,                              // No creation flags
        NULL,                           // Use parent's environment block
        NULL,                           // Use parent's starting dircetory
        &si,                           // Pointer to STARTUPINFO structure
        &pi                              // Pointer to PROCESS_INFOMATION structure
    )) {
        printf("CreateProcess failed (%d). \n", GetLastError());
        return -1;
    }

    // Wait Until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles;
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}