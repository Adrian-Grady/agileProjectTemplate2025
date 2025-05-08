#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;
void entryIO();
void getSummary();
void recordAttn();
void addStudent();
void addClass();
void editStudent();
void editClass();
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
        //get data from database
    }
    else if (sumIn == 2)
    {
        //get data from database
    }
    else if (sumIn == 3)
    {
        //get data from database
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
    cout << "Which class would you like to record attendance for?" << endl;
    //populate from database
    auto start = std::chrono::system_clock::now();
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    char tmBuff[30];
    ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
    cout << "What day do you wish to record attendance for?" << endl << "1. Use Current Time" << endl << "2. Enter a date." << endl;
    char inDateOpt = 0;
    cin >> inDateOpt;
    if (inDateOpt == '1')
    {
        //do stuff
    }
    else if (inDateOpt == '2')
    {
        //do stuff
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
    //commit to database
    //db.addStudent(firstName, lastName);
    cout << endl << "Successfully added student." << endl << "Add another?" << endl << "1. Yes" << "2. No" << endl;

    string response;
    cin >> response;

    if (response == "2"){
        continueAdding = false;
    }
        
    while (response != "2" && response != "1"){
        cout << "Invalid entry! Please try again." << endl << endl;
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
    //populate from database
    while (true)
    {
        cout << "What would you like to edit about them?" << endl << "1. First Name" << endl << "2. Last Name" << endl << "3. Edit Attendance" << endl << "4. Edit Class Enrollment" << endl;
        char editStudentChar;
        cin >> editStudentChar;
        if (editStudentChar == '1')
        {
            //do stuff
            break;
        }
        else if (editStudentChar == '2')
        {
            //do stuff
            break;
        }
        else if (editStudentChar == '3')
        {
            //do stuff
            break;
        }
        else if (editStudentChar == '4')
        {
            //do stuff
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
    cout << "1. Enroll Student" << endl << "2. Remove Student" << endl << "3. Edit Class Name" << endl << "4. Add Custom Order" << endl;
    char editClassChar;
    cin >> editClassChar;
    if (editClassChar == '1')
    {
        //do stuff
    }
    else if (editClassChar == '2')
    {
        //do stuff
    }
    else if (editClassChar == '3')
    {
        //do stuff
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