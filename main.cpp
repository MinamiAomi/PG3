#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <regex>
#include <sstream>

struct StudentNumber {
    std::string emailAddress;
    int year;
    int local;
};

std::vector<std::string> Split(const std::string& src, const std::string& delim) {
    std::vector<std::string> dest;
    std::string::size_type length = src.length();

    for (std::string::size_type i = 0, n = 0; i < length; i = n + 1) {
        n = src.find_first_of(delim, i);
        if (n == std::string::npos) { n = length; }
        dest.emplace_back(src.substr(i, n - i));
    }
    return dest;
}

std::vector<StudentNumber> LoadStudentNumbers(const std::filesystem::path& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return {};
    }
    std::vector<std::string> splitStrings = Split(std::string(std::istreambuf_iterator(file), std::istreambuf_iterator<char>()), ",");
    file.close();

    std::vector<StudentNumber> studentNumbers;
    studentNumbers.reserve(splitStrings.size());
    
    for(const auto& string : splitStrings) {

        std::smatch smatch;
        if (!std::regex_search(string, smatch, std::regex(R"(k(\d+)g(\d+)@g.neec.ac.jp)"))) { continue; }
        
        studentNumbers.emplace_back(smatch[0], std::stoi(smatch[1]), std::stoi(smatch[2]));
    }

    return studentNumbers;
}

int main() {

    auto studentNumbers = LoadStudentNumbers("PG3_05_02.txt");

    std::sort(studentNumbers.begin(), studentNumbers.end(), 
        [](const StudentNumber& a, const StudentNumber& b) {
            return a.year * 10000 + a.local < b.year * 10000 + b.local;
        });

    for (const auto& studentNumber : studentNumbers) {
        std::cout << std::setw(2) << studentNumber.year << " " << std::setw(4) << studentNumber.local << " " << studentNumber.emailAddress << std::endl;
    }

    std::cout << std::endl << "このプログラムは終了しました。" << std::endl;

    (void)std::getchar();
    return 0;
}