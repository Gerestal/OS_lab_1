#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

struct employee {
    int num;           
    char name[10];     
    double hours;      
};

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <output-file> <record-count>\n";
        return 1;
    }

    const char* filename = argv[1];
    int recordCount = atoi(argv[2]);

    if (recordCount <= 0) {
        cerr << "Invalid record count: " << argv[2] << "\n";
        return 2;
    }

    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Cannot open file for writing: " << filename << "\n";
        return 3;
    }

    for (int i = 0; i < recordCount; ++i) {
        employee emp;
        string tmp;

        cout << "Enter information about employee number " << (i + 1) << "\n";

        cout << "Employee identification number: ";
        cin >> emp.num;

        cout << "Employee's name: ";
        cin >> tmp;
        strncpy_s(emp.name, sizeof(emp.name), tmp.c_str(), _TRUNCATE);
        emp.name[sizeof(emp.name) - 1] = '\0'; 

        cout << "Number of working hours: ";
        cin >> emp.hours;

        fout.write(reinterpret_cast<const char*>(&emp), sizeof(emp));
        if (!fout) {
            cerr << "Write error on record " << (i + 1) << "\n";
            return 4;
        }
    }

    fout.close();
    cout << "Done. Wrote " << recordCount << " records into \"" << filename << "\"\n";
    return 0;
}

