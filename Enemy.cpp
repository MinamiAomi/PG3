#include "Enemy.h"

#include <iostream>

void (Enemy::* Enemy::s_behaviorTable[])() = {
    &Enemy::Melee,
    &Enemy::Shoot,
    &Enemy::Leave
};

void Enemy::Initialize(const std::string& name) {
    m_name = name;
    m_behavior = Behavior::Melee;
}

void Enemy::Update() {
    std::cout << m_name << "の行動 : ";
    (this->*s_behaviorTable[static_cast<size_t>(m_behavior)])();
    std::cout << std::endl;
}

void Enemy::Melee() {
    std::cout << "近接攻撃!!" << std::endl;
    m_behavior = Behavior::Shoot;
}

void Enemy::Shoot() {
    std::cout << "射撃!!" << std::endl;
    m_behavior = Behavior::Leave;
}

void Enemy::Leave() {
    std::cout << "離脱!!" << std::endl;
    m_behavior = Behavior::Melee;
}
