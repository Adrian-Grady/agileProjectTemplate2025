#pragma once
#include <iostream>
#include "sqlite3.h"
#include <string>
#include <vector>


using namespace std;

class DBAbstraction
{
public:
    DBAbstraction(const string& dbPath);
    ~DBAbstraction();
    
    void getAllStudents(); //prints all the students]
    void getAllClasses();
    void addStudent(const string& firstName, const string& lastName); //add students
    void addClass(const string& className);
    void editStudentFirstName(int studentID, const string& newFirstName);
    void editStudentLastName(int studentID, const string& newLastName);
    void editClassName(int classID, const string& newClassName);
    void recordAttendence(int studentID, int classID, const string& date, const string& present);
    void getClassSummary(int classID);
    void getDaySummary(const string& date);
    void getStudentSummary(int studentID);
    void enrollStudentInClass(int studentID, int classID);
    void removeStudentFromClass(int studentID, int classID);
    string getStudentFromID(int studentId);
    vector<int> getStudentsInClass(int classID);
    void printAllStudentsInClass(int classID);
    
    

private:
    sqlite3* db;
    bool openDB(const string& dbPath);
    void closeDB();
};
