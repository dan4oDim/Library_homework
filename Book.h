#pragma once
#include <string>
#include <stdexcept>
#include "Author.h" 
#include <iostream> 

class Book {
private:
    std::string title;
    Author author;
    int year;
    double price;
    std::string isbn;

    // Статичен член за броене на живите инстанции
    static int totalBooks;

public:
    // --- Rule of 5 Членове ---

    // 1. Конструктор по подразбиране
    Book() : title("No Title"), author(), year(2000), price(0.0), isbn("N/A") {
        totalBooks++;
    }

    // 2. Параметризиран конструктор (списък за инициализация и валидация)
    Book(const std::string& t, const Author& a, int y, double p, const std::string& i)
        : title(t), author(a), year(y), price(p), isbn(i) {
        if (price < 0.0) throw std::invalid_argument("Price cannot be negative.");
        if (year < 1850 || year > 2025) throw std::invalid_argument("Invalid book year.");
        totalBooks++;
    }

    // 3. Копиращ конструктор
    Book(const Book& other)
        : title(other.title), author(other.author), year(other.year), price(other.price), isbn(other.isbn) {
        totalBooks++;
    }

    // 4. Копиращ оператор
    Book& operator=(const Book& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
            year = other.year;
            price = other.price;
            isbn = other.isbn;
        }
        return *this;
    }

    // 5. Деструктор (Намалява статичния брояч)
    ~Book() {
        totalBooks--;
    }

    // Преместващ конструктор и оператор (Rule of 5 - = default е оптимално)
    Book(Book&& other) noexcept = default;
    Book& operator=(Book&& other) noexcept = default;

    // Static getter
    static int getTotalBooks() { return totalBooks; }

    // Getters 
    std::string getTitle() const { return title; }
    const Author& getAuthor() const { return author; }
    std::string getIsbn() const { return isbn; }

    // to_string() const
    std::string to_string() const {
        return "Book: \"" + title + "\" (" + std::to_string(year) + "), ISBN: " + isbn +
               ", Price: " + std::to_string(static_cast<int>(price * 100) / 100.0) +
               ", " + author.to_string();
    }
};

int Book::totalBooks = 0;