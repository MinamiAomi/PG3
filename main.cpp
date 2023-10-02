#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <functional>

int main() {

    // シード値生成器
    std::random_device seedGenerator;
    // 乱数生成器
    std::mt19937 randomGenerator(seedGenerator());

    // ダイスを振る関数
    std::function RollDice = [&]() {
        return std::uniform_int_distribution<int>(1, 6)(randomGenerator);
    };

    while (true) {
        std::cout << "終了 : 0, 奇数 : 1, 偶数 : 2 を入力してください。" << std::endl;
        int input = 0;
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

        // 3秒待つ
        const int kWaitTime = 3;
        for (int i = 0; i < kWaitTime; ++i) {
            std::cout << ". ";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // コールバック関数を呼び出す
        int answer = RollDice();
        std::cout << "答えは : " << answer << std::endl;
        if (answer % 2 == 0) {
            std::cout << "偶数です。" << std::endl;
        }
        else {
            std::cout << "奇数です。" << std::endl;
        }

        std::cout << std::endl;
    }


    (void)std::getchar();
    return 0;
}