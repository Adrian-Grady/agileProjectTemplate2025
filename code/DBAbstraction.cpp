#include "DBAbstraction.h"
#include <iomanip>

using namespace std;

DBAbstraction::DBAbstraction(const string& dbPath)
{
    if(!openDB(dbPath))
    {
        cerr << "Error opening database";
    }
}
DBAbstraction::~DBAbstraction()
{
    closeDB();
}
bool DBAbstraction::openDB(const string& dbPath)
{
    return sqlite3_open(dbPath.c_str(), &db) == SQLITE_OK;
}
void DBAbstraction::closeDB()
{
    if(db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}
//Add new students to the database
void DBAbstraction::addStudent(const string& firstName, const string& lastName)
{
    const char* sql = "INSERT INTO Students (first_name, last_name) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Status Failed: " << sqlite3_errmsg(db) << endl;
        return;
    }
    //put the students names to the place holder
    sqlite3_bind_text(stmt, 1, firstName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, lastName.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
        }
        else
        {
            cout << "Student added successfully.\n";
        }

        sqlite3_finalize(stmt);
}
void DBAbstraction::addClass(const string& className)
{
    const char* sql = "INSERT INTO class (class_name) VALUES (?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Status Failed: " << sqlite3_errmsg(db) << endl;
        return;
    }
    //put the students names to the place holder
    sqlite3_bind_text(stmt, 1, className.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Class added successfully.\n";
    }
    sqlite3_finalize(stmt);

}
void DBAbstraction::getAllStudents()
{
    const char* sql = "SELECT id, first_name, last_name FROM Students;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
        return;
    }
    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        //extract the column values
        int id = sqlite3_column_int(stmt,0);
        string firstName = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
        string lastName = reinterpret_cast<const
            char*>(sqlite3_column_text(stmt, 2));
        //print out the student info
        cout << "ID: " << id << ", First Name: " << firstName << ", Last Name: " << lastName << endl;
    }
    sqlite3_finalize(stmt);
}
//update the students name lines 77 - 127
void DBAbstraction::editStudentFirstName(int studentID, const string& newFirstName)
{
    const char* sql = "UPDATE Students SET first_name = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Preparation failed: " << sqlite3_errmsg(db) << endl;
        return;
    }
    // put the info in the place it is suppose to be in 
    sqlite3_bind_text(stmt, 1, newFirstName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, studentID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "First name updated successfully." << endl;
    }

    sqlite3_finalize(stmt);
}
void DBAbstraction::editStudentLastName(int studentID, const string& newLastName)
{
    const char* sql = "UPDATE Students SET last_name = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Preparation failed: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, newLastName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, studentID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Last name updated successfully." << endl;
    }

    sqlite3_finalize(stmt);
}
void DBAbstraction::editClassName(int classID, const string& newClassName)
{
    const char* sql = "UPDATE class SET class_name = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Preparation failed: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, newClassName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, classID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Class name updated successfully." << endl;
    }
    sqlite3_finalize(stmt);

}
void DBAbstraction::getAllClasses()
{
    sqlite3_stmt* myStatement;
    const char* query = "SELECT * FROM class";
    int statusOfPrep = sqlite3_prepare_v2(db, query, -1, &myStatement, NULL);

    if (statusOfPrep == SQLITE_OK)
        {
            cout << "Class List:\n";
            while (sqlite3_step(myStatement) == SQLITE_ROW)
            {
                int classID = sqlite3_column_int(myStatement, 0);
                const unsigned char* className = sqlite3_column_text(myStatement, 1);

                cout << "Class ID: " << classID << ", Class Name: " << className << endl;
            }
            sqlite3_finalize(myStatement);
        }
        else
        {
            cerr << "Problem creating prepared statement: " << sqlite3_errmsg(db) << endl;
        }
}

void DBAbstraction::getClassSummary(int classID)
{
    sqlite3_stmt* myStatement;
    const char* query = "SELECT DISTINCT Students.first_name, Students.last_name, Attendence.date, Attendence.present, Attendence.class_id, Attendence.id FROM Students, Attendence WHERE Attendence.class_id = ? AND Attendence.student_id = Students.id AND Attendence.date IS NOT NULL ORDER BY Attendence.date ASC; ";
    int statusOfPrep = sqlite3_prepare_v2(db, query, -1, &myStatement, NULL);
    sqlite3_bind_int(myStatement, 1, classID);
   

    if (statusOfPrep == SQLITE_OK)
    {
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW)
        {
            const unsigned char* firstName = sqlite3_column_text(myStatement, 0);
            const unsigned char* lastName = sqlite3_column_text(myStatement, 1);
            const unsigned char* classDate = sqlite3_column_text(myStatement, 2);
            const unsigned char* present = sqlite3_column_text(myStatement, 3); 
            int classID = sqlite3_column_int(myStatement, 4);
            int attendenceID = sqlite3_column_int(myStatement, 5);
            cout << firstName << " " << lastName << " " << present << " on " << classDate << endl;

            //need to cast and decide what to print still
            statusOfStep = sqlite3_step(myStatement);
        }

        sqlite3_finalize(myStatement);
    }
    else
    {
        cout << "Problem creating a prepared statement" << endl;
    }
}

void DBAbstraction::getDaySummary(const string& date)
{
    sqlite3_stmt* myStatement;
    const char* query = "SELECT DISTINCT Students.first_name, Students.last_name, Attendence.date, Attendence.present, Attendence.class_id, Attendence.id, class.class_name FROM Students, Attendence, class WHERE Attendence.date = ? AND Attendence.student_id = Students.id AND Attendence.class_id = class.id AND Attendence.date IS NOT NULL ORDER BY Attendence.date ASC; ";
    int statusOfPrep = sqlite3_prepare_v2(db, query, -1, &myStatement, NULL);
    sqlite3_bind_text(myStatement, 1, date.c_str(), -1, SQLITE_STATIC);

    if (statusOfPrep == SQLITE_OK)
    {
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW)
        {
            const unsigned char* firstName = sqlite3_column_text(myStatement, 0);
            const unsigned char* lastName = sqlite3_column_text(myStatement, 1);
            const unsigned char* classDate = sqlite3_column_text(myStatement, 2);
            const unsigned char* present = sqlite3_column_text(myStatement, 3);
            int classID = sqlite3_column_int(myStatement, 4);
            int attendenceID = sqlite3_column_int(myStatement, 5);
            const unsigned char* className = sqlite3_column_text(myStatement, 6);
            cout << firstName << " " << lastName << " " << present << " on " << classDate << " in " << className << endl;

            //need to cast and decide what to print still
            statusOfStep = sqlite3_step(myStatement);
        }

        sqlite3_finalize(myStatement);
    }
    else
    {
        cout << "Problem creating a prepared statement" << endl;
    }
}

void DBAbstraction::getStudentSummary(int studentID)
{
    sqlite3_stmt* myStatement;
    const char* query = "SELECT DISTINCT Students.first_name, Students.last_name, Attendence.date, Attendence.present, Attendence.class_id, Attendence.id, class.class_name FROM Students, Attendence, class WHERE Attendence.student_id = ? AND Attendence.student_id = Students.id AND Attendence.class_id = class.id AND Attendence.date IS NOT NULL ORDER BY Attendence.date ASC; ";
    int statusOfPrep = sqlite3_prepare_v2(db, query, -1, &myStatement, NULL);
    sqlite3_bind_int(myStatement, 1, studentID);

    if (statusOfPrep == SQLITE_OK)
    {
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW)
        {
            const unsigned char* firstName = sqlite3_column_text(myStatement, 0);
            const unsigned char* lastName = sqlite3_column_text(myStatement, 1);
            const unsigned char* classDate = sqlite3_column_text(myStatement, 2);
            const unsigned char* present = sqlite3_column_text(myStatement, 3);
            int classID = sqlite3_column_int(myStatement, 4);
            int attendenceID = sqlite3_column_int(myStatement, 5);
            const unsigned char* className = sqlite3_column_text(myStatement, 6);
            cout << present << " on " << classDate << " in " << className << endl;

            //need to cast and decide what to print still
            statusOfStep = sqlite3_step(myStatement);
        }

        sqlite3_finalize(myStatement);
    }
    else
    {
        cout << "Problem creating a prepared statement" << endl;
    }
}

void DBAbstraction::enrollStudentInClass(int studentID, int classID)
{
    string sql = "INSERT INTO Attendence (student_id, class_id, date, present) VALUES (?, ?, NULL, NULL);";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, studentID);
        sqlite3_bind_int(stmt, 2, classID);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error enrolling student: " << sqlite3_errmsg(db) << endl;
        }
    } else {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}

void DBAbstraction::removeStudentFromClass(int studentID, int classID) {
    string sql = "DELETE FROM Attendence WHERE student_id = ? AND class_id = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, studentID);
        sqlite3_bind_int(stmt, 2, classID);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error removing student: " << sqlite3_errmsg(db) << endl;
        }
    } else {
        cerr << "SQL prepare error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}
string DBAbstraction::getStudentFromID(int studentId)
{
    sqlite3_stmt* myStatement;
    const char* query = "SELECT Students.first_name, Students.last_name FROM Students WHERE Students.id = ? ";
    int statusOfPrep = sqlite3_prepare_v2(db, query, -1, &myStatement, NULL);
    sqlite3_bind_int(myStatement, 1, studentId);
    string fullName;

    if (statusOfPrep == SQLITE_OK)
    {
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW)
        {
            const unsigned char* firstName = sqlite3_column_text(myStatement, 0);
            const unsigned char* lastName = sqlite3_column_text(myStatement, 1);
            fullName = string(reinterpret_cast<const char*>(firstName)) + " " + string(reinterpret_cast<const char*>(lastName));

            //need to cast and decide what to print still
            statusOfStep = sqlite3_step(myStatement);
        }

        sqlite3_finalize(myStatement);
    }
    else
    {
        cout << "Problem creating a prepared statement" << endl;
    }
    return fullName;
}
vector<int> DBAbstraction::getStudentsInClass(int classID)
{
    sqlite3_stmt* myStatement;
    const char* query = "SELECT DISTINCT Attendence.student_id FROM Attendence WHERE Attendence.date IS NULL AND Attendence.class_id = ?";
    int statusOfPrep = sqlite3_prepare_v2(db, query, -1, &myStatement, NULL);
    sqlite3_bind_int(myStatement, 1, classID);
    vector<int> studentIDs;
    if (statusOfPrep == SQLITE_OK)
    {
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW)
        {
            int id = sqlite3_column_int(myStatement, 0);
            studentIDs.push_back(id);
            statusOfStep = sqlite3_step(myStatement);
        }

        sqlite3_finalize(myStatement);
    }
    else
    {
        cout << "Problem creating a prepared statement" << endl;
    }

    return studentIDs;
}
vector<int> DBAbstraction::getAllStudentsIDsOrderByLastName(int classID)
{
    sqlite3_stmt* myStatement;
    const char* query = "SELECT Students.id FROM Students WHERE Students.id IN( SELECT DISTINCT Attendence.student_id FROM Attendence WHERE Attendence.date IS NULL AND Attendence.class_id = ?) ORDER BY Students.last_name ASC";
    int statusOfPrep = sqlite3_prepare_v2(db, query, -1, &myStatement, NULL);
    sqlite3_bind_int(myStatement, 1, classID);
    vector<int> studentIDs;
    if (statusOfPrep == SQLITE_OK)
    {
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW)
        {
            int id = sqlite3_column_int(myStatement, 0);
            studentIDs.push_back(id);
            statusOfStep = sqlite3_step(myStatement);
        }

        sqlite3_finalize(myStatement);
    }
    else
    {
        cout << "Problem creating a prepared statement" << endl;
    }

    return studentIDs;
}
void DBAbstraction::printAllStudentsInClass(int classID)
{
    sqlite3_stmt* stmt;
    const char* sql =
        "SELECT DISTINCT Students.id, Students.first_name, Students.last_name, class.class_name "
        "FROM Students "
        "JOIN Attendence ON Students.id = Attendence.student_id "
        "JOIN class ON Attendence.class_id = class.id "
        "WHERE class.id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, classID);

    cout << "Students in class ID " << classID << " " << endl;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* firstName = sqlite3_column_text(stmt, 1);
        const unsigned char* lastName = sqlite3_column_text(stmt, 2);
        const unsigned char* className = sqlite3_column_text(stmt, 3);

        cout << "ID: " << id << ", Name: " << firstName << " " << lastName << ", Class: " << className << endl;
    }

    sqlite3_finalize(stmt);
}
void DBAbstraction::recordAttendence(int studentID, int classID, const string& date, const string& present)
{
    const char* sql = "INSERT INTO Attendence (student_id, class_id, date, present) VALUES (?,?,?,?);";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to send student statement: " << sqlite3_errmsg(db) << endl;
    }
    
    sqlite3_bind_int(stmt, 1, studentID);
    sqlite3_bind_int(stmt, 2, classID);
    sqlite3_bind_text(stmt, 3, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, present.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Failed to record attendence: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Attendence recorded: " << present << " for student " << studentID << " on " << date << endl;
    }
    sqlite3_finalize(stmt);
}

