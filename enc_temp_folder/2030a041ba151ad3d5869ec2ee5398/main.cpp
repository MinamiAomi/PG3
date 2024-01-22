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
int map[mapHeight][mapWidth] = {};
std::mutex printLock;

void SafePrint(const std::string& str) {
    std::lock_guard<std::mutex> lock(printLock);
    std::cout << str << std::endl;
}

enum class TaskState {
    Stanby,
    Running,
    Completed,
    NotFound
};

class TaskQueue {
public:

    TaskQueue() : thread_([this]() { WorkLoop(); }), unfinishedTaskCount_(0), nextTaskHandle_(0), exit_(false) {}

    int Push(std::function<void()> task) {
        std::lock_guard<std::mutex> lock(queueMutex_);
        unfinishedTaskCount_++;
        int resultHandle = nextTaskHandle_++;
        SetTaskState(resultHandle, TaskState::Stanby);
        queue_.push(std::make_pair(resultHandle, task));
        cond_.notify_all();
        return  resultHandle;
    }

    void Terminate() {
        exit_ = true;
        cond_.notify_all();
        thread_.join();
    }

    int GetUnfinishedTaskCount() const { return unfinishedTaskCount_; }

    bool CompletedAll() { return unfinishedTaskCount_ <= 0; }

    TaskState GetTaskState(int handle) {
        std::lock_guard<std::mutex> lock(mapMutex_);
        if (taskStateMap_.contains(handle)) {
            return taskStateMap_[handle];
        }
        return TaskState::NotFound;
    }

private:
    void WorkLoop() {
        std::unique_lock<std::mutex> uniqueLook(condMutex_);
        while (!exit_) {
            if (queue_.empty()) {
                cond_.wait(uniqueLook, [this]() { return !queue_.empty() || exit_; });
            }
            else {
                auto task = TaskPop();
                SetTaskState(task.first, TaskState::Running);
                task.second();
                SetTaskState(task.first, TaskState::Completed);
                unfinishedTaskCount_--;
            }
        }
    }

    void SetTaskState(int handle, TaskState taskState) {
        std::lock_guard<std::mutex> lock(mapMutex_);
        taskStateMap_[handle] = taskState;
    }

    std::pair<int, std::function<void()>> TaskPop() {
        std::lock_guard<std::mutex> lock(queueMutex_);
        auto task = queue_.front();
        queue_.pop();
        return task;
    }

    std::thread thread_;
    std::queue<std::pair<int, std::function<void()>>> queue_;
    std::condition_variable cond_;
    std::mutex condMutex_;
    std::mutex queueMutex_;
    std::mutex mapMutex_;
    std::unordered_map<int, TaskState> taskStateMap_;
    int unfinishedTaskCount_;
    int nextTaskHandle_;
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

    int loadMapTaskHandle = taskQueue.Push(LoadMap);
    int loadMapTaskHandle2 = taskQueue.Push(LoadMap);

    while (true) {
        if (taskQueue.GetTaskState(loadMapTaskHandle) == TaskState::Stanby) {
            SafePrint("TaskState : Stanby");

        }
        else if (taskQueue.GetTaskState(loadMapTaskHandle) == TaskState::Running) {
            SafePrint("TaskState : Running");

        }
        else if (taskQueue.GetTaskState(loadMapTaskHandle) == TaskState::Completed) {
            SafePrint("TaskState : Completed");
        }

        if (taskQueue.GetTaskState(loadMapTaskHandle2) == TaskState::Stanby) {
            SafePrint("TaskState2 : Stanby");

        }
        else if (taskQueue.GetTaskState(loadMapTaskHandle2) == TaskState::Running) {
            SafePrint("TaskState2 : Running");

        }
        else if (taskQueue.GetTaskState(loadMapTaskHandle2) == TaskState::Completed) {
            SafePrint("TaskState2 : Completed");
        }
    
        if (taskQueue.CompletedAll()) {
            break;
        }
    }

    taskQueue.Terminate();

    PrintMap();

    std::cout << std::endl << "このプログラムは終了しました。" << std::endl;

    (void)std::getchar();
    return 0;
}