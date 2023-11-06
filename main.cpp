#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <functional>

// シード値生成器
std::random_device g_seedGenerator;
// 乱数生成器
std::mt19937 g_randomGenerator(g_seedGenerator());

// サイコロを振る
int RollDice() {
    return std::uniform_int_distribution<int>(1, 6)(g_randomGenerator);
}

void DispResult(int input) {
    int answer = RollDice();
    std::cout << "答えは : " << answer << std::endl;

    if (answer % 2 == input % 2) {
        std::cout << "正解です。" << std::endl;
    }
    else {
        std::cout << "不正解です。" << std::endl;
    }
}

void SetTimeout(std::function<void()> func, size_t second) {
    std::this_thread::sleep_for(std::chrono::seconds(second));
    func();
}

int main() {


    std::cout << "終了 : 0, 奇数 : 1, 偶数 : 2 を入力してください。" << std::endl;
    int input = 0;
    std::cin >> input;

    // 0の場合は終了
    if (input == 0) {
        std::cout << "終了します。" << std::endl;
    }
    else {
        // 3秒後に実行
        SetTimeout([input]() { DispResult(input); }, 3);

        std::cout << std::endl;
    }


    (void)std::getchar();
    return 0;
}