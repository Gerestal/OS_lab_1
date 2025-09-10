#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <exception>

using namespace std;


struct Employee {
    int id;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    try {
        if (argc != 4)
            throw runtime_error("Usage: Reporter <input_file> <output_file> <hourly_rate>");

        const char* inputFileName = argv[1];
        const char* outputFileName = argv[2];
        double hourlyRate = stod(argv[3]);  

        ifstream inputFile(inputFileName, ios::binary);
        inputFile.exceptions(ifstream::failbit | ifstream::badbit);

        ofstream outputFile(outputFileName);
        outputFile.exceptions(ofstream::failbit | ofstream::badbit);

        outputFile << "Report on the \"" << inputFileName << "\" file\n";
        outputFile << "Number Name Hours Payment\n";

        Employee emp;
        while (inputFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
            double salary = emp.hours * hourlyRate;
            outputFile
                << emp.id << " "
                << emp.name << " "
                << fixed << setprecision(2) << emp.hours << " "
                << fixed << setprecision(2) << salary << "\n";
        }

        inputFile.close();
        outputFile.close();
    }
    catch (const invalid_argument& e) {
        cerr << "Error: invalid hourly rate – " << e.what() << endl;
        return 2;
    }
    catch (const out_of_range& e) {
        cerr << "Error: hourly rate out of range – " << e.what() << endl;
        return 3;
    }
    catch (const ios_base::failure& e) {
        cerr << "I/O Error: " << e.what() << endl;
        return 4;
    }
    catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
        return 5;
    }

    return 0;
}