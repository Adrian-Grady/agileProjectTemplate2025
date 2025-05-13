#include <iostream>
#include <ctime>
#include <chrono>
#include "DBAbstraction.h"
#include <vector>
#include <string>
using namespace std;
void entryIO();
void getSummary();
void recordAttn();
void addStudent();
void addClass();
void editStudent();
void editClass();
DBAbstraction dbase("attendence.db");
int main()
{
    entryIO();
    return 0;
}
void entryIO()
{
    cout << "Hello, Professor" << endl << "1. Summary" << endl << "2. Record Attendance" << endl << "3. Edit or Add Students or Classes" << endl;
    char inChar = 0;

    cin.clear();
    fflush(stdin);
    cin >> inChar;
    if (inChar == '1')
    {
        getSummary();
    }
    else if (inChar == '2')
    {
        recordAttn();
    }
    else if (inChar == '3')
    {
        cout << "1. Add Student" << endl << "2. Add Class" << endl << "3. Edit Student" << endl << "4. Edit Class" << endl << "5. Return to Top" << endl;
        char charEditAdd;
        cin >> charEditAdd;
        cin.clear();
        fflush(stdin);
        if (charEditAdd == '1')
        {
            addStudent();
        }
        else if (charEditAdd == '2')
        {
            addClass();
        }
        else if (charEditAdd == '3')
        {
            editStudent();
        }
        else if (charEditAdd == '4')
        {
            editClass();
        }
        else if (charEditAdd == '5')
        {
            entryIO();
        }
        else
        {
            cout << "Invalid entry! Please try again." << endl;
            entryIO();
        }
    }
    else
    {
        cout << "Invalid entry! Please try again." << endl;
        entryIO();
    }
}

void getSummary()
{
    cout << "Which summary would you like?" << endl << "1. Summary of the entire class" << endl << "2. Summary of one day" << endl << "3. Summary of one student" << endl << "4. Return to Top" << endl;
    int sumIn;
    cin >> sumIn;
    if (sumIn == 1)
    {
        dbase.getClassSummary();
    }
    else if (sumIn == 2)
    {
        dbase.getDaySummary();
    }
    else if (sumIn == 3)
    {
        dbase.getStudentSummary();
    }
    else if (sumIn == 4)
    {
        entryIO();
    }
    else
    {
        cout << "Invalid entry! Please try again." << endl;
        getSummary();
    }
    entryIO();
}

void recordAttn()
{
    dbase.getAllClasses();
    cout << "Which class would you like to record attendance for?" << endl;
    string classID;
    cin >> classID;
    auto start = std::chrono::system_clock::now();
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    char tmBuff[30];
    ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
    cout << "What day do you wish to record attendance for?" << endl << "1. Use current time" << endl << "2. Enter a date." << endl;
    cout << "Enter p for present, l for late, ea for excused absence, and ua for unexcused absence." << endl;
    char inDateOpt = 0;
    cin >> inDateOpt;
    if (inDateOpt == '1')
    {
        tm localtime = *localtime(&legacyStart);
        int year = localtime.tm_year + 1900;
        int month = localtime.tm_mon + 1;
        int day = localtime.tm_mday;
        string date = day + "/" + month + "/" + year;
        vector<int> allStudents = dbase.getStudentsInClass(classID);
        foreach(int studentID : allStudents)
        {
            string name = dbase.getStudentFromID(studentID);
            cout << "Student ID: " << studentID << name << endl;
            string attnData;
            cin >> attnData;
            dbase.recordAttendance(studentID, classID, date, attnData);
        }

;    }
    else if (inDateOpt == '2')
    {
        cout << "Enter the date you wish to edit" << endl;
        string date;
        cin >> date;

        vector<int> allStudents = dbase.getStudentFromClass(classID);
        foreach(int studentID : allStudents)
        {
            string name = dbase.getName(studentID);
            cout << "Student ID: " << studentID << name << endl;
            string attnData;
            cin >> attnData;
            dbase.recordAttendance(studentID, classID, date, attnData);
        }
    }
    entryIO();
}

void addStudent()
{
    bool continueAdding = true;
    while (continueAdding){

    cout << "Please enter the new student's first name" << endl;
    string firstName;
    cin >> firstName;
    cout << "Please enter the new student's last name" << endl;
    string lastName;
    cin >> lastName;
    dbase.addStudent(firstName, lastName);
    cout << endl << "Successfully added student." << endl << "Add another?" << endl << "1. Yes" << "2. No" << endl;

    string response;
    cin >> response;

    if (response == "2"){
        continueAdding = false;
    }
        
    while (response != "2" && response != "1"){
        cout << "Invalid entry! Please try again." << endl;
        cin >> response;
    }
    }
    entryIO();
}

void addClass()
{
    cout << "Please enter the class name" << endl;
    string className;
    cin >> className;
    dbase.addClass(className);
    while (true)
    {
        cout << "Would you like to populate this class now?" << endl << "1. Yes" << endl << "2. No" << endl;
        char popClassBool;
        cin >> popClassBool;
        if (popClassBool == '1')
        {
            editClass();
            break;
        }
        else if (popClassBool == '2')
        {
            entryIO();
            break;
        }
        else
        {
            cout << "Invalid entry! Please try again." << endl;
        }
    }
    entryIO();
}

void editStudent()
{
    cout << "Which student would you like to edit?" << endl;
    dbase.getAllStudents();
    cout << "Enter the selected student ID number" << endl;
    int stuID;
    cin >> stuID;
    while (true)
    {
        cout << "What would you like to edit about them?" << endl << "1. First Name" << endl << "2. Last Name" << endl << "3. Edit Attendance" << endl << "4. Edit Class Enrollment" << endl;
        char editStudentChar;
        cin >> editStudentChar;
        if (editStudentChar == '1')
        {
            cout << "Enter their new first name" << endl;
            string newFirstName;
            cin >> newFirstName;
            dbase.editStudentFirstName(stuID, newFirstName);
            break;
        }
        else if (editStudentChar == '2')
        {

            cout << "Enter their new last name" << endl;
            string newLastName;
            cin >> newLastName;
            dbase.editStudentLastName(stuID, newLastName);
            break;
        }
        else if (editStudentChar == '3')
        {
            dbase.getStudentSummary(stuID);
            cout << "Enter the class ID" << endl;
            int classID;
            cin >> classID;
            dbase.getClassSummary(classID);
            cout << "Enter the date you wish to edit" << endl;
            string newDate;
            cin >> newDate;
            cout << "Enter the new attendance record" << endl;
            string attnRec;
            cin >> attnRec;
            dbase.recordAttendence(stuID, classID, newDate, attnRec)
            break;
        }
        else if (editStudentChar == '4')
        {
            cout << "1. Add student to class" << endl << "2. Remove student from class" << endl;
            string editEnrollBool;
            cin >> editEnrollBool;
            dbase.getAllClasses();

            cout << "Enter the class ID" << endl;
            string classID;
            cin >> classID;
            if (editEnrollBool == '1')
            {
                dbase.enrollStudentInClass(stuID, classID);
            }
            else if (editEnrollBool == '2')
            {
                dbase.removeStudentFromClass(stuID, classID);
            }
            else
            {
                cout << "Invalid info! Please try again." << endl;
                editStudent();
            }
            break;
        }
        else
        {
            cout << "Invalid entry! Please try again" << endl;
        }
    }
    entryIO();
}

void editClass()
{
    cout << "Which class would you like to edit?" << endl;
    //populate from database
    dbase.getAllClasses();
    char classSelection;
    cin >> classSelection;
    cout << "1. Enroll Student" << endl << "2. Remove Student" << endl << "3. Edit Class Name" << endl << "4. Add Custom Order" << endl;
    char editClassChar;
    cin >> editClassChar;
    if (editClassChar == '1')
    {
        //do stuff
        bool continueAdding = true;
        while (continueAdding){
            cout << "Which student would you like to add?" << endl;
            dbase.getAllStudents();
            char studentSelection;
            cin >> studentSelection;
            dbase.enrollStudentInClass(studentSelection, classSelection);
            cout << "Student added. Add another?" << endl;
            char continueAddingSelection;
            cin >> continueAddingSelection;
            if (continueAddingSelection == '2'){
                continueAdding = false;
            }
                
            while (continueAddingSelection != '2' && continueAddingSelection != '1'){
                cout << "Invalid entry! Please try again." << endl << endl;
                cin >> continueAddingSelection;
            }
            }
            entryIO(); 
        
    }
    else if (editClassChar == '2')
    {
        //do stuff
        bool continueAdding = true;
        while (continueAdding){
            cout << "Which student would you like to remove?" << endl;
            dbase.getAllStudentsInClass(classSelection);
            char studentSelection;
            cin >> studentSelection;
            dbase.removeStudentFromClass(studentSelection, classSelection);
            cout << "Student removed. Remove another?" << endl;
            char continueAddingSelection;
            cin >> continueAddingSelection;
            if (continueAddingSelection == '2'){
                continueAdding = false;
            }
                
            while (continueAddingSelection != '2' && continueAddingSelection != '1'){
                cout << "Invalid entry! Please try again." << endl << endl;
                cin >> continueAddingSelection;
            }
        }
            entryIO(); 
    }
    else if (editClassChar == '3')
    {
        //do stuff
        cout << "Enter new name for class:" << endl;
        string newName;
        cin >> newName;
        dbase.editClassName(editClassChar, newName);
        cout << "Name successfully changed." << endl;
        entryIO();
    }
    else if (editClassChar == '4')
    {
        //do stuff
    }
    else
    {
        cout << "Invalid entry! Please try again" << endl;
        editClass();
    }
    entryIO();
}
