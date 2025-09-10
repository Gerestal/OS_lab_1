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
    try {

        if (argc != 3) {
            throw invalid_argument(
                string("Usage: ") + argv[0] + " <output-file> <record-count>");
        }

        const char* filename = argv[1];
        int recordCount = stoi(argv[2]);

        if (recordCount <= 0) {
            throw invalid_argument(
                string("Invalid record count: ") + argv[2]);
        }

        ofstream fout(filename, ios::binary);
        fout.exceptions(ofstream::failbit | ofstream::badbit);

        for (int i = 0; i < recordCount; ++i) {
            employee emp;
            string tmp;

            cout << "Enter information about employee number " << (i + 1) << "\n";

            cout << "Employee identification number: ";
            if (!(cin >> emp.num)) {
                throw runtime_error("Invalid input for employee id");
            }

            cout << "Employee's name: ";
            if (!(cin >> tmp)) {
                throw runtime_error("Invalid input for employee name");
            }
            strncpy_s(emp.name, sizeof(emp.name), tmp.c_str(), _TRUNCATE);
            emp.name[sizeof(emp.name) - 1] = '\0';

            cout << "Number of working hours: ";
            if (!(cin >> emp.hours))
                throw runtime_error("Invalid input for working hours");

            fout.write(reinterpret_cast<const char*>(&emp), sizeof(emp));
        }

        fout.close();
        cout << "Done. Wrote " << recordCount << " records into \"" << filename << "\"\n";
      
    }
    catch (const invalid_argument& e) {
        cerr << "Argument error: " << e.what() << endl;
        return 1;
    }
    catch (const out_of_range& e) {
        cerr << "Out of range error: " << e.what() << endl;
        return 2;
    }
    catch (const ios_base::failure& e) {
        cerr << "I/O error: " << e.what() << endl;
        return 3;
    }
    catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
        return 4;
    }
    return 0;
}

