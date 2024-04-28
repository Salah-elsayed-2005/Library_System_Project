#ifndef LIBRARY_SYSTEM_PROJECT_DATABASEMANAGER_H
#define LIBRARY_SYSTEM_PROJECT_DATABASEMANAGER_H

#include "sqlite3.h"
#include <string>
#include "Str.h"
#include "Book.h"
#include "User.h"

using namespace OurBook;

// External vectors to hold references to books, users, and loans that can be accessed globally
extern vector<Book*> ex_library_books;
extern vector<User*> ex_library_users;
extern vector<Loan*> ex_library_loans;

class DatabaseManager {
public:

    // Constructor: Initializes a DatabaseManager instance by opening a connection to the specified SQLite database
    explicit DatabaseManager(const std::string& databaseName);

    // Destructor: Closes the database connection when the DatabaseManager instance is destroyed
    ~DatabaseManager();

    // Create required tables (Books, Users, Loans) in the SQLite database
    void createTables();

    // Insert sample data into the database tables for testing purposes
    void insertSampleData();

    // Insert a book into the Books table using detailed book information
    void insertBook(const std::string& isbn, const std::string& title, const std::string& author,
                    int publicationYear, const std::string& genre, bool availability, int quantity);

    // Overload of insertBook to insert a book using a Book object
    void insertBook(Book*);

    // Insert a user into the Users table using a User object
    void insertUser(User*);

    // Insert a loan into the Loans table using a Loan object
    void insertLoan(Loan*);

    // Delete a book from the Books table by its ISBN
    void deleteBook(const std::string& isbn);

    // Display all records in the Books table
    void displayBooks();

    // import all books from the Books table into a provided vector
    void importBooks(vector<Book*> &book_list);

    // import all users from the Users table into a provided vector
    void importUsers(vector<User*> &user_list);

    // import all loans from the Loans table into a provided vector
    void importLoans(vector<Loan*> &loan_list);

    // Retrieve all books loaned by a specific user based on user ID
    vector<Book*> getLoanedBooksByUser(const std::string& userId);

    // Search for books in the Books table using a specified attribute and value
    void searchBooks(const std::string& attribute, const std::string& value);

    // Search for users in the Users table using a specified attribute and value
    void searchUsers(const std::string& attribute, const std::string& value);

    // Search for loans in the Loans table using a specified attribute and value
    void searchLoans(const std::string& attribute, const std::string& value);

    // Decrease the quantity of a book in the Books table by one
    void decrementBookQuantity(const std::string& isbn);

    // Clear all records from all tables
    void boomboom();

    // Callback function to handle specific user data fetching scenarios
    static int userCallback(void *data, int argc, char **argv, char **azColName);

private:
    // SQLite database connection handle
    sqlite3* db;

    // Generic callback function to process SQL query results
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);

    // Execute an SQL query with optional callback and user data
    int execute_sql(const std::string& sql, int (*callback)(void*,int,char**,char**) = nullptr, void* data = nullptr);
};

#endif //LIBRARY_SYSTEM_PROJECT_DATABASEMANAGER_H