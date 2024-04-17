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
    std::string sql = "INSERT OR IGNORE INTO Books VALUES ('8624625635653', 'Calculus', 'Stewart', 2012, 'Math', 1, 1),('8624625635663', 'Calculus', 'Larson', 2004, 'Math', 1, 1),('8624625635673', 'Advanced Calculus', 'Larson', 2010, 'Math', 1, 1),('8622625632663', 'Physics', 'Mo. Ismail', 2016, 'Physics', 1, 1),('8622625632673', 'Quantum Mechanics', 'Dirac', 1988, 'Physics', 1, 1),('8622625632683', 'Classical Mechanics', 'Taylor', 2005, 'Physics', 1, 1),('8624625635683', 'Statistics', 'Freedman', 2009, 'Math', 1, 1),('8624625635693', 'Algebra', 'Artin', 2011, 'Math', 1, 1),('8624625635703', 'Geometry', 'Coxeter', 1969, 'Math', 1, 1),('8624625635713', 'Trigonometry', 'Lial', 1992, 'Math', 1, 1),('8624625635723', 'Linear Algebra', 'Strang', 2016, 'Math', 1, 1),('8622625632693', 'Thermodynamics', 'Callen', 1985, 'Physics', 1, 1),('8622625632703', 'Electrodynamics', 'Griffiths', 1999, 'Physics', 1, 1),('8622625632713', 'Particle Physics', 'Griffiths', 2008, 'Physics', 1, 1),('8622625632723', 'Astrophysics', 'Carroll', 2007, 'Physics', 1, 1),('8624625635733', 'Differential Equations', 'Arnold', 1973, 'Math', 1, 1),('8624625635743', 'Real Analysis', 'Rudin', 1976, 'Math', 1, 1),('8624625635753', 'Complex Analysis', 'Ahlfors', 1966, 'Math', 1, 1),('8624625635763', 'Number Theory', 'Hardy', 1938, 'Math', 1, 1),('8624625635773', 'Topology', 'Munkres', 1975, 'Math', 1, 1),('8622625632733', 'Fluid Mechanics', 'Batchelor', 1967, 'Physics', 1, 1),('8622625632743', 'Relativity', 'Hartle', 2003, 'Physics', 1, 1),('8622625632753', 'Quantum Field Theory', 'Peskin', 1995, 'Physics', 1, 1),('8622625632763', 'Solid State Physics', 'Ashcroft', 1976, 'Physics', 1, 1),('8622625632773', 'Optics', 'Hecht', 1987, 'Physics', 1, 1),('8624625635783', 'Probability', 'Ross', 2010, 'Math', 1, 1),('8624625635793', 'Biostatistics', 'Daniel', 1999, 'Math', 1, 1),('8624625635803', 'Discrete Mathematics', 'Rosen', 2012, 'Math', 1, 1),('8624625635813', 'Combinatorics', 'Bona', 2011, 'Math', 1, 1),('8624625635823', 'Logic and Proofs', 'Velleman', 2006, 'Math', 1, 1),('8622625632783', 'Nuclear Physics', 'Krane', 1988, 'Physics', 1, 1),('8622625632793', 'Molecular Physics', 'McQuarrie', 2008, 'Physics', 1, 1),('8622625632803', 'Cosmology', 'Weinberg', 2008, 'Physics', 1, 1),('8622625632813', 'Signal Processing', 'Oppenheim', 1999, 'Electronics', 1, 1),('8622625632823', 'Microelectronics', 'Sedra', 2004, 'Electronics', 1, 1),('8622625632833', 'VLSI Design', 'West', 2012, 'Electronics', 1, 1),('8622625632843', 'Antenna Theory', 'Balanis', 2016, 'Electronics', 1, 1),('8622625632853', 'Digital Communication', 'Proakis', 2007, 'Electronics', 1, 1),('8622625632863', 'Control Systems', 'Ogata', 2010, 'Electronics', 1, 1),('8622625632873', 'Robotics', 'Craig', 2005, 'Engineering', 1, 1),('8622625632883', 'Thermal Physics', 'Schroeder', 2000, 'Physics', 1, 1),('8622625632893', 'Organic Chemistry', 'Carey', 2013, 'Chemistry', 1, 1),('8622625632903', 'Inorganic Chemistry', 'Housecroft', 2010, 'Chemistry', 1, 1),('8622625632913', 'Biochemistry', 'Voet', 2016, 'Chemistry', 1, 1),('8622625632923', 'Analytical Chemistry', 'Skoog', 2014, 'Chemistry', 1, 1),('8622625632933', 'Environmental Science', 'Keller', 2018, 'Biology', 1, 1),('8622625632943', 'Molecular Biology', 'Weaver', 2012, 'Biology', 1, 1),('8622625632953', 'Cell Biology', 'Pollard', 2017, 'Biology', 1, 1),('8622625632963', 'Genetics', 'Pierce', 2014, 'Biology', 1, 1),('8622625632973', 'Evolutionary Biology', 'Freeman', 2011, 'Biology', 1, 1),('8622625632983', 'Neuroscience', 'Bear', 2015, 'Biology', 1, 1),('8622625632993', 'Ecology', 'Smith', 2014, 'Biology', 1, 1),('8622625633003', 'Anatomy and Physiology', 'Marieb', 2019, 'Biology', 1, 1),('8622625633013', 'Pathophysiology', 'Copstead', 2013, 'Medicine', 1, 1),('8622625633023', 'Pharmacology', 'Katzung', 2018, 'Medicine', 1, 1),('8622625633033', 'Public Health', 'Turnock', 2016, 'Medicine', 1, 1),('8622625633043', 'Epidemiology', 'Gordis', 2014, 'Medicine', 1, 1);";

    std::cout << "Inserting sample data..." << std::endl;
    execute_sql(sql);
}

