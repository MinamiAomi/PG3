#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <functional>

void SetTimeout(std::function<void()> func, std::chrono::seconds seconds) {
    std::this_thread::sleep_for(seconds);
    func();
}

int main() {

    // シード値生成器
    std::random_device seedGenerator;
    // 乱数生成器
    std::mt19937 randomGenerator(seedGenerator());

    int input = 0;

    // ダイスの結果を表示
    std::function PrintDice = [&]() {
        int dice = std::uniform_int_distribution<int>(1, 6)(randomGenerator);
        std::cout << "答えは : " << dice << std::endl;

        if (dice % 2 == 0) {
            std::cout << "偶数です。" << std::endl;
        }
        else {
            std::cout << "奇数です。" << std::endl;
        }

        if ((dice % 2) == (input % 2)) {
            std::cout << "正解です。" << std::endl;
        }
        else {
            std::cout << "不正解です。" << std::endl;
        }
    };

    while (true) {
        std::cout << "終了 : 0, 奇数 : 1, 偶数 : 2 を入力してください。" << std::endl;
        std::cin >> input;
        // 0の場合は終了
        if (input == 0) {
            std::cout << "終了します。" << std::endl;
            break;
        }
        // 0,1,2以外の場合はもう一度聞く
        if (input < 0 || input > 2) {
            continue;
        }

        SetTimeout(PrintDice, std::chrono::seconds(3));

        std::cout << std::endl;
    }


    (void)std::getchar();
    return 0;
}