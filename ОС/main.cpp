#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


struct employee {
    int num;
    char name[10];
    double hours;
    
};

struct employee2 {
    int num;
    char name[10];
    double hours;
    double salary;
};


bool DoProcess(const wstring& appPath, const wstring& params)
{
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    
    wstring cmdLine = L"\"" + appPath + L"\" " + params;

    if (!CreateProcessW(
        appPath.c_str(),         
        &cmdLine[0],             
        NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE,
        NULL, NULL,
        &si, &pi))
    {
        wcerr << L"Ошибка запуска процесса: " << appPath << endl;
        return false;
    }

    
    DWORD waitResult = WaitForSingleObject(pi.hProcess, INFINITE);
    if (waitResult == WAIT_FAILED)
    {
        cerr << "Ошибка ожидания процесса. Код: " << GetLastError() << endl;
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return false;
    }

    
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return true;
}


void PrintFile(const string& fileName)
{
    employee emp;
    ifstream file(fileName, ios::binary);
    if (!file)
    {
        cerr << "Не удалось открыть файл: " << fileName << endl;
        return;
    }
    
    int index = 1;
    while (file.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        cout << "\nEmployee " << index++ << endl;
        cout << "Number: " << emp.num << endl;
        cout << "Name: " << emp.name << endl;
        cout << "Hours: " << emp.hours << endl;
    }
    file.close();

    cout << endl;
}

void PrintFile2(const string& fileName)
{
    employee2 emp;
    ifstream file(fileName);
    if (!file)
    {
        cerr << "Не удалось открыть файл: " << fileName << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
    cout << endl;
}

int main()
{

    setlocale (LC_ALL, "Russian");

    
    string binFileName;
    int recordCount;

    cout << "Enter the name of the binary file: ";
    cin >> binFileName;
    cout << "Enter the number of entries: ";
    cin >> recordCount;

    
    wstring creatorPath = L"C:/Users/User/Desktop/С++/ОС/x64/Release/ОС_1.exe";
    wstring creatorParams = wstring(binFileName.begin(), binFileName.end()) + L" " + to_wstring(recordCount);

    if (!DoProcess(creatorPath, creatorParams))
    {
        _cputs("Creator startup Error.\n");
        return 0;
    }

    
    cout << "\nThe contents of the binary file:\n";
    PrintFile(binFileName);

  
    string reportFileName;
    double hourlyRate;

    cout << "\nEnter the name of the report file: ";
    cin >> reportFileName;
    cout << "Enter the payment for the hour of work: ";
    cin >> hourlyRate;

    
    wstring reporterPath = L"C:/Users/User/Desktop/С++/ОС/x64/Release/Reporter.exe";
    wstring reporterParams = wstring(binFileName.begin(), binFileName.end()) + L" " +
        wstring(reportFileName.begin(), reportFileName.end()) + L" " +
        to_wstring(hourlyRate);

    if (!DoProcess(reporterPath, reporterParams))
    {
        _cputs("Reporter launch error.\n");
        return 0;
    }

    
    cout << "\nReport Content:\n";
    PrintFile2(reportFileName);

    _cputs("\nThe work is completed.\n");
    _getch();
    return 0;
}
