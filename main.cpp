#include <iostream>
#include <string>

template<class T>
const T& Min(const T& a, const T& b) {
    return a < b ? a : b;
}

template<class T>
void PrintMin(const T& a, const T& b) {
    // Min<T>(a, b) : result
    std::string str("Min<");
    str += typeid(T).name() + ">(" + std::to_string(a) + ", " + std::to_string(b) + ") : ";
    std::cout << str << Min(a, b) << std::endl;
}

template<>
void PrintMin<char>(const char& a, const char& b) {
    std::cout << "”ŽšˆÈŠO‚Ío—Í‚Å‚«‚Ü‚¹‚ñB" << std::endl;
}


int main() {

    PrintMin<int>(2, 3);
    PrintMin<float>(2.0f, 3.0f);
    PrintMin<double>(2.0, 3.0);
    PrintMin<char>(2, 3);


    (void)std::getchar();
    return 0;
}