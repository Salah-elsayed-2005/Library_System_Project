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

    void createTable();
    void insertSampleData();
    void insertBook(const std::string& isbn, const std::string& title, const std::string& author,
                    int publicationYear, const std::string& genre, bool availability, int quantity);
    void insertBook(Book*);
    void insertUser(User*);
    void insertLoan(Loan*);


    void deleteBook(const std::string& isbn);
    void displayBooks();
    void disp(); // TEMP
    void exportBooks(vector<Book*> & book_list);
    void exportUsers(vector<User*> &user_list);
    void exportLoans(vector<Loan*> &loan_list);
    void setCheckedOutBooks(Member* member);
    void setMemberLoans(Member* member);

    void searchBooks(const std::string& attribute, const std::string& value);
    void decrementBookQuantity(const std::string& isbn);
    vector<Book*> getLoanedBooksByUser(const std::string& userId);
    void boomboom();
    static int userCallback(void *data, int argc, char **argv, char **azColName);

private:
    sqlite3* db;

    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    int execute_sql(const std::string& sql, int (*callback)(void*,int,char**,char**) = nullptr, void* data = nullptr);
};




#endif //LIBRARY_SYSTEM_PROJECT_DATABASEMANAGER_H
