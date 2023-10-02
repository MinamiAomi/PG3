#include <iostream>
#include <string>


int CalcSalaryGeneral(int hours) {
    const int kHourlySalary = 1072;
    if (hours <= 0) {
        return 0;
    }
    return kHourlySalary * hours;
}

int SalaryRecursiveFunc(int horus, int salary) {
    if (horus <= 1) {
        return salary;
    }
    return salary + SalaryRecursiveFunc(--horus, salary * 2 - 50);
}

int CalcSalaryRecursive(int hours) {
    const int kBaseSalary = 100;
    if (hours <= 0) {
        return 0;
    }
    return SalaryRecursiveFunc(hours, kBaseSalary);
}

int main() {

    for (int i = 0; i <= 10; ++i) {
        std::cout << i << "時間" << std::endl;
        int genreal = CalcSalaryGeneral(i);
        int recursive = CalcSalaryRecursive(i);
        std::cout << "一般的な給料形態 : " << genreal << std::endl;
        std::cout << "再起的な給料形態 : " << recursive << std::endl;
        if (recursive > genreal) {
            std::cout << "再起的な給料形態のほうが給料が高い" << std::endl;
        }
        else {
            std::cout << "一般的な給料形態のほうが給料が高い" << std::endl;
        }
        std::cout << std::endl;
    }


    (void)std::getchar();
    return 0;
}