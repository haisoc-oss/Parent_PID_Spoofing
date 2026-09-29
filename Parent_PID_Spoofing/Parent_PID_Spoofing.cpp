// Parent_PID_Spoofing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <iostream>

/*DWORD FindProcessPid(const char* procname)
{
    PROCESSENTRY32 pe32 = { 0 };
    pe32.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // takes a snapshot of all the processes running in the system
    if (hSnapshot)
    {
        if (Process32First(hSnapshot, &pe32)) // from the snapshot of the processes, we extract the process name
        {
            do
            {
                if (strcmp(pe32.szExeFile, procname) == 0) // compares the process name, with our user supplied name
                {
                    return pe32.th32ProcessID; // if its the same, return the process id
                }
            } while (Process32Next(hSnapshot, &pe32));
            CloseHandle(hSnapshot);
        }
    }

    return -1; // returns negative one if the process is not found
}
*/

int main()
{
    STARTUPINFOEXA si;
    SIZE_T attribute_size;
    const char* ProcessPath = "E:\\tool\\lastdance.exe";
    PPROCESS_INFORMATION Process_info = new PROCESS_INFORMATION();
    ZeroMemory(&si, sizeof(STARTUPINFOEXA));


    HANDLE Parent_proc_handle = OpenProcess(MAXIMUM_ALLOWED,FALSE,27556);

    InitializeProcThreadAttributeList(NULL, 1, 0, &attribute_size);
    si.lpAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), 0, attribute_size);
    InitializeProcThreadAttributeList(si.lpAttributeList,1,0,&attribute_size);
    
    UpdateProcThreadAttribute(si.lpAttributeList,0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &Parent_proc_handle, sizeof(HANDLE),NULL,NULL);
    si.StartupInfo.cb = sizeof(STARTUPINFOEXA);
    CreateProcessA(ProcessPath, 0, 0, 0, TRUE, EXTENDED_STARTUPINFO_PRESENT, 0, 0, &si.StartupInfo, Process_info);



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
