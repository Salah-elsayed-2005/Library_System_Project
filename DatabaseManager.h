#ifndef LIBRARY_SYSTEM_PROJECT_DATABASEMANAGER_H
#define LIBRARY_SYSTEM_PROJECT_DATABASEMANAGER_H

#include "sqlite3.h"
#include <string>
#include "Str.h"
#include "Book.h"
#include "User.h"

using namespace OurBook;

class DatabaseManager {
public:
    explicit DatabaseManager(const std::string& databaseName);
    ~DatabaseManager();

    void createTables();
    void insertSampleData();
    void insertBook(const std::string& isbn, const std::string& title, const std::string& author,
                    int publicationYear, const std::string& genre, bool availability, int quantity);
    void insertBook(Book*);
    void insertUser(User*);
    void insertLoan(Loan*);

    // Delete book record in table Books by ISBN
    void deleteBook(const std::string& isbn);

    // Dispalay all books in the Books table
    void displayBooks();

    void disp(); // TEMP

    // Exports all the books in table Books to vector of type Book
    void exportBooks(vector<Book*> & book_list);

    // Exports all the users in table Users to vector of type User
    void exportUsers(vector<User*> &user_list);

    // Exports all the users in table Loans to vector of type Loan
    void exportLoans(vector<Loan*> &loan_list);

    //
    void setCheckedOutBooks(Member* member);
    void setMemberLoans(Member* member);


    vector<Book*> getLoanedBooksByUser(const std::string& userId);

    vector<Loan*> getLoanedDataByUser(const std::string& userId);

    // Search in Books table by providing the attribute (column name) and value (element in cell corresponding to the column)
    void searchBooks(const std::string& attribute, const std::string& value);

    // Search in Users table by providing the attribute (column name) and value (element in cell corresponding to the column)
    void searchUsers(const std::string& attribute, const std::string& value);

    // Search in Loans table by providing the attribute (column name) and value (element in cell corresponding to the column)
    void searchLoans(const std::string& attribute, const std::string& value);

    //Decrease the value of Quantity in Books table by 1 (used in loans)
    void decrementBookQuantity(const std::string& isbn);

    //Clear all values in all tables
    void boomboom();

    static int userCallback(void *data, int argc, char **argv, char **azColName);

    // temp for testing
    void tmep();

private:
    // Special variable for sqlite to function
    sqlite3* db;

    // Function to handel the incoming data from sqlite database
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);

    // Function to send the queries to the sqlite database and outout an error if meet
    int execute_sql(const std::string& sql, int (*callback)(void*,int,char**,char**) = nullptr, void* data = nullptr);
};




#endif //LIBRARY_SYSTEM_PROJECT_DATABASEMANAGER_H
