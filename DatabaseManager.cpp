//
// Created by Fouad Hashesh on 13/04/2024.
//
#include <iostream>
#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(const std::string& databaseName) {
    if (sqlite3_open(databaseName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Database opened successfully." << std::endl;
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
    std::cout << "Database connection closed." << std::endl;
}

int DatabaseManager::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << " ";
    }
    std::cout << std::endl;
    return 0;
}

int DatabaseManager::execute_sql(const std::string& sql, int (*callback)(void*,int,char**,char**), void* data) {
    char* errorMessage;
    int result = sqlite3_exec(db, sql.c_str(), callback, data, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    return result;
}

void DatabaseManager::createTable() {
    std::string sql = "CREATE TABLE IF NOT EXISTS Books ("
                      "ISBN VARCHAR(20) PRIMARY KEY,"
                      "Title VARCHAR(255) NOT NULL,"
                      "Author VARCHAR(255),"
                      "PublicationYear INT,"
                      "Genre VARCHAR(100),"
                      "Availability BOOLEAN DEFAULT TRUE,"
                      "Quantity INT DEFAULT 1);";
    std::cout << "Creating table if not exists..." << std::endl;
    execute_sql(sql);
}

void DatabaseManager::insertBook(const std::string& isbn, const std::string& title, const std::string& author,
                                 int publicationYear, const std::string& genre, bool availability, int quantity) {
    std::string sql = "INSERT OR REPLACE INTO Books (ISBN, Title, Author, PublicationYear, Genre, Availability, Quantity) VALUES ('" +
                      isbn + "', '" + title + "', '" + author + "', " +
                      std::to_string(publicationYear) + ", '" + genre + "', " + (availability ? "1" : "0") + ", " +
                      std::to_string(quantity) + ");";
    std::cout << "Inserting a new book record..." << std::endl;
    execute_sql(sql);
}

void DatabaseManager::deleteBook(const std::string& isbn) {
    std::string sql = "DELETE FROM Books WHERE ISBN = '" + isbn + "';";
    std::cout << "Deleting book with ISBN " << isbn << "..." << std::endl;
    execute_sql(sql);
}

void DatabaseManager::displayBooks() {
    std::string sql = "SELECT * FROM Books;";
    std::cout << "Current state of the Books table:" << std::endl;
    execute_sql(sql, callback);
}

void DatabaseManager::searchBooks(const std::string& attribute, const std::string& value) {
    std::string sql = "SELECT * FROM Books WHERE " + attribute + " LIKE '%" + value + "%';";
    std::cout << "Searching for books with " << attribute << " like " << value << ":" << std::endl;
    execute_sql(sql, callback);
}

void DatabaseManager::decrementBookQuantity(const std::string& isbn) {
    // First, check the current quantity
    std::string checkQuantitySql = "SELECT Quantity FROM Books WHERE ISBN = '" + isbn + "';";
    int quantity = -1;
    auto callback = [](void *data, int argc, char **argv, char **azColName) -> int {
        if (argc > 0 && argv[0]) {
            *(int*)data = std::stoi(argv[0]);
        }
        return 0;
    };

    execute_sql(checkQuantitySql, callback, &quantity);

    // If quantity is greater than 0, decrement it and update the table
    if (quantity > 0) {
        quantity--;
        bool newAvailability = quantity > 0;
        std::string updateSql = "UPDATE Books SET Quantity = " + std::to_string(quantity) +
                                ", Availability = " + (newAvailability ? "1" : "0") +
                                " WHERE ISBN = '" + isbn + "';";
        execute_sql(updateSql);
        std::cout << "Updated quantity for ISBN " << isbn << ". New quantity is " << quantity << "." << std::endl;
    } else {
        std::cout << "No more books available for ISBN " << isbn << ". Cannot decrement quantity." << std::endl;
    }
}



// TEST ONLY. DELETE ME !
void DatabaseManager::insertSampleData() {
    std::string sql = "INSERT OR IGNORE INTO Books VALUES"
                      "('8624625635653', 'Calculus', 'Stewart', 2012, 'Math', 1, 1),"
                      "('8624625635663', 'Calculus', 'Larson', 2004, 'Math', 1, 1),"
                      "('8622625632663', 'Physics', 'Mo. Ismail' , 2016, 'Physics', 1, 1);";
    std::cout << "Inserting sample data..." << std::endl;
    execute_sql(sql);
}

