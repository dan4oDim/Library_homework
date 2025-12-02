#include <iostream>
#include <stdexcept>
#include <vector>
#include "Library.h" 

using namespace std;

int main() {
    try {
        Library lib;

        cout << "--- 1. Initialization and Author/Book to_string ---\n";
        Author a1{"Ivan Vazov", 1850};
        Author a2{"Elin Pelin", 1877};
        
        try {
           
            Book b1{"Pod igoto", a1, 1894, 25.50, "ISBN-001"};
            Book b2{"Nemili-nedragi", a1, 1900, 18.90, "ISBN-002"};
            Book b3{"Geracite", a2, 1911, 15.00, "ISBN-003"};
            
            lib.addBook(b1);
            lib.addBook(b2);
            lib.addBook(b3);

            cout << b1.to_string() << endl;
            cout << b3.to_string() << endl;

        } catch (const std::invalid_argument& e) {
            cout << "Initialization Error: " << e.what() << endl;
        }

        cout << "\n--- 2. Member and Library Setup ---\n";
        try {
            lib.addMember(Member{"Petar Petrov", "M001", 2023});
            lib.addMember(Member{"Maria Koleva", "M002", 2024});
            
        } catch (const std::invalid_argument& e) {
            cout << "Member Error: " << e.what() << endl;
        }
        cout << lib.to_string();


        cout << "\n--- 3. Loan/Return Logic ---\n";

        // Първи заем (успешен)
        cout << "Is ISBN-001 Available? " << boolalpha << lib.isBookAvailable("ISBN-001") << endl;
        if (lib.loanBook("ISBN-001", "M001", "2025-11-03", "2025-11-17")) {
            cout << "Loan created successfully for ISBN-001.\n";
        }

        // Опит за повторен заем 
        cout << "Is ISBN-001 Available now? " << boolalpha << lib.isBookAvailable("ISBN-001") << endl;
        if (!lib.loanBook("ISBN-001", "M002", "2025-11-04", "2025-11-18")) {
            cout << "Second loan attempt for ISBN-001 failed as expected.\n";
        }

        // Връщане
        if (lib.returnBook("ISBN-001", "M001")) {
            cout << "ISBN-001 returned by M001.\n";
        }
        cout << "Is ISBN-001 Available after return? " << boolalpha << lib.isBookAvailable("ISBN-001") << endl;

        cout << "\n--- 4. Loan Overdue Check ---\n";
        if (lib.loanBook("ISBN-002", "M002", "2024-10-01", "2024-10-15")) {
             cout << "Loan created for ISBN-002 (due 2024-10-15).\n";
        }
        
        // Проверка за просрочие на датата
        string today = "2025-01-01";
        cout << "Checking overdue on " << today << ":\n";
        for (const auto& loan : lib.getLoans()) {
            if (!loan.isReturned()) {
                cout << "Loan for " << loan.getIsbn() << " is overdue? " << boolalpha 
                     << loan.isOverdue(today) << endl;
            }
        }

        cout << "\n--- 5. findByAuthor Demo ---\n";
        vector<Book> vazov_books = lib.findByAuthor("Vazov");
        cout << "Found " << vazov_books.size() << " books by Vazov:\n";
        for (const auto& bk : vazov_books) {
            cout << " -> " << bk.getTitle() << endl;
        }

        cout << "\n--- 6. Static Count Check (Rule of 5) ---\n";
        cout << "Current Total Books (Static): " << Book::getTotalBooks() << endl;

        Book b_copy;
        {
            Book b_temp{"Temp Book", a2, 2020, 10.0, "TEMP-001"};
            cout << "Total Books after creating temp: " << Book::getTotalBooks() << endl;
            b_copy = b_temp; 
        }
        cout << "Total Books after temp scope exit (should be same as before): " << Book::getTotalBooks() << endl;
        
        cout << "\n--- 7. Final Summary ---\n";
        cout << lib.to_string();

    } catch (const std::exception& e) {
        cerr << "Unhandled Exception: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "An unknown error occurred." << endl;
        return 1;
    }
    return 0;
}