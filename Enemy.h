#pragma once

#include <string>

class Enemy {
public:
    enum class Behavior {
        Melee,
        Shoot,
        Leave
    };

    void Initialize(const std::string& name);
    void Update();

private:
    static void (Enemy::* s_behaviorTable[])();

    void Melee();
    void Shoot();
    void Leave();

    std::string m_name;
    Behavior m_behavior;
};

