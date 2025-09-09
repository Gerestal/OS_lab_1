#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>

struct Employee {
    int id;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: Reporter <input_binary_file> <output_report_file> <hourly_rate>\n";
        return 1;
    }

    const char* inputFileName = argv[1];
    const char* outputFileName = argv[2];
    double hourlyRate = std::stod(argv[3]);

    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile) {
        std::cerr << "Error opening output file.\n";
        return 1;
    }

    
    outputFile << "Report on the \"" << inputFileName << "\" file\n";
    outputFile << "Number Name Hours Payment\n";

    
    Employee emp;
    while (inputFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        double salary = emp.hours * hourlyRate;
        outputFile << emp.id << " "
            << emp.name << " "
            << emp.hours << " "
            << std::fixed << std::setprecision(2) << salary << "\n";
    }

    inputFile.close();
    outputFile.close();

   /* std::cout << "Отчет успешно создан: " << outputFileName << "\n";*/
    return 0;
}
