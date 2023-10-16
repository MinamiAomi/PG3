#include <iostream>

#include <variant>

template<class T, class U, class W = T>
class  Pair {
public:
    Pair(const T& a, const U& b) :
        a(a), b(b) {
    }

    W Min() {
        return a < b ? static_cast<W>(a) : static_cast<W>(b);
    }

private:
    T a;
    U b;
};

int main() {


    Pair intAndInt(10, 9);
    Pair intAndFloat(10, 9.0f);
    Pair intAndDouble(10, 9.0);

    Pair floatAndFloat(10.0f, 9.0f);
    Pair floatAndDouble(10.0f, 9.0);

    Pair doubleAndDouble(10.0, 9.0);

    std::cout << intAndInt.Min() << std::endl;
    std::cout << intAndFloat.Min() << std::endl;
    std::cout << intAndDouble.Min() << std::endl;

    std::cout << floatAndFloat.Min() << std::endl;
    std::cout << floatAndDouble.Min() << std::endl;

    std::cout << doubleAndDouble.Min() << std::endl;

    std::cout << std::endl << "このプログラムは終了しました。" << std::endl;

    (void)std::getchar();
    return 0;
}