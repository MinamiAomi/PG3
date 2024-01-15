#include <iostream>
#include <thread>

void Print(int num) {
    std::printf("thread %d\n", num);
}

int main() {

    std::thread thread1(Print, 1);
    thread1.join();

    std::thread thread2(Print, 2);
    thread2.join();
    
    std::thread thread3(Print, 3);
    thread3.join();
    
    (void)std::getchar();
    return 0;
}