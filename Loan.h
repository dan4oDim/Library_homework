#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

bool is_date_earlier_local(const std::string& date1, const std::string& date2) {
    return date1 < date2;
}

class Loan {
private:
    std::string isbn;
    std::string memberId;
    std::string startDate;
    std::string dueDate;
    bool returned;

public:
    // Параметризиран конструктор (с валидация)
    Loan(const std::string& i, const std::string& m, const std::string& start, const std::string& due)
        : isbn(i), memberId(m), startDate(start), dueDate(due), returned(false) {
        if (is_date_earlier_local(due, start)) {
            throw std::invalid_argument("Due date must be on or after start date.");
        }
    }

    // Getters
    std::string getIsbn() const { return isbn; }
    std::string getMemberId() const { return memberId; }
    bool isReturned() const { return returned; }

    // Методи
    void markReturned() {
        returned = true;
    }

    bool isOverdue(const std::string& today) const {
        return !returned && is_date_earlier_local(dueDate, today);
    }

    // to_string() const
    std::string to_string() const {
        std::string status = returned ? "Returned" : "Active";
        return "Loan: Book " + isbn + " to Member " + memberId +
               " (Start: " + startDate + ", Due: " + dueDate + ", Status: " + status + ")";
    }
};