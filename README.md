# Проект: Библиотечна система (Library Management System)

## Описание
Проектът „Библиотечна система" представлява малка C++ система, която моделира работа с книги, членове на библиотека, автори и позиции в библиотеката чрез четири взаимосвързани класа — `Book`, `Member`, `Author`, `Loan` и `Library`.

Той демонстрира прилагането на основни обектно-ориентирани концепции в C++:

- конструктори и деструктори;
- капсулация и достъп чрез getters и setters;
- const-коректност и валидация на данни;
- статични членове и методи;
- работа с вектори и динамични колекции;
- добри ООП практики в реалистичен контекст.

## Структура на проекта
```
homework_library_danonino/
├── Author.h
├── Book.h
├── Loan.h
├── Library.h
├── Member.h
├── README.md
├── main.cpp
└── output/
```

## Компилация и изпълнение
Отворете терминал в директорията `homework_library_danonino/` и изпълнете:

```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o main
```

След това стартирайте програмата:

```bash
./main
```

## Класове

### Клас Author
Представя автор на книга с основни характеристики.

**Членове:**
- `std::string name` — име на автора
- `std::string country` — страна на произход
- `int birth_year` — година на раждане

**Методи:**
- `Author(std::string n, std::string c, int y)` — параметризиран конструктор
- `getName() const` — връща име на автора
- `getCountry() const` — връща страна на произход
- `getBirthYear() const` — връща година на раждане
- `to_string() const` — връща текстово описание на автора

### Клас Book
Представя книга със своите свойства.

**Членове:**
- `std::string title` — заглавие на книгата
- `Author author` — автор на книгата
- `int publication_year` — година на издаване
- `std::string isbn` — ISBN номер
- `bool available` — флаг за налично/заемано

**Методи:**
- `Book(std::string t, Author a, int py, std::string i)` — параметризиран конструктор
- `getTitle() const` — връща заглавието
- `getAuthor() const` — връща информация за автора
- `getISBN() const` — връща ISBN номер
- `isAvailable() const` — проверява дали книгата е налична
- `setAvailable(bool status)` — задава статус на наличност
- `to_string() const` — текстово представяне на книгата

### Клас Member
Представя член на библиотеката.

**Членове:**
- `std::string name` — име на члена
- `int member_id` — уникален идентификатор
- `std::vector<Book>` — списък на заетите книги
- `static int total_members` — брояч на всички членове

**Методи:**
- `Member(std::string n, int id)` — параметризиран конструктор
- `getName() const` — връща име на члена
- `getMemberId() const` — връща идентификатор
- `borrowBook(const Book& b)` — членът заема книга
- `returnBook(const std::string& title)` — членът връща книга
- `getBorrowedBooks() const` — връща списък на заетите книги
- `static getTotal() const` — връща общия брой членове
- `to_string() const` — текстово представяне

### Клас Loan
Представя заем (позиция за заемане на книга).

**Членове:**
- `Book book` — заемана книга
- `Member member` — члена, който заема
- `std::string loan_date` — дата на заемане
- `std::string due_date` — крайна дата за връщане
- `bool returned` — флаг дали е върната

**Методи:**
- `Loan(Book b, Member m, std::string ld, std::string dd)` — конструктор
- `getBook() const` — връща книгата
- `getMember() const` — връща члена
- `isReturned() const` — проверява дали е върната
- `returnBook()` — отбелязва книгата като върната
- `to_string() const` — текстово представяне на позицията

### Клас Library
Представлява библиотеката, която управлява книги, членове и позиции.

**Членове:**
- `std::string name` — име на библиотеката
- `std::vector<Book>` — колекция на всички книги
- `std::vector<Member>` — колекция на всички членове
- `std::vector<Loan>` — колекция на всички позиции

**Методи:**
- `Library(std::string n)` — конструктор
- `addBook(const Book& b)` — добавя книга в библиотеката
- `addMember(const Member& m)` — регистрира нов член
- `borrowBook(int member_id, const std::string& title)` — членът заема книга
- `returnBook(int member_id, const std::string& title)` — членът връща книга
- `getAvailableBooks() const` — връща всички налични книги
- `getMemberLoans(int member_id) const` — връща позициите на член
- `to_string() const` — текстово представяне на библиотеката

## Образователни цели
Проектът има за цел да демонстрира:

- разделение между интерфейс (.h) и имплементация в главния файл;
- използване на конструктори и инициализирани членове;
- валидация и управление на състояние на обекти;
- работа със статични членове за глобално броене;
- прилагане на const-коректност в методите;
- използване на вектори за динамични колекции;
- комбинирането на няколко класа в една система.
