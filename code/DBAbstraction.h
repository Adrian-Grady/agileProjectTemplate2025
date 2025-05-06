#pragma once
#include <iostream>
#include "sqlite3.h"
#include <string>


using namespace std;

class DBAbstraction
{
public:
    DBAbstraction(const string& dbPath);
    ~DBAbstraction();
    
    void getAllStudents(); //prints all the students
private:
    sqlite3* db;
    bool openDB(const string& dbPath);
    void closeDB();
};
