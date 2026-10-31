#pragma once
#include "pch.h"
#include <windows.h>
#include <filesystem>
#include <iostream>
#include <string>

bool RunBatch(const std::string& batchFilePathAndName, const std::vector<std::string>& args, bool closeTerminalOnFinish = true, bool relativePathing = true, const std::string& workingDirectory = "") {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    std::string commandLine = "cmd.exe ";
    commandLine += ((closeTerminalOnFinish) ? "/C " : "/K ");
    commandLine += "\"\"";
    if (!relativePathing) { commandLine += std::filesystem::absolute(batchFilePathAndName).string(); }
    else { commandLine += batchFilePathAndName; }
    commandLine += "\"";
    for (const std::string& arg : args) { commandLine += " \"" + arg + "\""; }
    commandLine += "\"";

    if (CreateProcessA(
        NULL,                   // Application name
        commandLine.data(),     // Command line arguments
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        0,                      // No creation flags
        NULL,                   // Use parent's environment block
        workingDirectory.empty() ? NULL : workingDirectory.c_str(),         // Use parent's starting directory 
        &si,                    // Pointer to STARTUPINFO structure
        &pi                     // Pointer to PROCESS_INFORMATION structure
    ))
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return true;
    }
    else
    {
        std::cout << "ERROR: RunBatch: CreateProcess failed with error: " << GetLastError() << "\n";
        return false;
    }
}