#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>

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
        throw runtime_error("Cannot start process: " +
            string(appPath.begin(), appPath.end()));
    }

    
    DWORD waitResult = WaitForSingleObject(pi.hProcess, INFINITE);
    if (waitResult == WAIT_FAILED)
    {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        throw runtime_error("Error waiting for process. Code: " +
            to_string(GetLastError()));
       
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
        cerr << "Couldn't open the file: " << fileName << endl;
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
        cerr << "Couldn't open the file: " << fileName << endl;
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
    try {

        string binFileName;
        int recordCount;

        cout << "Enter the name of the binary file: ";
        cin >> binFileName;
        cout << "Enter the number of employees: ";
        cin >> recordCount;


        wstring creatorPath = L"C:/Users/User/Desktop/я++/ня/x64/Release/ня_1.exe";
        wstring creatorParams = wstring(binFileName.begin(), binFileName.end()) + L" " + to_wstring(recordCount);

        DoProcess(creatorPath, creatorParams);


        cout << "\nThe contents of the binary file:\n";
        PrintFile(binFileName);


        string reportFileName;
        double hourlyRate;

        cout << "\nEnter the name of the report file: ";
        cin >> reportFileName;
        cout << "Enter the payment for the hour of work: ";
        cin >> hourlyRate;


        wstring reporterPath = L"C:/Users/User/Desktop/я++/ня/x64/Release/Reporter.exe";
        wstring reporterParams = wstring(binFileName.begin(), binFileName.end()) + L" " +
            wstring(reportFileName.begin(), reportFileName.end()) + L" " +
            to_wstring(hourlyRate);

        DoProcess(reporterPath, reporterParams);


        cout << "\nReport Content:\n";
        PrintFile2(reportFileName);

        _cputs("\nThe work is completed.\n");
        _getch();
       
    }
    catch (const ios_base::failure& io_err) {
        cerr << "I/O error: " << io_err.what() << endl;
        return 1;
    }
    catch (const invalid_argument& arg_err) {
        cerr << "Invalid argument: " << arg_err.what() << endl;
        return 2;
    }
    catch (const out_of_range& range_err) {
        cerr << "Value out of range: " << range_err.what() << endl;
        return 3;
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 4;
    }
    return 0;
}
