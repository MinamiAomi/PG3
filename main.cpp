#include <iostream>
#include <string>
#include <chrono>

int main() {

    std::chrono::microseconds copyTime;
    std::chrono::microseconds moveTime;

    {
        std::string a(100000000, 'a');
        std::chrono::system_clock::time_point ref = std::chrono::system_clock::now();
        std::string copy = a;
        copyTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - ref);
    }

    {
        std::string a(100000000, 'a');
        std::chrono::system_clock::time_point ref = std::chrono::system_clock::now();
        std::string move = std::move(a);
        moveTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - ref);
    }

    std::cout << "100,000文字を移動とコピーで比較しました。" << std::endl;
    std::cout << "コピー：" << copyTime << std::endl;
    std::cout << "移動：" << moveTime  << std::endl;


    std::cout << std::endl << "このプログラムは終了しました。" << std::endl;

    (void)std::getchar();
    return 0;
}