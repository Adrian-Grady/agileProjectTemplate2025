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
    void addStudent(const string& firstName, const string& lastName); //add students
    void editStudentFirstName(int studentID, const string& newFirstName);
    void editStudentLastName(int studentID, const string& newLastName);
    void getAllClasses();
private:
    sqlite3* db;
    bool openDB(const string& dbPath);
    void closeDB();
};
