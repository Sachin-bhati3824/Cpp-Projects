#include "PythonRunner.h"
#include <windows.h>

void run_python_hidden(const std::string& command)
{
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    char cmd[1024];
    strcpy(cmd, command.c_str());

    CreateProcess(NULL, cmd, NULL, NULL,
                  FALSE, CREATE_NO_WINDOW,
                  NULL, NULL, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
void run_cmd_and_wait(const std::string& command)
{
    std::string cmd = "cmd.exe /c " + command;
    // /k keeps window open
    // use /c later for release

    STARTUPINFO si{};
    PROCESS_INFORMATION pi{};

    si.cb = sizeof(si);

    char* cmdline = _strdup(cmd.c_str());

    if(CreateProcess(
        NULL,
        cmdline,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi))
    {
        // WAIT HERE
        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    free(cmdline);
}