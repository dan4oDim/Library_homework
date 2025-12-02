#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

#include "Book.h"
#include "Member.h"
#include "Loan.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;

    bool memberExists(const std::string& memberId) const {
        for (const auto& member : members) {
            if (member.getMemberId() == memberId) return true;
        }
        return false;
    }

public:
    Library() = default;

    void addBook(const Book& b) {
        for (const auto& book : books) {
            if (book.getIsbn() == b.getIsbn()) {
                throw std::invalid_argument("Book with this ISBN already exists.");
            }
        }
        books.push_back(b);
    }

    void addMember(const Member& m) {
        if (memberExists(m.getMemberId())) {
            throw std::invalid_argument("Member with this ID already exists.");
        }
        members.push_back(m);
    }

    bool hasBook(const std::string& isbn) const {
        for (const auto& book : books) {
            if (book.getIsbn() == isbn) return true;
        }
        return false;
    }

    // Проверка дали книгата е налична 
    bool isBookAvailable(const std::string& isbn) const {
        if (!hasBook(isbn)) return false; 

        for (const auto& loan : loans) {
            if (loan.getIsbn() == isbn && !loan.isReturned()) {
                return false; 
            }
        }
        return true;
    }

    bool loanBook(const std::string& isbn, const std::string& memberId, const std::string& start, const std::string& due) {
        if (!hasBook(isbn)) {
            std::cout << "Error: Book with ISBN " << isbn << " not found." << std::endl;
            return false;
        }
        if (!memberExists(memberId)) {
            std::cout << "Error: Member with ID " << memberId << " not found." << std::endl;
            return false;
        }

        if (isBookAvailable(isbn)) {
            try {
                loans.push_back(Loan(isbn, memberId, start, due));
                return true;
            } catch (const std::invalid_argument& e) {
                std::cout << "Error creating loan: " << e.what() << std::endl;
                return false;
            }
        }
        std::cout << "Error: Book with ISBN " << isbn << " is currently not available." << std::endl;
        return false;
    }

    bool returnBook(const std::string& isbn, const std::string& memberId) {
        for (auto& loan : loans) {
            if (loan.getIsbn() == isbn && loan.getMemberId() == memberId && !loan.isReturned()) {
                loan.markReturned();
                return true;
            }
        }
        std::cout << "Error: Active loan for ISBN " << isbn << " and Member " << memberId << " not found." << std::endl;
        return false;
    }

    std::vector<Book> findByAuthor(const std::string& authorName) const {
        std::vector<Book> result;
        for (const auto& book : books) {
            if (book.getAuthor().getName().find(authorName) != std::string::npos) {
                result.push_back(book);
            }
        }
        return result;
    }

    // to_string() const
    std::string to_string() const {
        int activeLoans = 0;
        for (const auto& loan : loans) {
            if (!loan.isReturned()) {
                activeLoans++;
            }
        }

        return "\n--- Library Summary ---\n"
               "Total Books: " + std::to_string(books.size()) + "\n"
               "Total Members: " + std::to_string(members.size()) + "\n"
               "Total Active Loans: " + std::to_string(activeLoans) + "\n"
               "Total Book Instances (Static Check): " + std::to_string(Book::getTotalBooks()) + "\n"
               "-----------------------\n";
    }
    
    const std::vector<Loan>& getLoans() const { return loans; }
};