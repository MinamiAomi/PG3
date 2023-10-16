#include <iostream>
#include <thread>
#include <chrono>

#include "Enemy.h"

int main() {

    const unsigned int kEndTurn = 15;
    unsigned int elapsedTurn = 0;

    Enemy enemy;
    enemy.Initialize("メタグロス");

    while (elapsedTurn < kEndTurn) {
        elapsedTurn++;
        std::cout << "現在のターン : " << elapsedTurn << std::endl;

        enemy.Update();

        // 一秒待つ
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << std::endl << "このプログラムは終了しました。" << std::endl;

    (void)std::getchar();
    return 0;
}