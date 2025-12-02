#pragma once
#include <string>
#include <stdexcept>

class Author {
private:
    std::string name;
    int birthYear;

public:
    // Конструктор по подразбиране
    Author() : name("Unknown"), birthYear(1900) {}

    // Параметризиран конструктор
    Author(const std::string& n, int by) : name(n), birthYear(by) {}

    // Getters (const-коректност)
    std::string getName() const { return name; }

    // Setter с валидиране
    void setBirthYear(int year) {
        if (year < 1850 || year > 2025) {
            throw std::invalid_argument("Birth year must be between 1850 and 2025.");
        }
        birthYear = year;
    }

    // to_string() const
    std::string to_string() const {
        return "Author: " + name + " (Born: " + std::to_string(birthYear) + ")";
    }
};