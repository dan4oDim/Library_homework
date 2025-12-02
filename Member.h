#pragma once
#include <string>
#include <stdexcept>
#include <iostream> 
class Member {
private:
    std::string name;
    std::string memberId;
    int yearJoined;

public:
    // Конструктор по подразбиране
    Member() : name(""), memberId(""), yearJoined(2000) {}

    // Параметризиран конструктор (с валидация)
    Member(const std::string& n, const std::string& id, int yj) : name(n), memberId(id), yearJoined(yj) {
        if (memberId.empty()) {
            throw std::invalid_argument("Member ID cannot be empty.");
        }
    }

    // Getters
    std::string getMemberId() const { return memberId; }

    // to_string() const
    std::string to_string() const {
        return "Member: " + name + " (ID: " + memberId + ", Joined: " + std::to_string(yearJoined) + ")";
    }
};