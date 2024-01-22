#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>

const char mapFile[] = "map.csv";
const int mapWidth = 26;
const int mapHeight = 12;
std::mutex printLock;
int map[mapHeight][mapWidth] = {};

void SafePrint(const std::string& str) {
    std::lock_guard<std::mutex> lock(printLock);
    std::cout << str << std::endl;
}

class TaskQueue {
public:

    TaskQueue() : thread_([this]() { WorkLoop(); }), unfinishedTaskCount_(0), exit_(false) {}

    void Push(std::function<void()> task) {
        std::lock_guard<std::mutex> lock(queueMutex_);
        unfinishedTaskCount_++;
        queue_.push([this, task]() { task(); unfinishedTaskCount_--; });
        cond_.notify_all();
    }

    void Terminate() {
        exit_ = true;
        cond_.notify_all();
        thread_.join();
    }

    int GetUnfinishedTaskCount() const { return unfinishedTaskCount_; }

    bool CompletedAll() { return unfinishedTaskCount_ > 0; }

private:
    void WorkLoop() {
        std::unique_lock<std::mutex> uniqueLook(condMutex_);
        while (!exit_) {
            if (queue_.empty()) {
                cond_.wait(uniqueLook, [this]() { return !queue_.empty() || exit_; });
            }
            else {
                auto task = queue_.front();
                queue_.pop();
                task();
            }
        }
    }

    std::function<void()> TaskPop() {
        std::lock_guard<std::mutex> lock(queueMutex_);
        auto task = queue_.front();
        queue_.pop();
        return task;
    }

    std::thread thread_;
    std::queue<std::function<void()>> queue_;
    std::condition_variable cond_;
    std::mutex condMutex_;
    std::mutex queueMutex_;
    int unfinishedTaskCount_;
    bool exit_;
};

std::vector<std::string> Split(std::string& input, char delimiter) {
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;
    while (std::getline(stream, field, delimiter)) {
        result.emplace_back(field);
    }
    return result;
}

void LoadMap() {
    SafePrint(std::string("Loading ") + mapFile);
    std::ifstream file(mapFile);
    std::string line;
    int x = 0, y = 0;
    while (std::getline(file, line)) {
        std::vector<std::string> splitLine = Split(line, ',');
        for (const auto& ele : splitLine) {
            map[y][x] = std::stoi(ele);
            x++;
        }
        x = 0;
        y++;
    }
    SafePrint("Loading completed");
}

void PrintMap() {
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            if (map[y][x] == 0) {
                std::cout << " ";
            }
            else {
                std::cout << "*";
            }
        }
        std::cout << std::endl;
    }
}

int main() {

    TaskQueue taskQueue;

    taskQueue.Push(LoadMap);

    while (true) {
        if (taskQueue.CompletedAll()) {
            SafePrint("Now Loading!!");
        }
        else {
            break;
        }
    }

    taskQueue.Terminate();

    PrintMap();

    std::cout << std::endl << "このプログラムは終了しました。" << std::endl;

    (void)std::getchar();
    return 0;
}