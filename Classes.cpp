#include "Classes.h"
#include "str.h"
#include <iostream>

using namespace OurString;
using namespace OurClasses;
using namespace std;

//*********************************** Book CLASS IMPLEMENTATION ***********************************
Book::Book() : _title("NULL"), _author("NULL"), _isbn("NULL"), _publicationYear(0), _genre("NULL"), _availability(false) {} // Default constructor
Book::Book(Str title, Str author, Str isbn, short publicationYear, Str genre, bool availability) : _title(title), _author(author), _isbn(isbn), _publicationYear(publicationYear), _genre(genre), _availability(availability) {} // Parameterized constructor

// Setters and getters
void Book::setTitle(Str title) {
    _title = title;
}
Str Book::getTitle() {
    return _title;
}
void Book::setAuthor(Str author) {
    _author = author;
}
Str Book::getAuthor() {
    return _author;
}
void Book::setIsbn(Str isbn) {
    _isbn = isbn;
}
Str Book::getIsbn() {
    return _isbn;
}
void Book::setPublicationYear(short year) {
    _publicationYear = year;
}
short Book::getPublicationYear() {
    return _publicationYear;
}
void Book::setGenre(Str genre) {
    _genre = genre;
}
Str Book::getGenre() {
    return _genre;
}
void Book::setAvailability(bool availability) {
    _availability = availability;
}
bool Book::getAvailability() {
    return _availability;
}

void Book::printData() { // Print the data of the book
    cout << "----------------------Book Info----------------------------\n";
    cout << "Title            : " << _title << endl;
    cout << "Author           : " << _author << endl;
    cout << "ISBN             : " << _isbn << endl;
    cout << "Publication Year : " << _publicationYear << endl;
    cout << "Genre            : " << _genre << endl;
    cout << "Availability     : " << (_availability ? "Available" : "Not available") << endl;
    cout << "-----------------------------------------------------------" << endl;
}
Book::~Book() {} // Destructor

//*********************************** Member CLASS IMPLEMENTATION ***********************************
Member::Member() : _name("NONE"), _id("NONE"), _type("NONE"), _password("NONE"), _fines(0) {} // Default constructor
Member::Member(Str name, Str id, Str type, Str password, vector<Book> checkedOutBooks) : _name(name), _id(id), _type(type), _password(password), _checkedOutBooks(checkedOutBooks) {} // Parameterized constructor
Str Member::getName() {
    return _name;
}
Str Member::getID() {
    return _id;
}
Str Member::getType() {
    return _type;
}
vector<Book> Member::getCheckedOutBooks() {
    return _checkedOutBooks;
}
short Member::getFines() {
    return _fines;
}
void Member::setName(Str name) {
    _name = name;
}
void Member::setID(Str ID) {
    _id = ID;
}
void Member::setType(Str type) {
    _type = type;
}
void Member::setPassword(Str password) {
    _password = password;
}
void Member::addBookToCheckedOutBooks(Book newBook) {
    _checkedOutBooks.push_back(newBook);
}
void Member::setFines(short fines) {
    _fines = fines;
}
Member::~Member() = default;

//*********************************** Loan CLASS IMPLEMENTATION ***********************************
void Loan::viewLoans(Str MemberId, Str isbn, Str BorrowDate, Str DueDate) {
    // Will implement when database is up
}
